#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	void print_gpuInfo();

	void average_gpu(
		unsigned char* inputImage,
		unsigned char* outputImage,
		int imageW,
		int imageH,
		int numChannels
	);

#ifdef __cplusplus
} //extern "C"
#endif
