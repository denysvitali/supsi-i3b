//
// Created by dvitali on 19.10.18.
//

#ifndef PROJUCER_DTMF_ANALYSIS_CIRCULARBUFFER_H
#define PROJUCER_DTMF_ANALYSIS_CIRCULARBUFFER_H


#include <assert.h>
#include <cstring>
#include <iostream>

#ifndef DEBUG_toString
#define DEBUG_toString(var)  " " << #var << "=" << var
#endif

/******************************************************************************
* CircularBuffer class
*
*
******************************************************************************/
template <typename Type>
class CircularBuffer
{
public:
	CircularBuffer(const int size, const int numSamples)
			: bufferSize(size)
			, bufferStep(numSamples)
			, bufferIndex(0)
	{
		assert(size > 0);
		assert(numSamples > 0);
		assert(numSamples < size);

		buffer = new Type[size];
		std::memset(buffer, 0, size * sizeof(Type));

		std::cout << "CircularBuffer("
				  << DEBUG_toString(bufferSize)
				  << ", " << DEBUG_toString(numSamples)
				  << ")" << std::endl;
	}

	~CircularBuffer() {
		delete[] buffer;
	}

	/**
	* return true if CircularBuffer has 'numSamples' new samples
	*/
	bool process(Type sample) {
		buffer[bufferIndex++] = sample;
		if (bufferIndex >= bufferSize)
			bufferIndex = 0;
		return (bufferIndex % bufferStep) == 0;
	}

	/**
	* copy CircularBuffer to outputBuffer starting from the oldest values
	*/
	void copyData(Type * const outputBuffer) {
		assert(outputBuffer != nullptr);

		if (bufferIndex == 0)
			std::memcpy(outputBuffer, buffer, bufferSize * sizeof(Type));
		else {
			const size_t firstPartSize = bufferSize - bufferIndex;
			const size_t secondPartSize = bufferIndex;
			std::memcpy(outputBuffer, buffer + bufferIndex, firstPartSize * sizeof(Type));
			std::memcpy(outputBuffer + firstPartSize, buffer, secondPartSize * sizeof(Type));
		}
	}

private:
	Type *buffer;
	size_t bufferIndex;
	const size_t bufferSize;
	const size_t bufferStep;
};


#endif //PROJUCER_DTMF_ANALYSIS_CIRCULARBUFFER_H
