//
// Created by dvitali on 10.10.18.
//

#ifndef S2_MATRIX_H
#define S2_MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
public:
    Matrix(unsigned long rows, unsigned long columns);
    std::vector<double*> operator[] (int v);
    Matrix operator + (const Matrix& m);

    unsigned long getRows() const;
    unsigned long getColumns() const;

    double get(int i, int j) const;

    friend std::ostream& operator << (std::ostream& os, const Matrix& m);
private:
    unsigned long rows;
    unsigned long columns;
    double* m_content;
};


#endif //S2_MATRIX_H
