#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_tokens
{
    char    **cmds;
    int     std_out;
    int     std_in;
    struct s_tokens *next;
}   t_tokens;

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return i;
}

void print_error(char *str, char *str1, int n)
{
    write(2, str, ft_strlen(str));
    if (str1)
        write(2, str1, ft_strlen(str1));
    write(2, "\n", 1);
    if (n)
        exit(1);
}

t_tokens *init_tokens()
{
    t_tokens *ret;

    ret = malloc(sizeof(t_tokens));
    if (ret == 0)
        print_error("error: fatal", NULL, 1);
    ret->cmds = malloc(sizeof(char *) * 1024);
    if (ret->cmds == 0)
        print_error("error: fatal", NULL, 1);
    ret->std_in = 0;
    ret->std_out = 1;
    return (ret);
}

int add_cmd(t_tokens *tokens, char **argv, int i)
{
    int j = 0;

    while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
    {
        tokens->cmds[j] = argv[i];
        i++;
        j++;
    }
    i++;
    tokens->cmds[j] = NULL;
    return (i);
}

void ft_pipe(t_tokens *tokens)
{
    int pip[2];

    pipe(pip); //0에 읽기, 1에 쓰기 파이프를 연다
    tokens->next = init_tokens(); //다음 토큰 받을 준비
    tokens->std_out = pip[1];
    tokens->std_in = pip[0];
}

void exec_cmd(t_tokens *tokens, int *start, int i) {
    int pid;

    if (!(strcmp(tokens->cmds[0], "cd"))) {
        if (tokens->cmds[2] || !tokens->cmds[1])
            print_error("error: cd: bad arguments", NULL, 0);
        else if (chdir(tokens->cmds[1]))
            print_error("error: cd: cannot change ", tokens->cmds[1], 0);
        *start = i;
        return;
    }

    pid = fork();
    if (pid < 0)
        print_error("error: fatal", NULL, 1);
    if (pid == 0) {
        if (tokens->std_out != 1) {
            close(tokens->next->std_in);
            if (dup2(tokens->std_out, 1) == -1)
                print_error("error: fatal", NULL, 1);
            execve(tokens->cmds[0], tokens->cmds, NULL);
            print_error("error: cannot execute ", tokens->cmds[0], 1);
        }
    }

    if (tokens->std_out != 1) //열린거 닫고
        close(tokens->std_out);
    if (tokens->std_in != 0) //이것도 닫고... 왜 닫지?
        close(tokens->std_in);
    if (tokens->std_out == 1)
    {
        while (*start < i) //start가 i를 따라잡을때까지 기다려야하나
        {
            waitpid(0, NULL, 0);
            (*start)++;
        }
    }
}

void    ft_free(t_tokens *tokens)
{
    if (tokens)
    {
        if (tokens->cmds)
            free(tokens->cmds);
        free(tokens);
        tokens = NULL;
    }
}

int main(int argc, char **argv)
{
    t_tokens *tokens;
    int i = 1;
    int start = i;
    t_tokens *before;
    while (i < argc)
    {
        if (tokens == NULL || start == i) //토큰이 비었거나, start = i, start가 뭐지?
            tokens = init_tokens();
        if (!(strcmp(argv[i], ";"))) //;가 있다면 i숫자만 올린 후, 다음으로 간다
        {
            i++;
            continue;
        }
        //;를 만나지 않았다면 ;나 |를 만나기 전까지 명령묶음을 cmds에 추가한다.
        i = add_cmd(tokens, argv, i);
        //i - 1이 있고, 왜냐하면 argv[i] 비교에서 끊겼을수도 있으니깐 그리고 그게 |가 아니면 파이프를 만들어야 한다.
        if (argv[i - 1] && !(strcmp(argv[i - 1], "|")))
            ft_pipe(tokens); //파이프를 열고, tokens->next를 준비시킨다.
        exec_cmd(tokens, &start, i);
        before = tokens;
        ft_free(before); //이전것 제거
    }
    return 0;
}