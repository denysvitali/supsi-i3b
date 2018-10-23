//
// Created by dvitali on 23.10.18.
//

#ifndef PROJUCER_DTMF_ANALYSIS_DECODEDTONE_H
#define PROJUCER_DTMF_ANALYSIS_DECODEDTONE_H


#include "Tone.h"

class DecodedTone {
public:
    DecodedTone(Tone& t, double time) : m_tone{t}, m_time{time} {}
    double getTime();
    Tone& getTone();
private:
    Tone& m_tone;
    double m_time;
};


#endif //PROJUCER_DTMF_ANALYSIS_DECODEDTONE_H
