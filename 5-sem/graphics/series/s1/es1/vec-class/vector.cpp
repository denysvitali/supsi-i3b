#include <iostream>
#include <cmath>
#include <vector>

#include "vector.h"

Vector::Vector(float x, float y, float z) : m_x{x}, m_y{y}, m_z{z} {

}

Vector Vector::operator+(const Vector& v){
  return Vector{
      this->m_x + v.m_x,
      this->m_y + v.m_y,
      this->m_z + v.m_z
  };
}

Vector Vector::operator-(const Vector& v){
  return Vector{
      this->m_x - v.m_x,
      this->m_y - v.m_y,
      this->m_z - v.m_z
  };
}

float Vector::intensity() const {
  return sqrt(pow(this->m_x,2) + pow(this->m_y, 2)
      + pow(this->m_z, 2));
}

Vector Vector::normalize() const {
  float i = this->intensity();

  return Vector {
    this->m_x / i,
    this->m_y / i,
    this->m_z / i
  };
}

float Vector::dot(const Vector& v){
  return (this->m_x * v.m_x + 
    this->m_y * v.m_y +
    this->m_z * v.m_z);
}

Vector Vector::cross(const Vector& v){
  return Vector {
    m_y * v.m_z - m_z * v.m_y,
    m_z * v.m_x - m_x * v.m_z,
    m_x * v.m_y - m_y * v.m_x
  };
}

void Vector::print() const {
  std::cout << "[" << this->m_x << ", " <<
    this->m_y << ", " << this->m_z << "]" << std::endl;
}

std::ostream &operator << (std::ostream &out, const Vector& v){
  out << "[" << v.m_x << ", " << v.m_y << ", " << v.m_z << "]";
  return out;
}
