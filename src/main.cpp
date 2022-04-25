#include <cmath>
#include <iostream>
#include <string>
#include "ppm.h"
#include "PerlinNoise.h"
#include "progressbar.h"

using namespace std;

#define VERSION "v0.15"

int main(int argc, char *argv[])
{
	string filename = "perlin_noise";

	// Define the size of the image
	unsigned int factor = 5;
	unsigned int width = 600, height = 450;

	int contour_lines = 10;
	float zoom = 1.0;
	float seed = 0.0;
	bool normalize = true;
	int red = 255, green = 255, blue = 255;

	// Commandline arguments
	for (int count = 0; count < argc; count++)
	{
		string input = argv[count];

		if (input.compare("-h") == 0 || input.compare("--help") == 0)
		{
			cout << "Options:" << endl
				 << "-h | --help       \tPrint this help" << endl
				 << "-v | --version    \tPrint version" << endl
				 << "-o | --output     \tChange Filename (default: " << filename << ")" << endl
				 << "-f | --factor     \tMultiply image resolution by factor (default: " << factor << ")" << endl
				 << "-w | --width      \tImage width in pixel (default: " << width << ")" << endl
				 << "-h | --height     \tImage height in pixel (default: " << height << ")" << endl
				 << "-z | --zoom       \tZoom in / Zoom out of perlin noise picture [float] (default: " << zoom << ")" << endl
				 << "-c | --contour    \tFactor for altitude of perlin noise (default: " << contour_lines << ")" << endl
				 << "-s | --seed       \tSeed for perlin noise randomness [float] (default: " << seed << ")" << endl
				 << "-n | --normalize  \tToggle perlin noise normalization (default: " << normalize << ")" << endl
				 << "-r | --red        \tRed value [0,...,255] (default: " << red << ")" << endl
				 << "-g | --green      \tGreen value [0,...,255] (default: " << green << ")" << endl
				 << "-b | --blue  	   \tBlue value [0,...,255] (default: " << blue << ")" << endl;

			return 0;
		}
		if (input.compare("-v") == 0 || input.compare("--version") == 0)
		{
			cout << "perlin noise imager " << VERSION << endl;
			return 0;
		}
		else if (input.compare("-o") == 0 || input.compare("--output") == 0)
		{
			filename = argv[count + 1];
		}
		else if (input.compare("-f") == 0 || input.compare("--factor") == 0)
		{
			factor = stoi(argv[count + 1]);
		}
		else if (input.compare("-w") == 0 || input.compare("--width") == 0)
		{
			width = stoi(argv[count + 1]);
		}
		else if (input.compare("-h") == 0 || input.compare("--height") == 0)
		{
			height = stoi(argv[count + 1]);
		}
		else if (input.compare("-z") == 0 || input.compare("--zoom") == 0)
		{
			zoom = stoi(argv[count + 1]);
		}
		else if (input.compare("-c") == 0 || input.compare("--contour") == 0)
		{
			contour_lines = stoi(argv[count + 1]);
		}
		else if (input.compare("-s") == 0 || input.compare("--seed") == 0)
		{
			seed = stof(argv[count + 1]);
		}
		else if (input.compare("-n") == 0 || input.compare("--normalize") == 0)
		{
			normalize = !normalize;
		}
		else if (input.compare("-r") == 0 || input.compare("--red") == 0)
		{
			red = stoi(argv[count + 1]);
		}
		else if (input.compare("-g") == 0 || input.compare("--green") == 0)
		{
			green = stoi(argv[count + 1]);
		}
		else if (input.compare("-b") == 0 || input.compare("--blue") == 0)
		{
			blue = stoi(argv[count + 1]);
		}
	}

	if (width == 0 || height == 0 || factor == 0 || contour_lines == 0)
	{
		cout << "ERROR: value not allowed!" << endl;
		return 1;
	}

	// Create an empty PPM image
	width *= factor;
	height *= factor;
	ppm image(width, height);

	// Create a PerlinNoise object with the reference permutation vector
	PerlinNoise pn;

	unsigned int kk = 0;
	unsigned long total_pixel_count = width * height;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < height; ++i)
	{ // y
		for (unsigned int j = 0; j < width; ++j)
		{ // x
			double x = (double)j / ((double)width);
			double y = (double)i / ((double)height);

			double n;

			// Wood like structure
			n = contour_lines * pn.noise(zoom * x, zoom * y, seed);
			// Round float to lower integer

			if (normalize)
				n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use
			// tones of grey
			image.r[kk] = floor(red * n);	// 180
			image.g[kk] = floor(green * n); // 100
			image.b[kk] = floor(blue * n);	// 50
			kk++;
		}

		if (kk % 100000 == 0)
			printProgress(0.5 * (double)kk / (double)total_pixel_count);
	}

	// Save the image in a binary PPM file
	image.write(filename + ".ppm");

	cout << "\nCrated perlin noise image with:\n"
		 << endl
		 << "Image size in pixel: \t" << width << " x " << height << endl
		 << "Color weighting: \tred[" << red << "/255]\tgreen[" << green << "/255]\tblue[" << blue << "/255]" << endl
		 << "Perlin noise options:" << endl
		 << "\t\tZoom factor: " << zoom << endl
		 << "\t\tAltitude facor: " << contour_lines << endl
		 << "\t\tSeed: " << seed << endl
		 << "\t\tNormalization: " << normalize << endl
		 << "\nSee options with -h" << endl;

	return 0;
}