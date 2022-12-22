//
// Created by Jinwoo Lee on 12/22/22.
//

#ifndef FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#define FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_base.hpp"

/*
 * random access iterator
 * https://cplusplus.com/reference/iterator/RandomAccessIterator/
 * https://en.cppreference.com/w/cpp/iterator/random_access_iterator
 * bidirectional을 가지고 만들어야 하지만, 굳이 쓰지도 않는거 만들 이유는 없다.
 * 그래서, 위 레퍼런스에 나온 random_access_iterator의 컨셉에 맞는 ft::를 만들면 더 편하다.
 */



namespace ft
{
    template <typename T>
    class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;
            typedef T*  pointer;
            typedef T& reference;






    };

}

#endif //FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
