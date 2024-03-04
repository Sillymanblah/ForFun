#include <stdint.h>
#include <type_traits>

#ifndef _STD
#define _STD ::std::
#endif // _STD

template < class _Ty >
class _matrix_operators;

template < class _Size_Ty >
struct size_type // For finding which size type we should use for the matrix class
{
    using type = _Size_Ty;
};

template < size_t, size_t >
inline constexpr bool same_num_v = false;
template < size_t _Value >
inline constexpr bool same_num_v< _Value, _Value > = true;

template < size_t _Value_1, size_t _Value_2 >
struct same_num : _STD bool_constant< same_num_v< _Value_1, _Value_2 > > {};

template < class _Ty, _Ty _Value, class _Cast_Ty >
struct is_castable
{
    static constexpr bool value = same_num_v< _Value, (_Ty)((_Cast_Ty) _Value) >;
    using type = _Cast_Ty;
};

template < size_t _Size, class... _Size_Types >
struct _Minimize
{
    using type = typename _STD disjunction< is_castable< size_t, _Size, _Size_Types >... >;
};

template < size_t _Size >
struct minimize : _Minimize< _Size, uint8_t, uint16_t, uint32_t, uint64_t > {};

typedef size_type< void > size_void;
typedef size_type< uint8_t > size_uint8;
typedef size_type< uint16_t > size_uint16;
typedef size_type< uint32_t > size_uint32;
typedef size_type< uint64_t > size_uint64;

template < class _Size_1, class _Size_2 >
struct max_of // Getting the maximum size of the integer.
{
    using type = typename _Size_1::type;
};

template < class _Size >
struct max_of< size_uint8, _Size >
{
    using type = typename _Size::type;
};

template <>
struct max_of< size_uint16, size_uint32 >
{
    using type = typename size_uint32::type;
};

template <>
struct max_of< size_uint16, size_uint64 >
{
    using type = typename size_uint64::type;
};

template <>
struct max_of< size_uint32, size_uint64 >
{
    using type = typename size_uint64::type;
};

template < class _Size_1, class _Size_2 >
using max_of_t = typename max_of< _Size_1, _Size_2 >::type;

template < class _Size, class... _Rest >
struct _Max_size // Rest is empty, so size is our max.
{
    using type = typename _Size::type;
};

template < class _Size, class _First, class... _Rest >
struct _Max_size< _Size, _First, _Rest... > // We can pull out an element so lets check its size.
{
    using type = typename _Max_size< max_of_t< _Size, typename _First::type >, _Rest... >::type;
};

template < class... _Sizes >
struct max_size : size_void // We sent no sizes, so our max is void.
{
    using type = typename size_void::type;
};

template < class _First, class... _Rest > // Any other amount of sizes were sent, lets find the max.
struct max_size< _First, _Rest... > : _Max_size< typename _First::type, _Rest... >
{

};

template < class... _Sizes >
using max_size_t = typename max_size< _Sizes... >::type;

template < class _Ty, class _Size_Ty >
class _matrix
{
    private:
        _Ty** __matrix;
        _Size_Ty __width, __length;

        void build()
        {
            __matrix = new _Ty*[__width];
            for ( _Size_Ty col_pos = 0; col_pos < __width; col_pos )
                __matrix[col_pos] = new _Ty[__length];
        }
        void destroy()
        {
            for ( _Size_Ty col_pos = 0; col_pos < __width; col_pos++ )
                delete [] __matrix[col_pos];
            delete [] __matrix;
        }
        _Ty& at( _Size_Ty _x_pos, _Size_Ty _y_pos )
        {
            return __matrix[_x_pos][_y_pos];
        }
};

template < class _Ty >
class _matrix< _Ty, uint8_t >
{
    public:
        _Ty* __matrix;

        void build()
        {
            __matrix = new _Ty[ this->__width * this->__length ];
        }
        void destroy()
        {
            delete [] __matrix;
        }
        _Ty& at( uint8_t _x_pos, uint8_t _y_pos )
        {
            return __matrix[ _x_pos + (this->__width * _y_pos) ];
        }
};

template < class _Ty, size_t _Dim_X, size_t _Dim_Y >
class matrix : _matrix< _Ty, max_size< minimize<_Dim_X>, minimize<_Dim_Y> > > // Standard matrix implementation.
{
    typedef max_size< minimize<_Dim_X>, minimize<_Dim_Y> > _Size_Ty;

    static_assert( _STD is_arithmetic_v<_Ty>, "_Ty must be an arithmetic type." );
    private:
        void copy_data( const matrix& _other )
        {
            for ( _Size_Ty _x_pos = 0; _x_pos < this->__width; _x_pos++ )
                for ( _Size_Ty _y_pos = 0; _y_pos < this->__length; _y_pos++ )
                    this->at( _x_pos, _y_pos );
        }

    public:
        matrix()
        {
            this->__width = _Dim_X;
            this->__length = _Dim_Y;
            this->__matrix = nullptr;
            this->build();
        }
        matrix( const matrix& _other ) : matrix()
        {
            this->copy_data( _other );
        }
};

template < class _Ty, size_t _Dims >
class matrix< _Ty, _Dims, _Dims > // Overloaded matrix for square matrices (allows computation of the determinant and diagonalizability).
{
    public:
        void diagonalize()
        {

        }
};

int main()
{
    matrix< int, 8, 8 > my_matrix;
}