//
// Created by dvitali on 23.10.18.
//

#include <iostream>
#include "Tone.h"
#include "Utils.h"

bool Tone::lookup(float *fft, double sampleRate, int fftSize) {
    // Frequency Band 1:
    double max_freq = sampleRate / 2; // Nyquist
    double bands = max_freq * 1.0 / (fftSize*1.0/2.0);

    int fbx,fby = -1;
    for(int i=0; i<= fftSize/2; i++){
        if((m_freqX >= bands*i) && (m_freqX < bands*(i+1))){
            // Our band!
            fbx = i;
        }
        if((m_freqY >= bands*i) && (m_freqY < bands*(i+1))){
            // Our band!
            fby = i;
        }
    }

    double dbx = fftToDB(fft[fbx], fftSize);
    double dby = fftToDB(fft[fby], fftSize);

    int threshold = -34;

    return dbx >= threshold && dby >= threshold;
}

string Tone::getName() {
    return this->m_name;
}

char Tone::getSymbol() {
    return this->m_symbol;
}

int Tone::getFreqX() {
    return this->m_freqX;
}

int Tone::getFreqY() {
        return this->m_freqY;
}

char Tone::decode(int rep) {
    return getName()[rep-1];
}

bool Tone::operator==(Tone& t) {
    if(this->getSymbol() == t.getSymbol()){
        if(this->getName() == t.getName()){
            if(this->getFreqX() == t.getFreqX()){
                if(this->getFreqY() == t.getFreqY()){
                    return true;
                }
            }
        }
    }
    return false;
}