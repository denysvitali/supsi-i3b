#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	void average_cpu(
		unsigned char* inputImage,
		unsigned char* outputImage,
		int imageW,
		int imageH,
		int numChannels
	);

#ifdef __cplusplus
} //extern "C"
#endif
