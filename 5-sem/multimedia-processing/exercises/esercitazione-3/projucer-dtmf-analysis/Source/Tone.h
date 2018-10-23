//
// Created by dvitali on 23.10.18.
//

#ifndef PROJUCER_DTMF_ANALYSIS_TONE_H
#define PROJUCER_DTMF_ANALYSIS_TONE_H

#include <string>
using namespace std;

class Tone {
public:
    Tone(char symbol, string name, int freqX, int freqY) :
            m_symbol{symbol},
            m_name{name},
            m_freqX{freqX},
            m_freqY{freqY} {}
    bool lookup(float* fft, double sampleRate, int fftSize);
    string getName();
    char getSymbol();
    int getFreqX();
    int getFreqY();
    char decode(int rep);

    bool operator==(Tone& t);
private:
    int m_freqX, m_freqY;
    char m_symbol;
    string m_name;
};

#endif //PROJUCER_DTMF_ANALYSIS_TONE_H
