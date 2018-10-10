#ifndef _VECTOR_H
#define _VECTOR_H

class Vector {
  public:
    Vector(float x, float y, float z);
    //Vector(int x, int y, int z);
    Vector normalize() const;
    float intensity() const;
    Vector operator+(const Vector& v);
    Vector operator-(const Vector& v);
    float dot(const Vector& v);
    Vector cross(const Vector& v);
    void print() const;
    friend std::ostream& operator << (std::ostream& out, const Vector& v);
  private:
    float m_x, m_y, m_z;
};

#endif
