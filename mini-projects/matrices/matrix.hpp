#pragma once
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stdint.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "specialized_arithmetic.hpp"

template <typename _Num>
uint8_t get_width( const _Num& _number, uint8_t _precision )
{
    _STD string temp(_number);
    return __min( (uint8_t) temp.size(), (uint8_t) temp.find('.') + _precision );
}

class _floating
{
    private:
        uint8_t _precision;
    public:
        void set_precision( uint8_t precision )
        {
            _precision = precision;
        }
};

class _integral {};

template <bool _Test, typename _Ty>
struct allow_if { using type = void; };
template <typename _Ty>
struct allow_if<true, _Ty> { using type = _Ty; };
template <bool _Test, typename _Ty>
using allow_if_t = typename allow_if<_Test, _Ty>::type;

template <typename _Num>
class square_matrix : _STD conditional< _STD is_floating_point_v<_Num>, _floating, _integral >
{
    static_assert( _SPEC is_arithmetic_v<_Num>, "_Num must be an arithmetic type." );

    private:
        _Num** _matrix;
        uint16_t _size;
        uint8_t _precision = 0;
        void copy_data( const square_matrix& _other )
        {
            for ( uint16_t y = 0; y < _other._size; y++ )
                for( uint16_t x = 0; x < _other._size; x++ )
                    this->at(x,y) = _other.at(x,y);
        }
        void build( uint16_t _size, const _Num _value )
        {
            _matrix = new _Num*[_size];
            for ( uint16_t i = 0; i < _size; i++ )
            {
                _matrix[i] = new _Num[_size]{_value}; // Builds a matrix initialized to _value.
            }
        }
        void destroy()
        {
            for ( uint16_t i = 0; i < _size; i++ )
            {
                delete [] _matrix[i];
            }
            delete [] _matrix;
        }
        void copy( const square_matrix& _other )
        {
            if ( this->_matrix )
                this->destroy();
            
            this->build(_other._size);
            this->copy_data(_other);
        }
        void compare_size( const square_matrix& _other)
        {
            if ( _other._size != this->_size )
                throw _STD invalid_argument( "Size of the matrices do not match." );
        }
        uint8_t col_width( const uint16_t& _column )
        {
            uint8_t max_width;
            for ( uint16_t pos = 0; pos < this->_size; pos++ )
            {
                max_width = __max( max_width, get_width( this->_matrix.at(_column, pos), this->_precision ) );
            }
            return max_width;
        }

    public:
        square_matrix() : _matrix(nullptr), _size(0) {};
        square_matrix( const uint16_t& __size, const _Num _value = 0 ) : _matrix(nullptr), _size(__size)
        {
            this->build(_size);
        }
        square_matrix( const square_matrix& _other ) : square_matrix()
        {
            this->copy(_other);
        }

        ~square_matrix()
        {
            this->destroy();
        }

        _Num& at( const uint16_t& _x_pos, const uint16_t& _y_pos )
        {
            return this->_matrix[_x_pos][_y_pos];
        }
        _Num& at( const uint16_t&& _x_pos, const uint16_t&& _y_pos )
        {
            return this->_matrix[_x_pos][_y_pos];
        }

        square_matrix& operator=( const square_matrix& _other )
        {
            this->copy(_other);
            return *this;
        }
        square_matrix operator+( const square_matrix& _other )
        {
            this->compare_size(_other);

            square_matrix temp( this->_size );
            for ( uint16_t y = 0; y < this->_size; y++ )
                for ( uint16_t x = 0; x < this->_size; x++ )
                {
                    temp._matrix[x][y] = this->_matrix[x][y] + _other._matrix[x][y];
                }
        }
        square_matrix operator*( const square_matrix& _other )
        {
            this->compare_size(_other);

            square_matrix temp(_other._size);
            for ( uint16_t y = 0; y < this->_size; y++ )
                for ( uint16_t x = 0; x < this->size; x++ )
                    for ( uint16_t pos = 0; pos < this->_size; pos++ )
                    {
                        temp._matrix[x][y] += this->_matrix[pos][y] * _other._matrix[x][pos];
                    }
        }
        friend _STD ostream& operator<<( _STD ostream& output, square_matrix& _ref )
        {
            for ( size_t x = 0; x < _ref._size; x++ )
            {
                for ( size_t y = 0; y < _ref._size; y++)
                    output << _ref.at(x,y) << " ";
                output << "\n";
            }
            return output;
        }
};

#endif // MATRIX_HPP