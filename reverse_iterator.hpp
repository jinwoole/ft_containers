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
     * stl_iterator.h 66번줄에 있다. 레퍼런스는 큰 도움 안된다. 코드를 보자.
     */
    template <typename Iterator>
    class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, \
                                                typename ft::iterator_traits<Iterator>::value_type, \
                                                typename ft::iterator_traits<Iterator>::difference_type, \
                                                typename ft::iterator_traits<Iterator>::pointer, \
                                                typename ft::iterator_traits<Iterator>::reference>
    {
    private:
        Iterator current;

    public:
        typedef Iterator                                                   iterator_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type    difference_type;
        typedef typename ft::iterator_traits<Iterator>::reference          reference;
        typedef typename ft::iterator_traits<Iterator>::pointer            pointer;


        /* Constructor of reverse_iterator
         * https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
         * 1. default constructor       -> 아무 객체도 가리키지 않는 리버스 이터레이터를 만든다.
         * 2. initalization constructor -> 원본 iterator it에서부터, 리버스 이터레이터를 만든다. 거꾸로 돌아간다는거 말곤, 원본과 똑같이 행동한다.
         * explicit reverse_iterator (iterator_type it)
         * 3. copy/type-cast constructor
         * 다른 리버스 이터레이터로부터 이터레이터를 만들고, 인자로 받은 것과 당연히 같아야지
         * template <class Iter> reverse_iterator (const reverse_iterator<Iter>& rev_it);
         */
        iterator_type base() const { return current; } //아래에서  쓰인다

        reverse_iterator() {}
        explicit reverse_iterator(iterator_type __x) : current(__x) {}
        reverse_iterator(const reverse_iterator& __x) : current(__x) { }

        template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) {}


        //연산자 오버라이드
        reference operator*() const
        {
            Iterator __tmp = current;
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

        //어디 써놓은것 같은데... 아무튼 difference_type은 두 이터레이터 차이 나타내는 타입이고, 사실상 그냥 ptrdiff다.
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
