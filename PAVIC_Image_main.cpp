

#include "PAVIC_Image.h"

int main(int argc, char** argv) {

	Image test("images/apple.jpg");


	//test.color_mask(0, 0, 1);
	//test.write("images/blue.png");
	//test.color_mask(0, 1, 0);
	//test.write("images/greem.png");
	test.color_mask(1, 0, 0);
	test.write("images/red.png");

	//test.write("images/new.png");

	//Image copy = test;

	/*Image gray_avg = test;
	gray_avg.grayscale_avg();
	gray_avg.write("images/gray_avg.png");

	Image gray_lum = test;
	gray_lum.grayscale_avg();
	gray_lum.write("images/gray_lum.png");

	for (int i = 0; i < copy.w * copy.channels;++i) {
		copy.data[i] = 255;
	}
	copy.write("images/copy.png");
	Image blank(100, 100, 3);
	blank.write("images/blank.jpg");*/

	return 0;

}