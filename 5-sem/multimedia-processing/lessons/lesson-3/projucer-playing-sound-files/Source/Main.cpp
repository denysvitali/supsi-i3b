/*
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include <cassert>

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

    std::cout << "Channels=" << numChannels << " sampleRate=" << (int)sampleRate << std::endl;

    AudioBuffer<float> myBuffer(numChannels, sampleRate / 10);
    AudioSourceChannelInfo info(myBuffer);

    source->prepareToPlay(512, sampleRate);

    while (source->getNextReadPosition() < source->getTotalLength())
    {
        // Read next audio block
        source->getNextAudioBlock(info);

        const int numSamples = info.buffer->getNumSamples();
        const int numChannels = info.buffer->getNumChannels();
        const float **data = info.buffer->getArrayOfReadPointers();
        // loop through each channel
        for (int channel = 0; channel < numChannels; channel++)
        {
            // channelData contains now 'numSamples' of input data
            const float *channelData = data[channel];

            //TODO implement you algorithm! The following example dumps to stdout the audio contents
            std::cout << "Channel=" << channel << " numSamples=" << numSamples << std::endl;
            for (int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
                std::cout << channelData[sampleIndex] << ", ";
            std::cout << std::endl;
        }
    }
    return 0;
}
