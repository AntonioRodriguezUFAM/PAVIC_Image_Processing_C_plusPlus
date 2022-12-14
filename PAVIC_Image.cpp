
#define STB_IMAGE_IMPLEMENTATION

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "PAVIC_Image.h"
#include"include/stb_image.h"
#include "include/stb_image_write.h"


Image::Image(const char* filename) {
	if (read(filename)) {
		printf("Read %s\n", filename);
		size = w * h * channels;
	}
	else {
		printf("Failed to Read %s\n", filename);
	}
}
Image::Image(int w, int h, int channels) : w(w),h(h),channels(channels) {
	size = w * h * channels;
	data = new uint8_t[size];
}
Image::Image(const Image& img) :Image (img.w, img.h, img.channels ) {
	memcpy(data, img.data, size);

}
Image::~Image() {
	stbi_image_free(data);

}

bool Image::read(const char* filename) {
	data= stbi_load(filename, &w, &h, &channels, 0);
	return data != NULL;

}

bool Image::write(const char* filename) {
	ImageType type = getFileType(filename);
	int sucess;
	switch (type)
	{
	case PNG:
		sucess = stbi_write_png(filename, w, h, channels, data, w * channels);
		break;
	case JPG:
		sucess = stbi_write_jpg(filename, w, h, channels, data, 100);
		break;
	case BMP:
		sucess = stbi_write_bmp(filename, w, h, channels, data);
		break;
	case TGA:
		sucess = stbi_write_tga(filename, w, h, channels, data);
		break;
	}

	return sucess != 0;
}

ImageType Image::getFileType(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if (ext != nullptr) {
		if (strcmp(ext, ".png") == 0) {
			return PNG;
		}
		else if (strcmp(ext, ".jpg") == 0) {
			return JPG;
		}
		else if (strcmp(ext, ".bmp") == 0) {
			return BMP;
		}
		else if (strcmp(ext, ".tga") == 0) {
			return TGA;
		}
	}
	return PNG;
}

// Graysacale filter
Image& Image::grayscale_avg() {
	// (R+G+B)/3
	if (channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already grayscale ", this);
	}
	else {
		for (int i = 0; i < size; i += channels) {
			// (R+G+B)/3
			int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
			memset(data + i, gray, 3);

		}
	}
	return *this;

}
Image& Image::grayscale_lum() {
	// 
	if (channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already grayscale ", this);
	}
	else {
		for (int i = 0; i < size; i += channels) {
			//  0.2126*data[i] + 0.7152*data[i + 1] + 0.0722*data[i + 2];
			int gray = 0.2126*data[i] + 0.7152*data[i + 1] + 0.0722*data[i + 2];
			memset(data + i, gray, 3);

		}
	}
	return *this;

}

Image& Image::color_mask(float r, float g, float b) {
	if (channels < 3) {
		printf("\e[31m[ERROR] Color mask requires at least 3 channels, but this image has %d channels\e[0m\n", channels);
	}
	else {
		for (int i = 0;i < size;i += channels) {
			data[i] *= r;
			data[i + 1] *= g;
			data[i + 2] *= b;
		}
	}
	return *this;
}
