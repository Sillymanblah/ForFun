#pragma once
#ifndef MATRIX_TEMPLATE_HPP
#define MATRIX_TEMPLATE_HPP

#include <stdint.h>
#include <type_traits>
#include <utility>
#include <iostream>

// Creating a derived float variable based on the floats defined to be used by the system.
#if defined(USER_FLOATS) && defined(UNIQUE_FLOATS)
#define DERIVED_FLOATS USER_FLOATS, UNIQUE_FLOATS
#elif defined(USER_FLOATS) // && !defined(UNIQUE_FLOATS)
#define DERIVED_FLOATS USER_FLOATS
#elif defined(UNIQUE_FLOATS) // && !defined(USER_FLOATS)
#define DERIVED_FLOATS UNIQUE_FLOATS
#endif

#ifndef _STD
#define _STD ::std::
#endif // _STD

template <class _Ty, class... _Types> // true if and only if _Ty is in _Types
inline constexpr bool _Is_any_of_v = _STD disjunction_v< _STD is_same< _Ty, _Types >... >;

template < class _Ty >
class _matrix_operators;

template < class _Ty >
struct storage_type // For finding which size type we should use for the matrix class
{
    using type = _Ty;
};

// Type definitions for our size types that we can use and call ::type for each.
typedef storage_type< void > size_void;
typedef storage_type< uint8_t > size_uint8;
typedef storage_type< uint16_t > size_uint16;
typedef storage_type< uint32_t > size_uint32;
typedef storage_type< uint64_t > size_uint64;

template < class _Ty, _Ty, _Ty >
inline constexpr bool same_value_v = false;
template < class _Ty, _Ty _Value >
inline constexpr bool same_value_v< _Ty, _Value, _Value > = true;

template < class _Ty, _Ty _Value_1, _Ty _Value_2 >
struct same_num : _STD bool_constant< same_value_v< _Ty, _Value_1, _Value_2 > > {};

template < class _Base_Ty, _Base_Ty _Value, class _Cast_Ty >
struct is_castable
{
    static constexpr bool value = same_value_v< _Base_Ty, _Value, (_Base_Ty)( (_Cast_Ty)(_Value) ) >;
    using type = _Cast_Ty;
};

template < class _Base_Ty, _Base_Ty _Size, class... _Size_Types >
struct _Min_Cast
{   // Some things to note here, disjunction returns a type based on the struct inside (is_castable).
    // is_castable::type is _Cast_Ty, so disjunction::type is the storage_type of the first successfully castable _Size_Ty in _Size_Types.
    using type = typename _STD disjunction< is_castable< _Base_Ty, _Size, _Size_Types >... >::type;
};

template < size_t _Size >
struct min_int_cast : _Min_Cast< size_t, _Size, uint8_t, uint16_t, uint32_t, uint64_t > {};

template < size_t _Size >
using min_int_cast_t = typename min_int_cast<_Size>::type;

// Getting the maximum size integer from a set of integer types.
template < class _Size_1, class _Size_2 >
struct max_of : storage_type<_Size_1> {}; // If the first is bigger, grab it.

// All the cases where the second is bigger:
template < class _Size >
struct max_of< uint8_t, _Size > : storage_type<_Size> {}; // Can handle 8 vs 16, 8 vs 32, & 8 vs 64
template < class _Size >
struct max_of< _Size, uint64_t > : size_uint64 {}; // Handles for 16 vs 64 & 32 vs 64
template <>
struct max_of< uint16_t, uint32_t > : size_uint32 {}; // Last case is the 16 vs 32
// The rest are handled by the base class.

// Type of the maximum int in a pair.
template < class _Size_1, class _Size_2 >
using max_of_t = typename max_of< _Size_1, _Size_2 >::type;

template < class _Largest, class... _Rest >
struct _Max_size // Rest is empty, so largest is our max.
{
    using type = _Largest;
};

template < class _Largest, class _First, class... _Rest >
struct _Max_size< _Largest, _First, _Rest... > // Rest contains at least one element, so pull it out and check size.
{
    using type = typename _Max_size< max_of_t< _Largest, _First >, _Rest... >::type;
};

template < class... _Size_Types > // Finding the max size of of a type set.
struct max_size : size_void {}; // If no sizes are sent.

template < class _First, class... _Rest > // Any other amount of sizes were sent.
struct max_size< _First, _Rest... > : _Max_size< _First, _Rest... > {};

template < class... _Size_Types >
using max_size_t = typename max_size< _Size_Types... >::type;

