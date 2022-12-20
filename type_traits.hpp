/*
 * Created by Jinwoo Lee on 12/15/22.
 * 1. enable_if
 * 2. is_integral
*/
#ifndef FT_CONTAINERS_ENABLE_IF_HPP
#define FT_CONTAINERS_ENABLE_IF_HPP

namespace ft {
    /* 1. enable_if
     * enable_if로 SFINAE가 가능해진다.
     * https://cplusplus.com/reference/type_traits/enable_if/?kw=enable_if
     * type T는 bool B가 true일때, enable_if::의 멤버 타입이 된다. false면, enable_if::type은 정의되지 않는다.
     * 컴파일 타임 와중에 조건문처럼 작동하게 해준다.
     */

    template<bool B, class T = void>
    struct enable_if {
    };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    /* 2. is_integral
     * https://cplusplus.com/reference/type_traits/is_integral/?kw=is_integral
     * https://en.cppreference.com/w/cpp/types/is_integral
     * 얘도 traits class다. 뭐냐면 그냥 T로 들어온게 integral인지 아닌지 알려준다. 근데,
     * bool, char, int, long int, unsigned char, unsigned long long int 등등 죄다 integral로 친다고 한다.
     * 아무튼 템플릿 특수화로 구현될 수 밖에 없다. 저걸 다 체크해야하니깐. 총 15개다. 그래서 자료형별로 특수화되어있고,
     * false_type과 true_type을 상속받는 빈 구조체다. llvm type_traits 738번째 줄부터 보니깐 뭐가 많다.
     */

    /*
    * 2.1 integral_constant
    * https://cplusplus.com/reference/type_traits/integral_constant/
    * 이거 또 어떻게 생겨먹었나 하니깐, 대충 베이스가 되는건 integral_constant인지 뭔지 있다. 431번줄에 있다.
    * 원본 함수는 constexpr이 있지만, c++ 11부터 나온거라 못쓴다.
     * T는 integral constant의 타입이다. v는 integral constant의 값이다.
    */

    template<class T, T v>
    struct integral_constant {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator T() { return v; }
    };
    //템플릿 연산에서 true와 false를 정의할 수 있다.
    typedef integral_constant<bool, true>   true_type;
    typedef integral_constant<bool, false>  false_type;

    template <class T>      struct is_integral_check                    : public false_type {};
    template <>      struct is_integral_check<bool>                     : public true_type {};
    template <>      struct is_integral_check<char>                     : public true_type {};
    template <>      struct is_integral_check<char16_t>                 : public true_type {};
    template <>      struct is_integral_check<char32_t>                 : public true_type {};
    template <>      struct is_integral_check<wchar_t>                  : public true_type {};
    template <>      struct is_integral_check<signed char>              : public true_type {};
    template <>      struct is_integral_check<short int>                : public true_type {};
    template <>      struct is_integral_check<int>                      : public true_type {};
    template <>      struct is_integral_check<long int>                 : public true_type {};
    template <>      struct is_integral_check<long long int>            : public true_type {};
    template <>      struct is_integral_check<unsigned char>            : public true_type {};
    template <>      struct is_integral_check<unsigned short int>       : public true_type {};
    template <>      struct is_integral_check<unsigned int>             : public true_type {};
    template <>      struct is_integral_check<unsigned long int>        : public true_type {};
    template <>      struct is_integral_check<unsigned long long int>   : public true_type {};

    //완성!
    template <class T> struct is_integral : public is_integral_check<T> {};
}
#endif //FT_CONTAINERS_ENABLE_IF_HPP