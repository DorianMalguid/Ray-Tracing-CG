#pragma once

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


// Classe en charge d’écrire un fichier png à partir du tableau de flottants contenant les couleurs des pixels, en utilisant
// une seule méthode statique publique.
class PNGWriter {
public:
	// Cache l’appel à stb
	static void write_file(const char* name, int width, int height, int channels, float* data, int data_size) {
		unsigned char* integer_data = convert_data(data, data_size);
		stbi_write_png(name, width, height, channels, integer_data, width * channels);
	}

private:
	// Convertit le tableau de flottants en tableau d’entiers 8 bits pour stb
	static unsigned char* convert_data(float* data, int data_size) {
        unsigned char* out = new unsigned char[data_size];
		for (int i = 0; i < data_size; i++)
		{
			out[i] = unsigned char(255.999f * data[i]);
		}
		return out;
	}
};