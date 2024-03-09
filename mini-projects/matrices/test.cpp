#include "test.hpp"
#include <stdint.h>
#include <random>
#include <limits>
#include <ctime>
#include <iostream>

#define READABLE_OUTPUT true
#define GET_RANDOM_DECIMAL (double)rand() / RAND_MAX

int main()
{
    using matrix_type = uint16_t;
    const size_t matrix_size = 4;
    const size_t num_matrices = 4;
    matrix_type max_rand = _STD numeric_limits<matrix_type>::max();
    matrix_type min_rand = _STD numeric_limits<matrix_type>::min();

    if (READABLE_OUTPUT)
        matrix_type max_rand = 10;

    matrix< matrix_type, matrix_size, matrix_size > square_matrices[num_matrices]; // Building n square matrices.

    srand( time(NULL) );
    for ( size_t matrix_num = 1; matrix_num < num_matrices; matrix_num++ ) // For each matrix.
    {
        auto& current_matrix = square_matrices[matrix_num];
        for ( size_t x = 0; x < matrix_size; x++ ) // For each x position.
            for ( size_t y = 0; y < matrix_size; y++ ) // For each y position.
                current_matrix.at(x,y) = ( (double)rand() / RAND_MAX ) * ( max_rand - min_rand ) + min_rand; // Assign a random value.

        _STD cout << current_matrix;
        if (matrix_num != num_matrices-1) 
            _STD cout << "+\n";
        square_matrices[0] += current_matrix;
    }

    _STD cout << "=\n" << square_matrices[0];
}