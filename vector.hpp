//
// Created by Jinwoo Lee on 12/20/22.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "type_traits.hpp"
/*
 * 1. Vector class
 * 2. vector base class
 */

namespace ft
{


/*
 * 2. vector base class
 * https://cplusplus.com/reference/vector/vector/?kw=vector
 * 백터는 가변인자배열이다. 용량을 변화시킬땐 재할당 해야한다. gcc 소스코드는 벡터 베이스 클래스를 만들어 할당과 재할당을 처리하는 역할을 맡긴다.
 * 이걸 그냥 벡터 클래스에 다 때려박으면 상관 없나 싶었지만, 만약 재할당 상황 등에서 벡터 생성자에서 할당오류가 발생하면 소멸자가 호출되지 않고,
 * 그냥 끝난다. 하지만 벡터 베이스 클래스가 있으면, 벡터 베이스 클래스의 소멸자가 안전하게 호출되어 try catch로 깔끔하게 처리할 수 있다.
 */
    template <class _T, class _alloc>
    struct _vector_base
        : public _vector_alloc_base<_T, _alloc, _A
    {

    };




/*
 * 1. Vector class
 *
 */
template <class _T, class _alloc = std::allocator<_T> >
class vector
        : protected _vector_base<_T, _alloc>
{

}

}

#endif //FT_CONTAINERS_VECTOR_HPP
