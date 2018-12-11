#include "average_cpu.h"
#include "utilities/commons.h"

#include <stdlib.h>
#include <stdio.h>

/******************************************************************************
* UTILITY FUNCTIONS
******************************************************************************/

static void readChannel(
	unsigned char * channelData,
	unsigned char *source,
	int imageW,
	int imageH, 
	int channelToExtract, 
	int numChannels)
{
	int i = 0;
	for (i = 0; i < (imageW * imageH); i++) {
		channelData[i] = source[numChannels * i + channelToExtract];
	}
}

static void writeChannel(
	unsigned char* destination, 
	unsigned char* channelData,
	int imageW,
	int imageH, 
	int channelToMerge, 
	int numChannels)
{
	int i = 0;
	for (i = 0; i < (imageW * imageH); i++) {
		destination[numChannels * i + channelToMerge] = (channelData[i]);
	}
}

/******************************************************************************
* AVERAGE FILTER
******************************************************************************/

static void compute_average(
	unsigned char* h_Dst,
	unsigned char* h_Src,
	int imageW,
	int imageH)
{
	const unsigned int numElements = ((2 * KERNEL_RADIUS) + 1) * ((2 * KERNEL_RADIUS) + 1);

	for (int y = 0; y < imageH; y++) {
		for (int x = 0; x < imageW; x++) {
			unsigned int sum = 0;
			for (int kY = -KERNEL_RADIUS; kY <= KERNEL_RADIUS; kY++) {
				const int curY = y + kY;
				if (curY < 0 || curY > imageH) {
					continue;
				}
				
				for (int kX = -KERNEL_RADIUS; kX <= KERNEL_RADIUS; kX++) {
					const int curX = x + kX;
					if (curX < 0 || curX > imageW) {
						continue;
					}

					const int curPosition = (curY * imageW + curX);
					if (curPosition >= 0 && curPosition < (imageW * imageH)) {
						sum += h_Src[curPosition];
					}
				}
			}
			h_Dst[y * imageW + x] = (unsigned char) (sum / numElements);
		}
	}
}

void average_cpu(
	unsigned char* inputImage,
	unsigned char* outputImage,
	int imageW,
	int imageH,
	int numChannels
)
{
	// Allocate memory for each channel
	unsigned char* const in_channel = (unsigned char*)malloc(imageW * imageH * sizeof(unsigned char));
	unsigned char* const out_channel = (unsigned char*)malloc(imageW * imageH * sizeof(unsigned char));
	int curChannel;

	printf(" average_cpu:\n");
	for (curChannel = 0; curChannel < numChannels; curChannel++) {
		printf("\tchannel(%d) readChannel", curChannel);
		readChannel(in_channel, inputImage, imageW, imageH, curChannel, numChannels);

		printf(" compute_average()");
		compute_average(out_channel, in_channel, imageW, imageH);

		printf(" writeChannel()\n");
		writeChannel(outputImage, out_channel, imageW, imageH, curChannel, numChannels);
	}
	free(in_channel);
	free(out_channel);
}