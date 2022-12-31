//
// Created by Jinwoo Lee on 12/15/22.
//

#ifndef FT_CONTAINERS_PAIR_HPP
#define FT_CONTAINERS_PAIR_HPP

/*
 * std::pair
 * make_pair()
 *
 *
 * std::pair
 * https://en.cppreference.com/w/cpp/utility/pair
 * https://cplusplus.com/reference/utility/pair/pair/
 * 그냥 두 개의 다른 종류로 이루어진 객체들을 하나의 단위로 묶는 클래스 템플릿이다. std::tuple인데, 2개만 있는거
 * T1과 T2가 있는 간단한 구조체다. gcc stl_pair.h에 정의되어 있다.
 * https://en.cppreference.com/w/cpp/utility/piecewise_construct
 */

namespace ft {
    template<class _T1, class _T2>
    struct pair {
        typedef _T1 first_type;
        typedef _T2 second_type;

        _T1 first; //first, second object의 copy들
        _T2 second;

        pair() : first(), second() {} //1. 기본 생성자

        pair(const _T1 &__a, const _T2 &__b) : first(__a), second(__b) {} //2. 복사생성자
        //first는 a로 생성되고, second는 b로 생성된다. 새로 생성자가 작동하지 않으면 슬픈 일이 일어날수도 있다.

        template<class _U1, class _U2>
        pair(const pair<_U1, _U2> &__pr) : first(__pr.first), second(__pr.second) {}
        //2. 그냥 pair를 때려박았을때도 처리해야지
    };
    // ==
    template<class _T1, class _T2>
    bool operator==(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y) {
        return __x.first == __y.first && __x.second == __y.secondl;
    }

    // !=
    template <class _T1, class _T2>
    bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
        return !(__x == __y);
    }

    // <
    template<class _T1, class _T2>
    bool operator<(const pair<_T1, _T2> &__x, const pair<_T1, _T2> &__y)
    {
        return __x.first < __y.first ||
               (!(__y.first < __x.first) && __x.second < __y.second);
    }
    // <=
    template <class _T1, class _T2>
    bool operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
        return !(__y < __x);
    }

    // >
    template <class _T1, class _T2>
    bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
        return __y < __x;
    }
    // >=
    template <class _T1, class _T2>
    bool operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
        return !(__x < __y);
    }

    /*
     * make pair
     * https://cplusplus.com/reference/utility/make_pair/?kw=make_pair
     * stl_pair.h 140줄부터
     * pair를 만드는 템플릿.
     */
    template <class _T1, class _T2>
    pair<_T1, _T2> make_pair(_T1 x, _T2 y)
    {
        return (pair<_T1, _T2> (x, y));
    }
}


#endif //FT_CONTAINERS_PAIR_HPP
