#include <cmath>
#include "ppm.h"
#include "PerlinNoise.h"

int main()
{
	// Define the size of the image
	unsigned int multi = 5;
	unsigned int width = multi * 600, height = multi * 450;

	// Create an empty PPM image
	ppm image(width, height);

	// Create a PerlinNoise object with the reference permutation vector
	PerlinNoise pn;

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < height; ++i)
	{ // y
		for (unsigned int j = 0; j < width; ++j)
		{ // x
			double x = (double)j / ((double)width);
			double y = (double)i / ((double)height);

			double n;

			int contour_lines = 10;
			int zoom = 3;
			float seed = 0; // 0

			// Wood like structure
			n = contour_lines * pn.noise(zoom * x, zoom * y, seed);
			// Round float to lower integer
			n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use
			// tones of grey
			image.r[kk] = floor(50 * n);  // 180
			image.g[kk] = floor(100 * n); // 100
			image.b[kk] = floor(180 * n); // 50
			kk++;
		}
	}

	// Save the image in a binary PPM file
	image.write("perlin_noise.ppm");

	return 0;
}