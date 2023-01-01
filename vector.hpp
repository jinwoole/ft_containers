//
// Created by Jinwoo Lee on 12/20/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory> //std::allocator
#include "type_traits.hpp"
#include "reverse_iterator.hpp"


/*
 * 1. Vector class

 */

namespace ft
{
/*
 * 2. vector base class(삭제, 비표준)
 * https://cplusplus.com/reference/vector/vector/?kw=vector
 * 백터는 가변인자배열이다. 용량을 변화시킬땐 재할당 해야한다. gcc 소스코드는 벡터 베이스 클래스를 만들어 할당과 재할당을 처리하는 역할을 맡긴다.
 * 이걸 그냥 벡터 클래스에 다 때려박으면 상관 없나 싶었지만, 만약 재할당 상황 등에서 벡터 생성자에서 할당오류가 발생하면 소멸자가 호출되지 않고,
 * 그냥 끝난다. 하지만 벡터 베이스 클래스가 있으면, 벡터 베이스 클래스의 소멸자가 안전하게 호출되어 try catch로 깔끔하게 처리할 수 있다.
 */

/*
 * 1. Vector class
 * 벡터는 sequence container다.
 * https://cplusplus.com/reference/vector/vector/?kw=vector
 * https://en.cppreference.com/w/cpp/memory/allocator
 */
template < class T, class Alloc = std::allocator<T> >
class vector
{
    //Template parameters T, Allocator
    typedef T       value_type;
    typedef Alloc   allocator_type;

    /*
     * size_type과 difference_type의 차이
     * 사실 그냥 unsigned int와 signed int다. size_type은 보통 std::size_t로 구현되고,
     * difference_type은 std::ptrdiff_t로 구현된다.
     * alloc에서 이걸 받아와서, 메모리 할당을 유연하게 하기 위한 목적으로 쓴다.
     */
    typedef typename allocator_type::size_type          size_type;
    typedef typename allocator_type::difference_type    difference_type;

    /*
     * 그냥 allocator로 할당된 지점을 가리키는 친구들.
     * T*, T&, const T* 같이 생겨서 역시 유연하게 쓸 수 있다.
     */
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference          const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;

    //이제 random_access_iterator만들어야함

};



}

#endif //FT_CONTAINERS_VECTOR_HPP
