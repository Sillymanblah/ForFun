#pragma once
#ifndef SPECIALIZED_ARITHMETIC_HPP
#define SPECIALIZED_ARITHMETIC_HPP

#include <type_traits>
#include "complex.hpp"

#define _SPEC ::spec::
#ifndef _STD
#define _STD ::std::
#endif // _STD
#ifndef _CSTD
#define _CSTD ::
#endif // _CSTD

namespace spec {

// Moved here so I can use it :/
template <class _Ty, class... _Types>
inline constexpr bool _Is_any_of_v = // true if and only if _Ty is in _Types
    _STD disjunction_v< _STD is_same< _Ty, _Types >... >;

template < class _Ty >
inline constexpr bool is_arithmetic_v = 
#if defined( ALT_ARITHMETIC )
    _SPEC _Is_any_of_v< _Ty, ALT_ARITHMETIC > || 
#endif // defined( ALT_ARITHMETIC )
    _STD is_arithmetic_v<_Ty>;

template < class _Ty >
struct is_arithmetic : _STD bool_constant< _SPEC is_arithmetic_v<_Ty> > {};

}; // namespace spec

#endif // SPECIALIZED_ARITHMETIC_HPP