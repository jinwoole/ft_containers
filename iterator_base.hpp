//
// Created by Lee on 2022/12/14.
//
#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <cstddef> //ptrdiff_t

/* 이거 하다보니 꽤 길어질것 같다. 목차 넘버 검색해서 찾자
 * 1. iterator base class
 *  1.1 Category class
 *  1.2 Distance struct
 * 2. iterator_traits
 * 3. Iterators
 *  3.1 bidirectinal iterator 와 리버스 만들 차례!
 */

namespace ft {
    /*
     * 1.1 Category class
    struct blablabla_iterator_tag {}; input, forward, bidirectional, random access, output 등등
     cplusplus에 따르면, empty class to identify the category of an iterator as an input iterator다.
     각 태그가 알맞게 들어가면, 이터레이터의 종류에 맞게 각 함수와 매서드들의 작동방식이 맞춰진다. 코드 보니 그렇더라.
     예를 들어, advance에 인자 2개만 들어가도 알아서 이거 하나 더 들어간 함수가 작동한다.
     */
    class input_iterator_tag {};
    class output_iterator_tag {};
    class forward_iterator_tag {};
    class bidirectional_iterator_tag {};
    class random_access_iterator_tag {};

    /*
     * 2. iterator_traits
     * https://cplusplus.com/reference/iterator/iterator_traits/?kw=iterator_traits
     * template<class Iterator>
     * class iterator_traits;
     * template <class T> class iterator_traits<T*>;
     * template <class T> class iterator_traits<const T*>;
     * traits class는 각 iterator의 성질을 결정한다. stl의 알고리즘들이 이걸 보고 들어와도 될지, 어떻게 작동할지를 결정한다.
     * 모든 iterator type마다 iterator_traits의 적절한 특수화가 이루어져야 한다.
     * difference_type, value_type, poiniter, reference, iterator_category는 무조건 define되어야 한다.
     *
     * 3개의 특수화가 이루어져야 하는데, 멤버는 각자 좀 다르다. generic defination, T*, const T*가 필요하다. 궁금하면 레퍼런스에 있다
     * 굳이 클래스 쓰는 이유가 뭔지 몰라서 gcc 소스코드를 살펴보니, struct로 만들어놨다. stl_iterator_base_types 참고하자
     */
    template <class Iterator>
    struct iterator_traits
    {
    public:
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    }; //여기서 이터레이터의 템플릿 매개변수에서 정보를 받아온다.

    template <typename T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef random_access_iterator_tag  iterator_category;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef ptrdiff_t                   difference_type;
        typedef const T                     value_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
        typedef random_access_iterator_tag  iterator_category;
    };

    /*
     * 1.2 Distance class
     * ptrdiff_t는 포인터 -연산의 결과를 나타내는 타입이다. 포인터 빼기 연산은 원소 안에서만 작동해야 하니깐
     * https://en.cppreference.com/w/cpp/types/ptrdiff_t
     *
     * distance
     * https://en.cppreference.com/w/cpp/iterator/distance
     * returns the nu,ber of hops from first to last
     * first -> 첫번째 원소 가리키는 반복자 last->last가 last
     * The number of increments needed to go from first to last. 아무튼 이걸 리턴한다
     * 구현을 살펴보면, random access와 input을 구분해야 한다. 왜냐면 input은 - 연산을 못하고 한칸씩 가는 수밖에 없기 때문이다.
     * 이때 traits를 써먹어야 한다.
     */
    template <class InputIterator>
    typename iterator_traits<InputIterator>::different_type __distance(InputIterator first, InputIterator last, ft::input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type result = 0;
        while (first != last)
        {
            ++first;
            ++result;
        }
        return result;
    }
    template <class InputIterator>
    typename iterator_traits<InputIterator>::different_type __distance(InputIterator first, InputIterator last, ft::random_access_iterator_tag)
    {
        return last - first;
    }

    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
    {
        return __distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
    }

    /*
     * 1. iterator base class 레퍼런스
    https://cplusplus.com/reference/iterator/iterator/?kw=iterator
     일단 여긴 아무 기능도 없다. 하지만, iterator_traits 클래스 템플릿을 만들기 위한 정보들을 포함한다.
    template <
     class Category,            // iterator::iterator_category
     class T,                   // iterator::value_type
     class Distance = ptrdiff_t,  // iterator::difference_type
     class Pointer = T*,          // iterator::pointer
     class Reference = T&         // iterator::reference > class iterator;
    */
    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator
    {
        typedef T           value_type; //원소 종류
        typedef Distance    difference_type; // 두 이터레이터 간 차이를 나타내기 위한 타입
        typedef Pointer     pointer; //가리켜진 원소의 포인터 나타내는 타입
        typedef Reference   reference; //레퍼런스 나타내는 타입
        typedef Category    iterator_category; //이터레이터의 종류
    };


}
#endif //FT_CONTAINERS_ITERATOR_HPP