template < size_t... _Sizes >
struct group_min_int_cast : max_size< min_int_cast_t<_Sizes>... > {};

template < size_t... _Sizes >
using group_min_int_cast_t = typename group_min_int_cast<_Sizes...>::type;

#if defined(DERIVED_FLOATS)
template < class _Ty >
inline constexpr bool is_floating_derived_v = _Is_any_of_v< _Ty, DERIVED_FLOATS >;
#else // ^^^ defined(DERIVED_FLOATS) / !defined(DERIVED_FLOATS) vvv
template < class _Ty >
inline constexpr bool is_floating_derived_v = false;
#endif // ^^^ !defined(DERIVED_FLOATS)

template < class _Ty >
inline constexpr bool is_multiplicative_invertible_v = _STD is_floating_point_v<_Ty> || is_floating_derived_v<_Ty>;

template < class _Ty >  
struct is_multiplicative_invertible : _STD bool_constant< is_multiplicative_invertible_v<_Ty> > {};

template < class _Ty, class _Size_Ty, _Size_Ty _Dim_X, _Size_Ty _Dim_Y >
class _matrix
{
    protected:
        using type = _Ty;
        using size = _Size_Ty;

        size __width = _Dim_X;
        size __length = _Dim_Y;
        type** __matrix = nullptr;

        void build( type& _default )
        {
            __matrix = new type*[__width];
            for ( size col_pos = 0; col_pos < __width; col_pos )
                __matrix[col_pos] = new type[__length]{_default};
        }
        void build( type&& _default )
        {
            __matrix = new type*[__width];
            for ( size col_pos = 0; col_pos < __width; col_pos )
                __matrix[col_pos] = new type[__length]{_default};
        }
        void destroy()
        {
            for ( size col_pos = 0; col_pos < __width; col_pos++ )
                delete [] __matrix[col_pos];
            delete [] __matrix;
        }
    
    public:
        type& at( size _x_pos, size _y_pos )
        {
            return __matrix[_x_pos][_y_pos];
        }
        const type& get( size _x_pos, size _y_pos )
        {
            return __matrix[_x_pos][_y_pos];
        }
};

template < class _Ty, uint8_t _Dim_X, uint8_t _Dim_Y >
class _matrix< _Ty, uint8_t, _Dim_X, _Dim_Y >
{
    protected:
        using type = _Ty;
        using size = uint8_t;

        size __width = _Dim_X;
        size __length = _Dim_Y;
        type* __matrix = nullptr;

        void build( type& _default )
        {
            __matrix = new type[ __width * __length ]{_default};
        }
        void build( type&& _default )
        {
            __matrix = new type[ __width * __length ]{_default};
        }
        void destroy()
        {
            delete [] __matrix;
        }
    
    public:
        type& at( size _x_pos, size _y_pos )
        {
            return __matrix[ _x_pos + (this->__width * _y_pos) ];
        }
        const type& get( size _x_pos, size _y_pos ) const
        {
            return __matrix[ _x_pos + (this->__width * _y_pos) ];
        }
};

template < class _Ty, class _Size_Ty, _Size_Ty _Dim_X, _Size_Ty _Dim_Y >
class _matrix_base : public _matrix< _Ty, _Size_Ty, _Dim_X, _Dim_Y >
{
    static_assert( _STD is_arithmetic_v<_Ty>, "_Ty must be an arithmetic type." );

    private:
        using super = _matrix< _Ty, _Size_Ty, _Dim_X, _Dim_Y >;
        using type = _Ty;
        using size = _Size_Ty;

        void copy_data( const _matrix_base& _other )
        {
            for ( size _x_pos = 0; _x_pos < this->__width; _x_pos++ )
                for ( size _y_pos = 0; _y_pos < this->__length; _y_pos++ )
                    this->at( _x_pos, _y_pos ) = _other.get( _x_pos, _y_pos );
        }

    public:
        // Might relocate these constructors to the derived matrix class.
        _matrix_base( type& _default )
        {
            this->build( _STD forward<type>(_default) );
        }
        _matrix_base( type&& _default )
        {
            this->build( _STD forward<type>(_default) );
        }
        _matrix_base( const _matrix_base& _other ) : _matrix_base(0)
        {
            this->copy_data( _other );
        }
        ~_matrix_base()
        {
            this->destroy();
        }

