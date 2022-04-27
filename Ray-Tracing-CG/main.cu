#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <fstream>

#include "PNGWriter.h"
#include "Vec3.h"

using namespace std;


const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;

const int THREAD_BLOCK_SIZE = 8;


__global__ void render(Vec3* buffer, int width, int height) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if (i >= width || j >= height)
        return;

    int n = i + j * width;
    buffer[n] = Vec3(float(i) / (width - 1),
                     float(height - j) / (height - 1),
                     0.25f);
}

int main()
{
    int buf_size = IMAGE_WIDTH * IMAGE_HEIGHT;
    Vec3* colour_buf;
    cudaMallocManaged((void**) &colour_buf, buf_size*sizeof(Vec3));

    dim3 blocks(1 + IMAGE_WIDTH / THREAD_BLOCK_SIZE, 1 + IMAGE_HEIGHT / THREAD_BLOCK_SIZE);
    dim3 threads(THREAD_BLOCK_SIZE, THREAD_BLOCK_SIZE);

    render<<<blocks, threads>>>(colour_buf, IMAGE_WIDTH, IMAGE_HEIGHT);
    cudaDeviceSynchronize();

    PNGWriter::write_file("image.png", IMAGE_WIDTH, IMAGE_HEIGHT, 3, colour_buf, buf_size);

    cudaFree(colour_buf);
    

    return 0;
}