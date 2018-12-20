#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "commons.h"
#include "average_cpu.h"
#include "average_gpu.h"

#include "profiling.h"
#include <math.h>
#include <stdlib.h>

#define BENCHMARK_CPU_ENABLED 1
#define BENCHMARK_GPU_ENABLED 1

static void waitForEnterPressed()
{
	char tmp;
	printf("Press enter to continue ... ");
	scanf("%c", &tmp);
}

unsigned char* generateRandomImage(const int w, const int h) 
{
	size_t i;
	size_t imageSize = w * h * 3;
	unsigned char *image = (unsigned char *)malloc(imageSize * sizeof(unsigned char));
	for (i = 0; i < imageSize; i++)
		*(image + i) = rand() / 256;
	return image;
}


void benchmark(
	profileStats_t *stats, 
	void (*function) (
		unsigned char* inputImage, 
		unsigned char* outputImage, 
		const int imageW, 
		const int imageH, 
		const int numChannels),
	unsigned int numBenchruns,
	unsigned char * input,
	int w, int h, int channels,
	unsigned char *output)
{
	profile_t *p = profile_init();
	int i;
	for (i = 0; i < numBenchruns; i++) {
		p->start(p);
		function(input, output, w, h, channels);
		stats->add(stats, p->stop(p));
	}
	profile_dispose(p);
}


int main(int argc, char **argv)
{
	char *filePath = NULL;
	int w = -1;
	int h = -1;
	int comp = -1;
	unsigned char* image = NULL;
	unsigned char* image_result = NULL;

	int generateImage = 0;
	if (argc == 2)
	{
		filePath = argv[1];
		image = stbi_load(filePath, &w, &h, &comp, STBI_rgb);
		if (image == NULL) {
			printf("Failed to load image '%s'\n", filePath);
			generateImage = 1;
		}
		if (w < 1 || h < 1) {
			printf("Invalid image size [%d, %d]\n", w, h);
			generateImage = 1;
		}

		if (generateImage == 0)
			printf("Loaded %s\n w=%d h=%d comp=%d\n", filePath, w, h, comp);
	} else {
		// No filepath specified: generate random image
		generateImage = 1;
	}

	print_gpuInfo();
 
	if (generateImage == 1) {
		w = 4096;
		h = 3072;
		comp = 3;
		printf("Generating random image [%d, %d]\n", w, h);
		image = generateRandomImage(w, h);
		stbi_write_jpg("generated_input.jpg", w, h, comp, image, 90);
	}

	profileStats_t *stats_cpu = profileStats_init();
	profileStats_t *stats_gpu = profileStats_init();
	// Keep 1 for testing purposes, increase for benchmark stats
	const int numRuns = 1;

	image_result = (unsigned char*) malloc(w * h * 3 * sizeof(unsigned char));
	if(BENCHMARK_CPU_ENABLED) {
		// Benchmark CPU average filter execution time on image
		benchmark(stats_cpu, average_cpu, numRuns, image, w, h, 3, image_result);
		stbi_write_jpg("result_avg_cpu.jpg", w, h, comp, image_result, 90);
	}

	if(BENCHMARK_GPU_ENABLED) {
		// Benchmark GPU average filter execution time on image
		memset(image_result, 0, w * h * 3 * sizeof(unsigned char));
		benchmark(stats_gpu, average_gpu, numRuns, image, w, h, 3, image_result);
		stbi_write_jpg("result_avg_gpu.jpg", w, h, comp, image_result, 90);

	}

	// Print benchmark stats
	printf("Benchmark stats\n");
	double gpuTime, cpuTime = 0.0;
	if(BENCHMARK_CPU_ENABLED) {
		printf("CPU        :");
		stats_cpu->printf(stats_cpu, 1, 1);
		cpuTime = stats_cpu->getAvg(stats_cpu);
	}
	if(BENCHMARK_GPU_ENABLED) {
		printf("GPU        :");
		stats_gpu->printf(stats_gpu, 1, 1);
		gpuTime = stats_gpu->getAvg(stats_gpu);
	}

	if(BENCHMARK_CPU_ENABLED && BENCHMARK_GPU_ENABLED) {
		printf("Speedups\n");
		printf("GPU        : %6.2f \n", cpuTime / gpuTime);
	}

	// Free memory
	free(image);
	free(image_result);

	if(BENCHMARK_CPU_ENABLED) {
		profileStats_dispose(stats_cpu);
	}

	if(BENCHMARK_GPU_ENABLED){
		profileStats_dispose(stats_gpu);
	}

	return 0;
}
