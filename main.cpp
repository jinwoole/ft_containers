#include <iostream>
#include <vector>
#include "./type_traits.hpp"
#include "./reverse_iterator.hpp"
//enable_if test
template<typename T, typename ft::enable_if<ft::is_integral<T>::value, int>::type = 0>
void foo(void) { std::cout << "true\n"; }

//integral_constant test
template <unsigned n>
struct factorial : ft::integral_constant<int,n * factorial<n-1>::value> {};
template <>
struct factorial<0> : ft::integral_constant<int,1> {};

//reverse_iterator test
void test_reverse_iterator()
{
    int __flag = 0;
    // Create a vector of integers
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    // Create a reverse iterator pointing to the last element in the vector
    ft::reverse_iterator<std::vector<int>::iterator> rit(v.end());
    // Check if the reverse iterator is pointing to the last element in the vector
    if (*rit != 5) {
        std::cout << "Unexpected value at reverse iterator: expected 5, got " << *rit << std::endl;
        __flag == 1;
    }
    // Check if the reverse iterator can be incremented and still point to the correct element
    ++rit;
    if (*rit != 4) {
        std::cout << "Unexpected value at reverse iterator after increment: expected 4, got " << *rit << std::endl;
        __flag == 1;
    }
    // Check if the reverse iterator can be decremented and still point to the correct element
    --rit;
    if (*rit != 5) {
        std::cout << "Unexpected value at reverse iterator after decrement: expected 5, got " << *rit << std::endl;
        __flag == 1;
    }
    if (__flag == 0)
        std::cout << "test passed\n";
}


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
    std::cout << factorial<5>::value << std::endl;

    //reverse_iterator test
    std::cout << "[reverse_iterator test]" << std::endl;
    test_reverse_iterator();
}