        friend _STD ostream& operator<< ( _STD ostream& _stream, const _matrix_base& _printable )
        {
            for ( size _x_pos = 0; _x_pos < _printable.__width; _x_pos++ )
            {
                for ( size _y_pos = 0; _y_pos < _printable.__length; _y_pos++ )
                    _stream << _printable.get( _x_pos, _y_pos ) << " ";
                _stream << "\n";
            }
            return _stream;
        }

        _matrix_base operator+( const _matrix_base& _other )
        {
            _matrix_base storage(0);

            for ( size _x_pos = 0; _x_pos < this->__length; _x_pos++ )
                for ( size _y_pos = 0; _y_pos < this->__length; _y_pos++ )
                    storage.at( _x_pos, _y_pos ) = this->get( _x_pos, _y_pos ) + _other.get( _x_pos, _y_pos );

            return storage;
        }
        _matrix_base& operator+=( const _matrix_base& _other )
        {
            for ( size _x_pos = 0; _x_pos < this->__width; _x_pos++ )
                for ( size _y_pos = 0; _y_pos < this->__length; _y_pos++ )
                    this->at( _x_pos, _y_pos ) += _other.get( _x_pos, _y_pos );

            return *this;
        }

    protected:
        template < class _Other_Size_Ty, _Other_Size_Ty _Other_Dim_X, _Other_Size_Ty _Other_Dim_Y >
        _STD enable_if< same_value_v< size_t, _Dim_Y, _Other_Dim_X >,
        _matrix_base< _Ty, max_of_t< _Size_Ty, _Other_Size_Ty >, _Dim_X, _Other_Dim_Y > >
        operator*( const _matrix_base< _Ty, _Other_Size_Ty, _Other_Dim_X, _Other_Dim_Y >& _other )
        {
            _matrix_base< _Ty, max_of_t< _Size_Ty, _Other_Size_Ty >, _Dim_X, _Other_Dim_Y > resulting;

            for ( size_t _x_pos = 0; _x_pos < _Dim_X; _x_pos++ )
                for ( size_t _y_pos = 0; _y_pos < _Other_Dim_Y; _y_pos++ )
                    for ( size_t _multiplied = 0; _multiplied < _Dim_Y; _multiplied++ )
                        resulting.at( _x_pos, _y_pos ) += this->get( _x_pos, _multiplied ) * _other.get( _multiplied, _y_pos );

            return resulting;
        }
};

template < class _Ty, size_t _Length, size_t _Width >
class matrix : public _matrix_base< _Ty, group_min_int_cast_t< _Length, _Width >, _Length, _Width > // Standard matrix implementation.
{
    private:
        using super = _matrix_base< _Ty, group_min_int_cast_t< _Length, _Width >, _Length, _Width >;
        using size = typename super::size;
        using type = _Ty;

    public:
        matrix() : super( 0 ) {}
        matrix( type& _default ) : super( _STD forward<type>(_default) ) {}
        matrix( type&& _default ) : super( _STD forward<type>(_default) ) {}

};

template < class _Ty, size_t _Size >
class matrix< _Ty, _Size, _Size > : public _matrix_base< _Ty, min_int_cast_t<_Size>, _Size, _Size > // Overloaded matrix for square matrices (allows computation of the determinant and diagonalizability).
{
    private:
        using super = _matrix_base< _Ty, min_int_cast_t<_Size>, _Size, _Size >;
        using size = min_int_cast_t< _Size >;
        using type = _Ty;

    public:
        matrix() : super( 0 ) {}
        matrix( type& _default ) : super( _STD forward<type>(_default) ) {}
        matrix( type&& _default ) : super( _STD forward<type>(_default) ) {}

        matrix& operator*=( const matrix& _other )
        {
            *this = *this * _other;
        }
};

template < class _Ty, size_t _Size >
using square_matrix = matrix< _Ty, _Size, _Size >;

template < class _Ty, size_t _Size >
class matrix< _STD enable_if< is_multiplicative_invertible_v<_Ty>, _Ty >, _Size, _Size > :
public _matrix_base< _Ty, min_int_cast_t<_Size>, _Size, _Size >
{
    private:
        using super = _matrix_base< _Ty, min_int_cast_t< _Size >, _Size, _Size >;
        using size = min_int_cast_t< _Size >;
        using type = _Ty;

    public:
        matrix() : super( 0 ) {}
        matrix( type& _default ) : super( _STD forward<type>(_default) ) {}
        matrix( type&& _default ) : super( _STD forward<type>(_default) ) {}

        void orthogonalize()
        {

        }
        void diagonalize()
        {
            
        }
};

#endif // MATRIX_TEMPLATE_HPP