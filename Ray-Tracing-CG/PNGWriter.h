#pragma once

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Vec3.h"


// Classe en charge d’écrire un fichier png à partir du tableau de flottants contenant les couleurs des pixels, en utilisant
// une seule méthode statique publique.
class PNGWriter {
public:
	// Cache l’appel à stb
	static void write_file(const char* name, int width, int height, int channels, Vec3* data, int data_size) {
		unsigned char* integer_data = convert_data(data, data_size);
		stbi_write_png(name, width, height, channels, integer_data, width * channels);
	}

private:
	// Convertit le tableau de flottants en tableau d’entiers 8 bits pour stb
	static unsigned char* convert_data(Vec3* data, int data_size) {
        unsigned char* out = new unsigned char[3 * data_size];
		for (int i = 0; i < data_size; i++)
		{
			out[3 * i] = unsigned char(255.999f * data[i][0]);
			out[3 * i + 1] = unsigned char(255.999f * data[i][1]);
			out[3 * i + 2] = unsigned char(255.999f * data[i][2]);
		}
		return out;
	}
};