
// Ref: https://www.youtube.com/watch?v=HWhLLIHI8rY
// Image Processing With C++: Ep. 2 - Grayscal

#include <cstdint>
#include <cstdio>


enum ImageType
{
	PNG, JPG, BMP,TGA
};

struct Image
{
	uint8_t* data = NULL;
	size_t size = 0;
	int w;
	int h;
	int channels;
	Image(const char* filename);
	Image(int w, int h, int channels);
	Image(const Image& img);
	~Image();

	bool read(const char* filename);
	bool write(const char* filename);
	ImageType getFileType(const char* filename);

	// Graysacale filter
	Image& grayscale_avg();
	Image& grayscale_lum();

	Image& color_mask(float r, float g, float b);




};