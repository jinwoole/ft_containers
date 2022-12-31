//
// Created by Jinwoo Lee on 12/31/22.
//

#ifndef FT_CONTAINERS_EQUAL_LEXICO_HPP
#define FT_CONTAINERS_EQUAL_LEXICO_HPP
/*
 * std::equal
 * std::lexicographical_compare
*/

namespace ft {

/*
* std::equal
* test whether the elements in two ranges are equal
* https://cplusplus.com/reference/algorithm/equal/
* stl_algobase.h 722줄 위치
*/

    /*
     * first1, last1 -> 배열의 시작지점과 종료지점을 설정한다. first1원소는 포함되지만, last1원소는 포함되지 않는다. [first1, last1)
     * first2 -> 두 번째 배열의 초기화 지점. 비교의 횟수는 첫번째 배열이 갈 수 있는 만큼 가게 된다.
     */
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

/*
 * std::lexicographical_compare
 * https://cplusplus.com/reference/algorithm/equal/
 * lexicographical : 사전편집
 * first1 last1이 first2 last2 보다 사전순으로 작을 경우
 * -> 두 범위 중 한 범위가 끝날때까지 요소의 내용이 동일한 경우, 마지막 원소들끼리 가슴이 웅장해지는 아스키 대결을 펼친다.
 * 이런걸 왜 만든거지?
 *
 */
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                  InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return first2 != last2;
    }
}




#endif //FT_CONTAINERS_EQUAL_LEXICO_HPP
