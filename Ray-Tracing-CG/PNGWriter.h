#pragma once

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


class PNGWriter {
public:
	static void write_file(const char* name, int width, int height, int channels, float* data, int data_size) {
		unsigned char* integer_data = convert_data(data, data_size);
		stbi_write_png(name, width, height, channels, integer_data, width * channels);
	}

private:
	static unsigned char* convert_data(float* data, int data_size) {
        unsigned char* out = new unsigned char[data_size];
		for (int i = 0; i < data_size; i++)
		{
			out[i] = unsigned char(255.999f * data[i]);
		}
		return out;
	}
};