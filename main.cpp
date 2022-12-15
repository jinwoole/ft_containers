#include <iostream>
#include <type_traits>
#include "./type_traits.hpp"

//enable_if test
template<typename T, typename ft::enable_if<ft::is_integral<T>::value, int>::type = 0>
void foo(void) { std::cout << "true\n"; }

//integral_constant test
template <unsigned n>
struct factorial : ft::integral_constant<int,n * factorial<n-1>::value> {};

template <>
struct factorial<0> : ft::integral_constant<int,1> {};


int main() {


    //enable_if test
    std::cout << "[enable_if test]" << std::endl;
    foo<char>();
    foo<int>();
    //foo<float>();은 컴파일 오류가 난다. 왜냐하면 integral계열이 아니면, enable_if가 이건 적합하지 않다고 판단, 인스턴스화하지 않기 때문이다.

    // is_integral test
    std::cout << std::boolalpha;
    std::cout << "[is_integral test]" << std::endl;
    std::cout << "char: " << ft::is_integral<char>::value << std::endl;
    std::cout << "int: " << ft::is_integral<int>::value << std::endl;
    std::cout << "float: " << ft::is_integral<float>::value << std::endl;

    //integral_constant test
    std::cout << "[Integral_constant test]" << std::endl;
    std::cout << factorial<5>::value;
    return 0;
}
