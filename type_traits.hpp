/*
 * Created by Jinwoo Lee on 12/15/22.
 * 1. enable_if
 * 2. is_integral
*/

#include <type_traits>

#ifndef FT_CONTAINERS_ENABLE_IF_HPP
#define FT_CONTAINERS_ENABLE_IF_HPP

namespace ft {
    /* 1. enable_if
     * enable_if로 SFINAE가 가능해진다.
     * https://cplusplus.com/reference/type_traits/enable_if/?kw=enable_if
     * 템플릿 첫번째 인자로 true가 오면, enable_if 구조체 안에서 type라는 자료형이 생긴다.
     * 따라서, template의 첫번째 인자로 boolean을 반환하게 하는 구문을 넣어놓고, 해당 구문에서 판별을 요청하면
     * 결과값에 따라 type이 생기거나, 생기지 않는다. 이를 이용한 것
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
     *얘도 traits class다. 뭐냐면 그냥 T로 들어온게 integral인지 아닌지 알려준다. 근데,
     * bool, char, int, long int, unsigned char, unsigned long long int 등등 죄다 integral로 친다고 한다.
     * 아무튼 템플릿 특수화로 구현될 수 밖에 없다. 저걸 다 체크해야하니깐. 총 15개다. 그래서 자료형별로 특수화되어있고,
     * false_type과 true_type을 상속받는 빈 구조체다. llvm type_traits 738번째 줄부터 보니깐 뭐가 많다.
     */


    /*
    * 2.1 integral_constant
    * https://cplusplus.com/reference/type_traits/integral_constant/
    * 이거 또 어떻게 생겨먹었나 하니깐, 대충 베이스가 되는건 integral_constant인지 뭔지 있다. 431번줄에 있다.
    * 원본 함수는 constexpr이 있지만, c++ 11부터 나온거라 못쓴다. 그냥 const붙여도 될 것 같긴 한데, 뭐 어차피 못바꾼다
     * T는 integral constant의 타입이다. v는 integral constant의 값이다.
     * constexpr을 못쓰므로 compile-time int type은 제공 못해주지만, 뭐 별 문제는 없을것같다.
     * 쭉 보니 is 계열 템플릿 특수화들의 베이스가 되어준다. 근데 이게 필요한가?
    */

    //오류 리포트 : T value = v 식으로 초기화하는건 c++11에서만 된다. 그래서 억지로 해주기 위해 static 붙이면 된다
    template<class T, T v>
    struct integral_constant {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator T() { return v; }
    };
    //템플릿 연산에서 true와 false를 정의할 수 있다. 소스코드 읽으니 맞는것 같긴 한데 이게 맞나 싶기도 하고
    //일단 이거 작성하고 테스트 돌려보자
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