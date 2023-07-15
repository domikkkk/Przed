#include <stdio.h>
#include "image.h"

int sepija(unsigned int width, unsigned int height, unsigned int lbytes, unsigned char* pixels, unsigned int color, short int dist);


int main(void){
	ImageInfo* x = readBmp("cos1.bmp");
	int color=0xFF6464;
	short int dist=400;
	int d=sepija(x->width, x->height, x->line_bytes, x->pImg, color, dist);
	printf("%d\n", d);
	saveBmp("result.bmp", x);
	return 0;
}
