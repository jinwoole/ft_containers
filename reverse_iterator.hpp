//
// Created by Jinwoo Lee on 12/16/22.
//

#ifndef FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterator_base.hpp"

namespace ft
{
    /*
     * reverse_iterator
     * https://en.cppreference.com/w/cpp/iterator/reverse_iterator
     * bidirectional iterator와 똑같은데, 거꾸로 한거다.
     * stl_iterator.h 66번줄에 있다. 레퍼런스는 뭐 이상하게 생겼다.
     * iterator base에서 상속받는데, 그 속성은 iterator_traits에서 받아온다.
     * 그냥 포인터 연산을 잘 해주면 된다.
     */
    template <typename _Iterator>
    class reverse_iterator : public ft::iterator<typename ft::iterator_traits<_Iterator>::iterator_category, \
                                                typename ft::iterator_traits<_Iterator>::value_type, \
                                                typename ft::iterator_traits<_Iterator>::difference_type, \
                                                typename ft::iterator_traits<_Iterator>::pointer, \
                                                typename ft::iterator_traits<_Iterator>::reference>
    {
    private:
        _Iterator current;

    public:
        typedef _Iterator                                                   iterator_type;
        typedef typename ft::iterator_traits<_Iterator>::difference_type    difference_type;
        typedef typename ft::iterator_traits<_Iterator>::reference          reference;
        typedef typename ft::iterator_traits<_Iterator>::pointer            pointer;


        /* Constructor of reverse_iterator
         * https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
         * 1. default constructor       -> 아무 객체도 가리키지 않는 리버스 이터레이터를 만든다.
         * 2. initalization constructor -> 원본 iterator it에서부터, 리버스 이터레이터를 만든다. 거꾸로 돌아간다는거 말곤, 원본과 똑같이 행동한다.
         * explicit reverse_iterator (iterator_type it)
         * 3. copy/type-cast constructor
         * 다른 리버스 이터레이터로부터 이터레이터를 만들고, 인자로 받은 것과 당연히 같아야지
         * template <class Iter> reverse_iterator (const reverse_iterator<Iter>& rev_it);
         */
        reverse_iterator() {}
        explicit reverse_iterator(iterator_type __x) : current(__x) {}
        reverse_iterator(const reverse_iterator& __x) : current(__x) { }
        template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) {}

        iterator_type base() const { return current; } //아래에서 쓰인다

        //연산자 오버라이드
        reference operator*() const
        {
            _Iterator __tmp = current;
            return *(--__tmp);
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reverse_iterator& operator++()
        {
            --current;
            return *this;
        }

        reverse_iterator& operator--()
        {
            ++current;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator __tmp = *this;
            ++current;
            return __tmp;
        }

        reverse_iterator operator+(difference_type __n) const
        {
            return reverse_iterator(current - __n);
        }

        reverse_iterator& operator+=(difference_type __n)
        {
            current -= __n;
            return *this;
        }

        reverse_iterator operator-(difference_type __n) const
        {
            return reverse_iterator(current + __n);
        }

        reverse_iterator& operator-=(difference_type __n)
        {
            current += __n;
            return *this;
        }

        reference operator[](difference_type __n) const
        {
            return *(*this + __n);
        }
    };


}

#endif
