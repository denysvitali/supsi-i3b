//
// Created by dvitali on 10.10.18.
//

#include "matrix.h"

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
            os << m.get(i, j) << " ";
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
}

double Matrix::get(int i, int j) const {
    return (m_content[i * this->getRows() + j]);
}
