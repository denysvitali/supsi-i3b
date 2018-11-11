//
// Created by dvitali on 07.11.18.
//

#ifndef S3_POINT_H
#define S3_POINT_H

class Point {
public:
    Point(float x, float y, float z);
    float getX();
    float getY();
    float getZ();

private:
    float m_x;
    float m_y;
    float m_z;
};

#endif //S3_POINT_H
