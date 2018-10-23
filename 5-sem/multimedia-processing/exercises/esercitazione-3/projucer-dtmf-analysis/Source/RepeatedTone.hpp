//
// Created by dvitali on 23.10.18.
//

#ifndef PROJUCER_DTMF_ANALYSIS_REPEATEDTONE_H
#define PROJUCER_DTMF_ANALYSIS_REPEATEDTONE_H


#include "Tone.h"

class RepeatedTone {
public:
    RepeatedTone(Tone& tone, int repetition) : m_tone{tone}, m_repetition{repetition} {}

    int getRepetition();
    int addRepetition();
    Tone& getTone();

private:
    Tone& m_tone;
    int m_repetition;
};


#endif //PROJUCER_DTMF_ANALYSIS_REPEATEDTONE_H
