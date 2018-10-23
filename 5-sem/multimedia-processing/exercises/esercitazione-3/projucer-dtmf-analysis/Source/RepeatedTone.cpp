//
// Created by dvitali on 23.10.18.
//

#include "RepeatedTone.hpp"

int RepeatedTone::getRepetition() {
    return m_repetition;
}

int RepeatedTone::addRepetition() {
    m_repetition++;
    return m_repetition;
}

Tone& RepeatedTone::getTone() {
    return m_tone;
}
