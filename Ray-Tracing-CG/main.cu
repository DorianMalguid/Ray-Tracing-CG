#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <fstream>

using namespace std;


const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;

void write_image_file(string file_name, float* colour_buf, int buf_size);

int main()
{
    int buf_size = 3 * IMAGE_WIDTH * IMAGE_HEIGHT;
    float* colour_buf = new float[buf_size];

    int k = 0;
    for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < IMAGE_WIDTH; i++)
        {
            colour_buf[k++] = float(i) / (IMAGE_WIDTH - 1);
            colour_buf[k++] = float(j) / (IMAGE_HEIGHT - 1);
            colour_buf[k++] = 0.25f;
        }
    }
    
    write_image_file("image.ppm", colour_buf, buf_size);

    return 0;
}



// Write the colour buffer into a ppm file
void write_image_file(string file_name, float* colour_buf, int buf_size) {
    ofstream out(file_name);

    out << "P3" << endl << IMAGE_WIDTH << " " << IMAGE_HEIGHT << endl << "255" << endl;

    int i = 0;

    while (i < buf_size) {
        int ir = int(255.999f * colour_buf[i++]);
        int ig = int(255.999f * colour_buf[i++]);
        int ib = int(255.999f * colour_buf[i++]);

        out << ir << " " << ig << " " << ib << endl;
    }
    out.close();
}