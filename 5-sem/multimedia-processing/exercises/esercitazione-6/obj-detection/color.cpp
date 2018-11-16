//
// Created by dvitali on 13.11.18.
//

#include "color.h"

using namespace std;

Color::Color(cv::Scalar &color) {
    m_r = static_cast<int>(color[2]);
    m_g = static_cast<int>(color[1]);
    m_b = static_cast<int>(color[0]);
}
string Color::label() {
    if(m_label.size() == 0){
        recognize_color();
    }
    return m_label;
}

int Color::R() {
    return m_r;
}

int Color::G() {
    return m_g;
}


int Color::B() {
    return m_b;
}

Color::Color(int r, int g, int b, const char *label) {
    m_r = r;
    m_g = g;
    m_b = b;
    m_label = label;
}

Color::Color(int r, int g, int b) : Color::Color(r,g,b, "") {}

void Color::recognize_color() {
    std::vector<Color> colors_v = colors();
    if(colors_v.size() == 0){
        this->m_label = "Unknown";
    }

    Color closest = colors_v[0];
    double distance = DBL_MAX;

    for(Color c : colors_v){

        double r_d = abs(c.m_r - m_r);
        double g_d = abs(c.m_g - m_g);
        double b_d = abs(c.m_b - m_b);

        if(r_d == g_d == b_d && r_d > 40){
            this->m_label = "Gray";
            break;
        }

        double d = sqrt(
                pow((c.m_r - m_r),2) +
                pow((c.m_g - m_g),2) +
                pow((c.m_b - m_b),2));
        if(d < distance){
            distance = d;
            closest = c;
        }
    }

    this->m_label = closest.m_label;
}

std::vector<Color> Color::colors() {
    return vector<Color>{
#include "all_colors.h"
    };
}
