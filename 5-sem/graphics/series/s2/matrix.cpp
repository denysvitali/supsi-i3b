//
// Created by dvitali on 10.10.18.
//

#include "matrix.h"
#include <iomanip>

Matrix::Matrix(unsigned long rows, unsigned long columns) {
    this->m_content = new double[rows * columns];
    this->rows = rows;
    this->columns = columns;
    for(int i=0; i<this->rows; i++){
        for(int j=0; j<this->columns; j++){
            this->m_content[i*columns + j] = 0;
        }
    }
}

Matrix Matrix::transpose() const {
    Matrix m = Matrix{this->getColumns(), this->getRows()};

    for(int i=0; i < this->getRows(); i++){
        for(int j=0; j < this->getColumns(); j++){
            *(m[j][i]) = this->get(i, j);
        }
    }

    return m;
}

std::vector<double*> Matrix::operator [] (int v) {
    std::vector<double*> row = std::vector<double*>(this->columns);

    for(unsigned long i= v * this->columns; i < (v + 1) * this->columns; i++){
        row[i - v*this->columns] = &(m_content[i]);
    }

    return row;
}

unsigned long Matrix::getRows() const {
    return this->rows;
}

unsigned long Matrix::getColumns() const {
    return this->columns;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << "Matrix " << m.getRows() << "x" << m.getColumns() << std::endl;
    for(int i=0; i < m.getRows(); i++){
        os << "[ ";
        for(int j=0; j<m.getColumns(); j++){
            os << std::setw(5) <<  m.get(i, j) << std::setw(1) << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}

Matrix Matrix::operator+(const Matrix &m) {
    if(m.columns != this->columns || m.rows != this->rows){
        throw std::invalid_argument("Unable to sum these two matrices!");
    }

    Matrix r = Matrix{m.getRows(), m.getColumns()};
    for(int i=0; i<m.getRows(); i++){
        for(int j=0; j<m.getColumns(); j++){
            *r[i][j] = this->get(i, j) + (m.get(i, j));
        }
    }

    return r;
}

double Matrix::get(int i, int j) const {
    return (m_content[i * this->getColumns() + j]);
}

Matrix Matrix::operator*(const Matrix &m) {
    /*
     * Two matrices (A and B) may only be multiplied iff:
     * - The number of A's columns matches the number of B's rows
     * The resulting Matrix is a matrix C with size (A's rows x B's columns)
     *
     * In short, given A (n x m) and B (m x p), the resulting Matrix C will be
     * of size (n x p).
     */

    // A = this
    // B = m

    if(this->getColumns() != m.getRows()){
        char* error_msg = new char[80];
        std::sprintf(error_msg, "Unable to multiply a %dx%d matrix by a %dx%d",
                static_cast<int>(this->getRows()),
                static_cast<int>(this->getColumns()),
                static_cast<int>(m.getRows()),
                static_cast<int>(m.getColumns()));
        throw std::invalid_argument(error_msg);
    }

    Matrix result{this->getRows(), m.getColumns()};

    for(int i=0; i<result.getRows(); i++){
        for(int j=0; j<result.getColumns(); j++){
            for(int k = 0; k < this->getRows(); k++){
                *result[i][j] += this->get(i,k) * m.get(k, j);
            }
        }
    }

    return result;
}
