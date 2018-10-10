#include <iostream>
#include "vector.h"
#include "matrix.h"

int main() {
    Matrix a = Matrix{3, 2};
    *a[0][0] = 1;
    *a[1][0] = 2;
    *a[1][1] = 3;
    *a[2][1] = 1;

    Matrix b = Matrix{3, 2};
    *b[0][0] = 3;
    *b[0][1] = 0.5;
    *b[1][0] = 0.5;
    *b[1][1] = 2;
    *b[2][0] = -0.5;
    *b[2][1] = 1;

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    Matrix c = a+b;
}