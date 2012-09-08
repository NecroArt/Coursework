#ifndef SKELETONIZATION_H
#define SKELETONIZATION_H


void rotateMask(IplImage *mask1);
void fileOutput(char *s, IplImage *inputImage);

IplImage *buildSkeleton (IplImage *inputImage) {
	IplImage *outputImage = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
	outputImage = cvCloneImage(inputImage);
	//mask1
		IplImage *mask1 = cvCreateImage(cvSize(3,3), IPL_DEPTH_8U, 1);
		uchar* mask1Ptr = (uchar*)(mask1->imageData + 0*mask1->widthStep);
		mask1Ptr[0] = 255; mask1Ptr[1] = 255; mask1Ptr[2] = 255;
		mask1Ptr = (uchar*)(mask1->imageData + 1*mask1->widthStep);
		mask1Ptr[0] = 128; mask1Ptr[1] = 0; mask1Ptr[2] = 128;
		mask1Ptr = (uchar*)(mask1->imageData + 2*mask1->widthStep);
		mask1Ptr[0] = 0; mask1Ptr[1] = 0; mask1Ptr[2] = 0;
	//mask2
		IplImage *mask2 = cvCreateImage(cvSize(3,3), IPL_DEPTH_8U, 1);
		uchar* mask2Ptr = (uchar*)(mask2->imageData + 0*mask2->widthStep);
		mask2Ptr[0] = 128; mask2Ptr[1] = 255; mask2Ptr[2] = 255;
		mask2Ptr = (uchar*)(mask2->imageData + 1*mask2->widthStep);
		mask2Ptr[0] = 0; mask2Ptr[1] = 0; mask2Ptr[2] = 255;
		mask2Ptr = (uchar*)(mask2->imageData + 2*mask2->widthStep);
		mask2Ptr[0] = 128; mask2Ptr[1] = 0; mask2Ptr[2] = 128;

	for (int y = 0; y < (outputImage->height - 2); y++) {
		uchar* imagePtr0 = (uchar*)(outputImage->imageData + y * outputImage->widthStep);
		uchar* imagePtr1 = (uchar*)(outputImage->imageData + (y + 1) * outputImage->widthStep);
		uchar* imagePtr2 = (uchar*)(outputImage->imageData + (y + 2) * outputImage->widthStep);
		for( int x=0; x < (outputImage->width - 2); x++) {
			for (int iter = 1; iter <= 4; iter++) {
				//mask1
				uchar* maskPtr0 = (uchar*)(mask1->imageData);
				uchar* maskPtr1 = (uchar*)(mask1->imageData + mask1->widthStep);
				uchar* maskPtr2 = (uchar*)(mask1->imageData + 2*mask1->widthStep);
				if ((maskPtr0[0] == 128 || maskPtr0[0] == imagePtr0[x]) && 
					(maskPtr0[1] == 128 || maskPtr0[1] == imagePtr0[x+1]) &&
					(maskPtr0[2] == 128 || maskPtr0[2] == imagePtr0[x+2]) &&

					(maskPtr1[0] == 128 || maskPtr1[0] == imagePtr1[x]) && 
					(maskPtr1[1] == 128 || maskPtr1[1] == imagePtr1[x+1]) &&
					(maskPtr1[2] == 128 || maskPtr1[2] == imagePtr1[x+2]) &&

					(maskPtr2[0] == 128 || maskPtr2[0] == imagePtr2[x]) && 
					(maskPtr2[1] == 128 || maskPtr2[1] == imagePtr2[x+1]) &&
					(maskPtr2[2] == 128 || maskPtr2[2] == imagePtr2[x+2])) {
					imagePtr1[x+1] = 255;
				}
				//чтобы не пововаричвать маску 4-й раз
				if(iter < 4) {
					rotateMask(mask1);
				}
			}
		}
		for( int x=0; x < (mask2->width - 2); x++) {
			for (int iter = 1; iter <= 4; iter++) {
				//mask2
				uchar* maskPtr0 = (uchar*)(mask2->imageData);
				uchar* maskPtr1 = (uchar*)(mask2->imageData + mask2->widthStep);
				uchar* maskPtr2 = (uchar*)(mask2->imageData + 2*mask2->widthStep);
				if ((maskPtr0[0] == 128 || maskPtr0[0] == imagePtr0[x]) && 
					(maskPtr0[1] == 128 || maskPtr0[1] == imagePtr0[x+1]) &&
					(maskPtr0[2] == 128 || maskPtr0[2] == imagePtr0[x+2]) &&

					(maskPtr1[0] == 128 || maskPtr1[0] == imagePtr1[x]) && 
					(maskPtr1[1] == 128 || maskPtr1[1] == imagePtr1[x+1]) &&
					(maskPtr1[2] == 128 || maskPtr1[2] == imagePtr1[x+2]) &&

					(maskPtr2[0] == 128 || maskPtr2[0] == imagePtr2[x]) && 
					(maskPtr2[1] == 128 || maskPtr2[1] == imagePtr2[x+1]) &&
					(maskPtr2[2] == 128 || maskPtr2[2] == imagePtr2[x+2])
					) {
					imagePtr1[x+1] = 255;
				}
				//чтобы не пововаричвать маску 4-й раз
				if(iter < 4) {
					rotateMask(mask2);
				}
			}
		}
	}
	
	cvReleaseImage(&mask1);
	cvReleaseImage(&mask2);
	
	return outputImage;
}

void rotateMask(IplImage *mask) {
	uchar* mask1Ptr0 = (uchar*)(mask->imageData);
	uchar* mask1Ptr1 = (uchar*)(mask->imageData + mask->widthStep);
	uchar* mask1Ptr2 = (uchar*)(mask->imageData + 2 * mask->widthStep);

	uchar buf;
	buf = mask1Ptr0[2]; mask1Ptr0[2] = mask1Ptr0[0]; mask1Ptr0[0] = mask1Ptr2[0]; mask1Ptr2[0] = mask1Ptr2[2]; mask1Ptr2[2] = buf;
	buf = mask1Ptr0[1]; mask1Ptr0[1] = mask1Ptr1[0]; mask1Ptr1[0] = mask1Ptr2[1]; mask1Ptr2[1] = mask1Ptr1[2]; mask1Ptr1[2] = buf;
}
void fileOutput(char *s, IplImage *inputImage){
	FILE *f = fopen(s, "w");
	char *temp = new char [5];
	int x1, y1; uchar* ptr1;
	for( int y=0; y<inputImage->height; y++ ) {
		uchar* ptr = (uchar*) (inputImage->imageData + y * inputImage->widthStep);
		for( int x=0; x < inputImage->width; x++ ) {

			itoa(ptr[x], temp, 10);
			fwrite(temp, sizeof(char), strlen(temp), f);
			fwrite("  ", sizeof(char), strlen("  "), f);
		}
		fwrite ("\n", sizeof(char), strlen("\n"), f);
	}
	delete temp;
	fclose(f);
}
#endif //SKELETONIZATION_H