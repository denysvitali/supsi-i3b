/*
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include <cassert>
#include <iostream>
#include <fstream>

const int FFT_LINES = 100;
int current_fft_line = 0;

void addFFTLine(float* fftBuffer, int fftSize, float* fftArr){
    for(int i=0; i<fftSize; i++){
        fftArr[i * FFT_LINES + current_fft_line] = fftBuffer[i];
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

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "Missing input audio file to analyze." << std::endl;
		return 1;
    }

    File input = File::getCurrentWorkingDirectory().getChildFile(argv[1]);
    if (input.exists() == false) {
		std::cerr << "File doesn't exists." << std::endl;
		return 1;
	}

	AudioFormatManager fmgr;
	fmgr.registerBasicFormats();
	ScopedPointer<AudioFormatReaderSource> source = new AudioFormatReaderSource(fmgr.createReaderFor(input), true);

	unsigned int numChannels = source->getAudioFormatReader()->numChannels;
	double sampleRate = source->getAudioFormatReader()->sampleRate;

	std::cout << "Channels=" << numChannels << " sampleRate=" << (int)sampleRate << std::endl;

	AudioBuffer<float> myBuffer(numChannels, sampleRate / 10);
	AudioSourceChannelInfo info(myBuffer);

	source->prepareToPlay(512, sampleRate);

    const int fftSize = 4096;
    auto* fftBuffer = new float[fftSize * 2];

    int power = static_cast<int>(log(fftSize) / log(2));

    std::cout << power << std::endl;

    dsp::FFT fft{power}; // 2^12 = 4096

    std::ofstream file;
    file.open("/tmp/fft.csv");

    int fftPos = 0;
    float* fftStore = new float[fftSize * FFT_LINES];

	while (source->getNextReadPosition() < source->getTotalLength())
	{
		// Read next audio block
		source->getNextAudioBlock(info);

		const int numSamples = info.buffer->getNumSamples();
		const int numChannels = info.buffer->getNumChannels();
		const float **data = info.buffer->getArrayOfReadPointers();
		// loop through each channel
		int channel = 0;
		const float *channelData = data[channel];
        for (int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++) {
            if(fftPos % 128 == 0) {
            }
            if(fftPos == fftSize){
                fft.performFrequencyOnlyForwardTransform(fftBuffer);
                addFFTLine(fftBuffer, fftSize, fftStore);
                fftPos = 0;
            }
            fftBuffer[fftPos] = channelData[fftPos];
            fftPos++;
        }
	}

	generateFFTCSV(file, fftSize, fftStore);
	return 0;
}