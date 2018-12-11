#include "commons.h"
#include "average_gpu.h"


// STD includes
#include <assert.h>
#include <stdio.h>

// CUDA runtime
#include <cuda_runtime.h>
#include <cuda.h>

#define BLOCKSIZE_X 16
#define BLOCKSIZE_Y 16

// Utilities and system includes
#include <helper_cuda.h>

#define gpuErrChk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, char *file, int line, bool abort=true) {
	if (code != cudaSuccess) {
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}


static // Print device properties
void printDevProp(cudaDeviceProp devProp) {
	printf("Major revision number:         %d\n", devProp.major);
	printf("Minor revision number:         %d\n", devProp.minor);
	printf("Name:                          %s\n", devProp.name);
	printf("Total global memory:           %zu\n", devProp.totalGlobalMem);
	printf("Total shared memory per block: %zu\n", devProp.sharedMemPerBlock);
	printf("Total registers per block:     %d\n", devProp.regsPerBlock);
	printf("Warp size:                     %d\n", devProp.warpSize);
	printf("Maximum memory pitch:          %zu\n", devProp.memPitch);
	printf("Maximum threads per block:     %d\n", devProp.maxThreadsPerBlock);
	for (int i = 0; i < 3; ++i)
		printf("Maximum dimension %d of block:  %d\n", i, devProp.maxThreadsDim[i]);
	for (int i = 0; i < 3; ++i)
		printf("Maximum dimension %d of grid:   %d\n", i, devProp.maxGridSize[i]);
	printf("Clock rate:                    %d\n", devProp.clockRate);
	printf("Total constant memory:         %zu\n", devProp.totalConstMem);
	printf("Texture alignment:             %zu\n", devProp.textureAlignment);
	printf("Concurrent copy and execution: %s\n", (devProp.deviceOverlap ? "Yes" : "No"));
	printf("Number of multiprocessors:     %d\n", devProp.multiProcessorCount);
	printf("Kernel execution timeout:      %s\n", (devProp.kernelExecTimeoutEnabled ? "Yes" : "No"));
	return;
}

void print_gpuInfo() {
	int rtVersion = 0;
	printf("*********************************************************************************************\n");
	checkCudaErrors(cudaRuntimeGetVersion(&rtVersion));
	printf("CUDA Runtime Version = %d\n", rtVersion);
	int driverVersion = 0;
	checkCudaErrors(cudaDriverGetVersion(&driverVersion));
	printf("CUDA Driver Version  = %d\n", rtVersion);

	int numDevices = 0;
	checkCudaErrors(cudaGetDeviceCount(&numDevices));
	printf("Devices found        = %d\n", numDevices);

	for (int i = 0; i < numDevices; i++) {
		cudaDeviceProp properties;
		checkCudaErrors(cudaGetDeviceProperties(&properties, i));
		printDevProp(properties);
	}
	printf("*********************************************************************************************\n");
}


/******************************************************************************
* UTILITY FUNCTIONS
******************************************************************************/

__global__ static void averageKernel(
		unsigned char* output,
		unsigned char* input,
		int imageW,
		int imageH
		){

	const int x = blockIdx.x * blockDim.x + threadIdx.x;
	const int y = blockIdx.y * blockDim.y + threadIdx.y;
	const int posIn = y * imageW + x;
	const int posOut = y * imageW + x;

	unsigned int sum = 0;
	unsigned int numels = 0;
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
				sum += input[curPosition];
				numels++;
			}
		}
	}
	output[y * imageW + x] = (unsigned char) (sum / numels);

	//output[posOut] = input[posIn];

}

__global__ static void readChannel(
		unsigned char *output,
		unsigned char *input,
		int imageW,
		int imageH,
		int channelToExtract,
		int numChannels) {

	const int x = blockIdx.x * blockDim.x + threadIdx.x;
	const int y = blockIdx.y * blockDim.y + threadIdx.y;

	const int posIn = y * imageW * numChannels + x * numChannels + channelToExtract;
	const int posOut = y * imageW + x;

	output[posOut] = input[posIn];
}

__global__ static void writeChannel(
		unsigned char *output,
		unsigned char *input,
		int imageW,
		int imageH,
		int channelToExtract,
		int numChannels) {

	const int x = blockIdx.x * blockDim.x + threadIdx.x;
	const int y = blockIdx.y * blockDim.y + threadIdx.y;

	const int posIn = y * imageW + x;
	const int posOut = y * imageW * numChannels + x * numChannels + channelToExtract;

	output[posOut] = input[posIn];
}

/******************************************************************************
* AVERAGE FILTER
******************************************************************************/

void average_gpu(
		unsigned char *inputImage,
		unsigned char *outputImage,
		int imageW,
		int imageH,
		int numChannels
) {
	unsigned char *gpuImage;
	size_t size = imageW * imageH * numChannels * sizeof(unsigned char);

	cudaMalloc(&gpuImage, size);
	cudaMemcpy(gpuImage, inputImage, size, cudaMemcpyHostToDevice);

	dim3 block(BLOCKSIZE_X, BLOCKSIZE_Y);
	dim3 grid(static_cast<unsigned int>(imageW / BLOCKSIZE_X), static_cast<unsigned int>(imageH / BLOCKSIZE_Y));

	unsigned char *channelData;
	unsigned char *averageChannel;
	int nrChannels = 3;
	int ch_size = imageW * imageH;

	for(int i=0; i<numChannels; i++) {
		cudaMalloc(&channelData, sizeof(unsigned char) * imageW * imageH);
		cudaMalloc(&averageChannel, sizeof(unsigned char) * imageW * imageH);

		readChannel <<< grid, block >>> (channelData, gpuImage, imageW, imageH, i, nrChannels);
		gpuErrChk(cudaPeekAtLastError());
		gpuErrChk(cudaDeviceSynchronize());

		averageKernel <<< grid, block >>> (averageChannel, channelData, imageW, imageH);
		writeChannel <<< grid, block >>> (gpuImage, averageChannel, imageW, imageH, i, nrChannels);
	}
	cudaMemcpy(outputImage, gpuImage, size, cudaMemcpyDeviceToHost);
	cudaFree(channelData);
	cudaFree(averageChannel);
}

