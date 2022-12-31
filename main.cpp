#include <iostream>
#include <vector>
#include "./type_traits.hpp"
#include "./reverse_iterator.hpp"
#include "./pair.hpp"
#include "./equal_lexico.hpp"
#include <list>
#include <random>
#include <utility>

//enable_if test
template<typename T, typename ft::enable_if<ft::is_integral<T>::value, int>::type = 0>
void foo(void) { std::cout << "true\n"; }

//integral_constant test
template <unsigned n>
struct factorial : ft::integral_constant<int,n * factorial<n-1>::value> {};
template <>
struct factorial<0> : ft::integral_constant<int,1> {};

//reverse_iterator test
void test_reverse_iterator()
{
    int __flag = 0;
    // Create a vector of integers
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    // Create a reverse iterator pointing to the last element in the vector
    ft::reverse_iterator<std::vector<int>::iterator> rit(v.end());
    // Check if the reverse iterator is pointing to the last element in the vector
    if (*rit != 5) {
        std::cout << "Unexpected value at reverse iterator: expected 5, got " << *rit << std::endl;
        __flag++;
    }
    // Check if the reverse iterator can be incremented and still point to the correct element
    ++rit;
    if (*rit != 4) {
        std::cout << "Unexpected value at reverse iterator after increment: expected 4, got " << *rit << std::endl;
        __flag++;
    }
    // Check if the reverse iterator can be decremented and still point to the correct element
    --rit;
    if (*rit != 5) {
        std::cout << "Unexpected value at reverse iterator after decrement: expected 5, got " << *rit << std::endl;
        __flag++;
    }
    std::reverse_iterator<std::vector<int>::iterator> val(v.begin() + 1);
    ft::reverse_iterator<std::vector<int>::iterator> ft_val(v.begin() + 1);
    if (*val != *ft_val || *(val.base()) != *(ft_val.base())) {
        std::cout << "Unexpected value at reverse iterator or .base()\n";
        __flag++;
    }
    if (__flag == 0)
        std::cout << "Reverse Iterator test passed!\n";
    else
        std::cout << "Reverse Iterator test failed!!!\n";
}
//pair_test
void pair_test()
{
    ft::pair <int, int> foo;
    ft::pair <int, int> bar;
    std::pair <int, int> real_bar;
    int flag = 0;

    foo = ft::make_pair(10, 20);
    bar = ft::make_pair(10.5, 'A'); //암시적 형변환이 되는가?
    real_bar = std::make_pair(10.5, 'A');

    ft::pair <int, char> copy(bar); //복사생성자가 작동하는가?

    //std::cout << copy.first << " " << copy.second << "\n";
    //std::cout << bar.first << " " << bar.second << "\n";
    //std::cout << real_bar.first << " " << real_bar.second << "\n";

    if (foo.first != 10 || foo.second != 20)
        flag = 1;
    if (bar.first != real_bar.first || bar.second != real_bar.second)
        flag = 1;
    if (copy.first != 10 || copy.second != 'A')
        flag = 1;
    if (flag == 0)
        std::cout << "Pair test passed!\n";
    else if (flag == 1)
        std::cout << "!! Pair test Failed!!!\n";
}
//equal_test + lexicographical
void equal_test()
{
    int flag = 0;
    int myints[] = {20, 40, 60, 80, 100};
    std::vector<int> myvector (myints, myints + 5);

    if (!(ft::equal (myvector.begin(), myvector.end(), myints)))
        flag = 1;

    myvector[3] = 81;

    if (ft::equal (myvector.begin(), myvector.end(), myints))
        flag = 1;

    if (flag == 1)
        std::cout << "ft::equal is fuc*ed\n";
    else
        std::cout << "Equal test passed!\n";

    //======================================

    char foo[]="Apple";
    char bar[]="apartment";
    char f_foo[]="super";
    char f_bar[]="zzzzz";

    std::cout << std::boolalpha;
    if (ft::lexicographical_compare(foo,foo+5,bar,bar+9) !=
    (std::lexicographical_compare(foo,foo+5,bar,bar+9)))
        std::cout << "Lexicographical test failed!!\n";
    else if (ft::lexicographical_compare(f_foo,f_foo+5,bar,bar+9) != false)
        //비교연산자는 <다. 그래서, r < e -> false
        std::cout << "Lexicographical test failed!!\n";
    else if (ft::lexicographical_compare(f_foo,f_foo+2,f_bar,f_bar+5) != true)
        // u < z 는 true
        std::cout << "Lexicographical test failed!!\n";
    else
        std::cout << "Lexicographical test passed!\n";


}


int main() {
    //enable_if test
    std::cout << "[enable_if test]" << std::endl;
    foo<char>();
    foo<int>();
    //foo<float>(); 는 컴파일 오류가 난다. 왜냐하면 integral계열이 아니면, enable_if가 이건 적합하지 않다고 판단, 인스턴스화하지 않기 때문이다.

    // is_integral test
    std::cout << std::boolalpha;
    std::cout << "[is_integral test]" << std::endl;
    std::cout << "char: " << ft::is_integral<char>::value << std::endl;
    std::cout << "int: " << ft::is_integral<int>::value << std::endl;
    std::cout << "float: " << ft::is_integral<float>::value << std::endl;

    //integral_constant test
    std::cout << "[Integral_constant test]" << std::endl;
    std::cout << factorial<5>::value << std::endl;

    //reverse_iterator test
    test_reverse_iterator();

    //pair test
    pair_test();

    //equal test
    equal_test();
}
