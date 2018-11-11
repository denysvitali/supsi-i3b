//
// Created by dvitali on 07.11.18.
//

#include "point.h"

Point::Point(float x, float y, float z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

float Point::getX() {
    return m_x;
}

float Point::getY() {
    return m_y;
}

float Point::getZ() {
    return m_z;
}