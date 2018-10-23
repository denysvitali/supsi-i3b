//
// Created by dvitali on 23.10.18.
//

#include <cmath>
float fftToDB(float fftValue, int fftSize)
{
    return 20.0f * log10f((fftValue) / (float) fftSize / 2.0f);
}