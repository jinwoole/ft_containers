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
 * 그래서, 위 레퍼런스에 나온 random_access_iterator의 컨셉에 맞는 ft::를 만들면
 */



namespace ft
{
    template <typename T>
    class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {

    public:
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
        typedef T *pointer;
        typedef T &reference;

        //기본생성자
        random_access_iterator() : pointer() {}

        //복사생성자, 소멸자는 필요없겠다
        random_access_iterator(pointer i) : _i(i) {}
        random_access_iterator(const random_access_iterator &other) : _i(other._i) {}

        //연산자 오버라이딩
        reference operator*() { return *_i; }
        pointer operator->() { return &(this->operator*()); }

        random_access_iterator &operator=(const random_access_iterator &other) {
            if (this == &other)
                return *this;
            this->_i = other._i;
            return *this;
        }
        random_access_iterator& operator++(void)
        {
            _i++;
            return *this;
        }
        random_access_iterator operator++(int)
        {
            random_access_iterator other(*this);
            operator++();
            return (other);
        }
        random_access_iterator& operator--(void)
        {
            _i--;
            return *this;
        }
        random_access_iterator operator--(int)
        {
            random_access_iterator other(*this);
            operator--();
            return (other);
        }
        random_access_iterator &operator+(difference_type n) { return (_i + n); } const
        random_access_iterator &operator+=(difference_type n)
        {
            _i += n;
            return *this;
        }
        random_access_iterator &operator-(difference_type n) { return (_i - n); } const
        random_access_iterator &operator-=(difference_type n)
        {
            _i -= n;
            return *this;
        }
        reference operator[] (difference_type n) { return *(operator+(n)); }

        private:
            pointer _i;
    };
    // ==, !=, <, >  부터 해서 또 뭐 많을것 같음

}

#endif //FT_CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
