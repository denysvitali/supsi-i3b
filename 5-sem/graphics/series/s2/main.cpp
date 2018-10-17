#include <iostream>
#include "vector.h"
#include "matrix.h"

int main() {

    // Exercise 1
    // a)
    std::cout << "a)" << std::endl;
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
    std::cout << "A + B = " << std::endl;
    std::cout << c << std::endl;

    // b)
    std::cout << "b)" << std::endl;
    Matrix d = Matrix{3,3};
    *d[0][0] = 0.5;
    *d[0][1] = -1;
    *d[0][2] = -2;
    *d[1][0] = 1;
    *d[1][1] = 0.5;
    *d[1][2] = -1;
    *d[2][0] = 2;
    *d[2][1] = 1;
    *d[2][2] = -0.5;

    Matrix transpose_me = Matrix{1, 2};
    *transpose_me[0][0] = 1;
    *transpose_me[0][1] = 2;

    std::cout << "Transpose: " << std::endl;
    std::cout << transpose_me << std::endl;
    Matrix transposed = transpose_me.transpose();

    std::cout << "Transposed: " << std::endl;
    std::cout << transposed << std::endl;

    transpose_me = Matrix{3, 2};
    *transpose_me[0][0] = 1;
    *transpose_me[0][1] = 2;
    *transpose_me[1][0] = 3;
    *transpose_me[1][1] = 4;
    *transpose_me[2][0] = 5;
    *transpose_me[2][1] = 6;

    std::cout << "Transpose: " << std::endl;
    std::cout << transpose_me << std::endl;
    transposed = transpose_me.transpose();

    std::cout << "Transposed: " << std::endl;
    std::cout << transposed << std::endl;

    std::cout << std::endl << std::endl;
    std::cout << "Transpose: " << std::endl;
    std::cout << d << std::endl;

    std::cout << "Transposed three times" << std::endl;
    std::cout << d.transpose().transpose().transpose() << std::endl;

    // c) Matrix * Vector
    std::cout << "e x v" << std::endl;
    Matrix e = Matrix{3,3};
    *e[0][0] = 1;
    *e[0][2] = 30;
    *e[1][1] = 1;
    *e[1][2] = 15;
    *e[2][2] = 1;

    std::cout << e << std::endl;

    Matrix v = Matrix{3,1};
    *v[0][0] = 1;
    *v[1][0] = 1;

    std::cout << v << std::endl;

    Matrix res = e * v;

    std::cout << "Result: " << std::endl;
    std::cout << res << std::endl;

    // d) Matrix^T x Matrix multiplication
    std::cout << "Matrix^T x Matrix multiplication" << std::endl;
    Matrix m1 {3,3}, m2{3,3};
    *m1[0][0] = 1;
    *m1[0][1] = -1;
    *m1[0][2] = 0;
    *m1[1][0] = -1;
    *m1[1][1] = 1;
    *m1[1][2] = 0;
    *m1[2][0] = 0;
    *m1[2][1] = 0;
    *m1[2][2] = 1;

    std::cout << "M1: " << m1 << std::endl;

    *m2[0][0] = 1;
    *m2[0][1] = 0;
    *m2[0][2] = 30;
    *m2[1][0] = 0;
    *m2[1][1] = 1;
    *m2[1][2] = 15;
    *m2[2][0] = 0;
    *m2[2][1] = 0;
    *m2[2][2] = 1;

    std::cout << "M2: " << m2 << std::endl;

    Matrix result = m1.transpose() * m2;
    std::cout << "Result: " << result << std::endl;
}