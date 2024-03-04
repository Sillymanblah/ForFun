#include "matrix.hpp"
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

int main()
{
    srand( time( NULL ) );
    const uint16_t MATRIX_SIZE = 4;

    typedef int matrix_type;

    uint16_t x, y;
    matrix_type temp = (matrix_type) rand() / RAND_MAX;
    square_matrix<matrix_type> test(MATRIX_SIZE);
    std::cout << "Hello World!\n";
    std::cout << test;

    x = rand() % MATRIX_SIZE;
    y = rand() % MATRIX_SIZE;

    std::cout << "\n" << x << "," << y << ": " << temp << "\n";

    test.at(x,y) = temp;
    std::cout << test;
}