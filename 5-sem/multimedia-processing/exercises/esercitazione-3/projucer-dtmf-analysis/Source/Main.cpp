/*
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "CircularBuffer.hpp"
#include "MyFilter.hpp"
#include "DecodedTone.hpp"
#include "RepeatedTone.hpp"
#include "Tone.h"
#include "Utils.h"

#include <vector>

#include <cassert>
#include <iostream>
#include <fstream>

const int FFT_LINES = 100;
int current_fft_line = 0;

Tone t1 {'1', "",       1209, 697};
Tone t2 {'2', "ABC",    1336, 697};
Tone t3 {'3', "DEF",    1477, 697};
Tone t4 {'4', "GHI",    1209, 770};
Tone t5 {'5', "JKL",    1336, 770};
Tone t6 {'6', "MNO",    1477, 770};
Tone t7 {'7', "PQRS",   1209, 852};
Tone t8 {'8', "TUV",    1336, 852};
Tone t9 {'9', "WXYZ",   1477, 852};
Tone ts {'*', "+",      1209, 941};
Tone t0 {'0', " ",      1336, 941};
Tone th {'#', "",       1477, 941};

Tone tones[] = {t1, t2, t3, t4, t5, t6, t7, t8, t9, ts, t0, th};

std::vector<DecodedTone> decodedTones {};

void addFFTLine(float* fftBuffer, int fftSize, float* fftArr) {
    fftArr[0 + current_fft_line] = fftToDB(fftBuffer[0], fftSize);
    for (int i = 1; i < fftSize / 2; i++) {
        fftArr[i * FFT_LINES + current_fft_line] = fftToDB(2 * fftBuffer[i], fftSize);
    }
    current_fft_line++;
}

/*  fftArr
 *          FFT_1  FFT_2  FFT_3
 *  f1        x      y      z
 *  f2
 *  f3
 *  f4
 *  fn
 */

void generateFFTCSV(std::ofstream& file, int fftSize, float* fftStore){
    for(int i=0; i<fftSize; i++){
        file << i;
        for(int j=0; j<=current_fft_line; j++) {
            file << "," << fftStore[i * FFT_LINES + j];
        }
        file << std::endl;
    }
    file.close();
}


void parseFFT(float* fftBuffer, int fftSize, double sampleRate, double sampleIndex){
    for(int i=0; i<sizeof(tones)/sizeof(Tone); i++){
        if(tones[i].lookup(fftBuffer, sampleRate, fftSize)){
            std::cout << "Found tone " << tones[i].getSymbol() << " at " << sampleIndex << std::endl;
            if(decodedTones.size() == 0){
                decodedTones.emplace_back(tones[i], sampleIndex);
            } else {
                double last_time = decodedTones[decodedTones.size()-1].getTime();
                if(sampleIndex - last_time <= 0.2){
                    continue;
                }
                decodedTones.emplace_back(tones[i], sampleIndex);
            }
        }
    }
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "Missing input audio file to analyze." << std::endl;
		return 1;
    }

    File input = File::getCurrentWorkingDirectory().getChildFile(argv[1]);
    if (!input.exists()) {
		std::cerr << "File doesn't exists." << std::endl;
		return 1;
	}

	AudioFormatManager fmgr;
	fmgr.registerBasicFormats();
	ScopedPointer<AudioFormatReaderSource> source = new AudioFormatReaderSource(fmgr.createReaderFor(input), true);

	unsigned int numChannels = source->getAudioFormatReader()->numChannels;
	double sampleRate = source->getAudioFormatReader()->sampleRate;
	double totalAudioSamples = source->getAudioFormatReader()->lengthInSamples;

	std::cout << "Channels=" << numChannels << " sampleRate=" << (int)sampleRate << std::endl;

	AudioBuffer<float> myBuffer(numChannels, sampleRate / 10);
	AudioSourceChannelInfo info(myBuffer);

	source->prepareToPlay(512, sampleRate);

    const int fftSize = 1024;
    auto fftBufferSize = fftSize * 2;
    auto* fftBuffer = new float[fftBufferSize];

    CircularBuffer<float> cb{fftSize, 256};


    int power = static_cast<int>(log(fftSize) / log(2));

    std::cout << power << std::endl;

    dsp::FFT fft{power}; // 2^12 = 4096

    std::ofstream file;
    file.open("/tmp/fft.csv");

    float* fftStore = new float[fftSize * FFT_LINES];

    int totalSampleParsed = 0;

	while (source->getNextReadPosition() < source->getTotalLength())
	{
		// Read next audio block
		source->getNextAudioBlock(info);

		const int numSamples = info.buffer->getNumSamples();
		const float **data = info.buffer->getArrayOfReadPointers();
		// loop through each channel
		int channel = 0;
		const float *channelData = data[channel];

		MyFilter<float> filter{670, 1500, sampleRate};

        for (int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++) {
            if(cb.process(channelData[sampleIndex])){
                cb.copyData(fftBuffer);
                filter.process(fftBuffer, fftSize);
                fft.performFrequencyOnlyForwardTransform(fftBuffer);
                parseFFT(fftBuffer, fftSize, sampleRate, (totalSampleParsed*numSamples)/sampleRate);
                addFFTLine(fftBuffer, fftSize, fftStore);
            }
        }

        //std::cout << "numSamples="<<numSamples << ", totalSampleParsed=" << (totalSampleParsed*numSamples)/sampleRate << ", totalAudioSamples=" << totalAudioSamples*1.0/sampleRate << std::endl;
        totalSampleParsed++;
	}

	/*for(int i=0; i<decodedTones.size(); i++){
	    std::cout << "Tone: " << decodedTones[i].getTone().getSymbol() << " at " << decodedTones[i].getTime() << std::endl;
	}*/

    // Count Repetitions


    std::vector<RepeatedTone> repeatedTones{};

    double prevTime = 0;
    for(int i=0; i<decodedTones.size(); i++){
        if(decodedTones[i].getTime() - prevTime >= 1){
            repeatedTones.emplace_back(RepeatedTone(decodedTones[i].getTone(), 1));
        } else {
            if(repeatedTones.size() == 0){
                repeatedTones.emplace_back(RepeatedTone{decodedTones[i].getTone(), 1});
                prevTime = decodedTones[i].getTime();
                continue;
            }

            RepeatedTone& lastTone = repeatedTones[repeatedTones.size() - 1];

            if(lastTone.getTone() == decodedTones[i].getTone()){
                repeatedTones[repeatedTones.size() - 1].addRepetition();
            }
        }
        prevTime = decodedTones[i].getTime();
    }

    for(int i=0; i<repeatedTones.size(); i++){
        //std::cout << repeatedTones[i].getTone().getSymbol() << "(" << repeatedTones[i].getRepetition() << ")" << std::endl;
        std::cout << repeatedTones[i].getTone().decode(repeatedTones[i].getRepetition());
    }
    std::cout << std::endl;

	generateFFTCSV(file, fftSize, fftStore);
	return 0;
}