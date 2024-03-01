#include <stdint.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "specialized_arithmetic.hpp"

#ifndef MATRIX_HPP
#define MATRIX_HPP

template <typename _Num>
uint8_t get_width( const _Num& _number, uint8_t _precision )
{
    _STD string temp(_number);
    return __min( (uint8_t) temp.size(), (uint8_t) temp.find('.') + _precision );
}

template <typename _Num>
class square_matrix
{
    static_assert( _SPEC is_arithmetic_v<_Num>, "_Num must be an arithmetic type." );
    private:
        _Num** _matrix;
        uint16_t _size;

        void copy_data( const square_matrix& _other )
        {
            for ( uint16_t y = 0; y < _other._size; y++ )
                for( uint16_t x = 0; x < _other._size; x++ )
                {
                    this->_matrix[x][y] = _other._matrix[x][y];
                }
        }
        void build( uint16_t _size )
        {
            _matrix = new _Num*[_size];
            for ( uint16_t i = 0; i < _size; i++ )
            {
                _matrix[i] = new _Num[_size]; // Builds a zeroed matrix.
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
            for ( uint16_t y = 0; y < this->_size; y++ )
            {

            }
        }

    public:
        square_matrix() : _matrix(nullptr), _size(0) {};
        square_matrix( uint16_t __size ) : _matrix(nullptr), _size(__size)
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

        _Num& get_pos( const uint16_t& _x_pos, const uint16_t& _y_pos )
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
        friend _STD ostream& operator<<( _STD ostream& output, const square_matrix& _ref );
};

template <class _Num>
_STD ostream& operator<<( _STD ostream& output, const square_matrix<_Num>& _ref )
{
    
}

#endif // MATRIX_HPP