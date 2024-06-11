#pragma once
#ifndef INPUTS_HPP
#define INPUTS_HPP

#include "core.hpp"

#include <vector>
#include <type_traits>
#include <istream>

_BEGIN_PROJB
    template < class _Elem, class _Ty >
    _Ty readData( std::basic_istream<_Elem>& input, std::basic_istream<_Elem>& (*reader)( std::basic_istream<_Elem>&, _Ty& ) );

    template < class _Elem, class _Ty >
    _Ty readValidatedData( std::basic_istream<_Elem>& input, _Ty (*validate)(_Ty),
        std::basic_istream<_Elem>& (*reader)( std::basic_istream<_Elem>&, _Ty& ) );

    template < class _Elem, class _Ty >
    _Ty printData( std::basic_ostream<_Elem>& output, std::basic_ostream<_Elem>& (*printer)( std::basic_ostream<_Elem>&, const _Ty& ) );

_END_PROJB


#endif // INPUTS_HPP