#ifndef SKELETONIZATION_H
#define SKELETONIZATION_H

using namespace std;

struct Arch {
	vector <CvPoint> point;
};

void rotateMask(IplImage *mask1);
void fileOutput(char *s, IplImage *inputImage);
void improveImageQuality (IplImage *src, IplImage *dst);

//функци€ вычисл€ет вес дуги скелета, который определ€етс€ количеством пикселей, из которых состоит дуга
int getWeightArc (CvPoint startPoint, CvPoint finishPoint);

vector <Arch> getSkeletArc(IplImage *image);

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
void improveImageQuality (IplImage *src, IplImage *dst) {
	//преобразование изображени€ из rgb в hsv
	IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
	cvCvtColor( src, hsv, CV_BGR2HSV );
		
	//поиск минимума и максимума €ркости
	int fmin = 255;
	int fmax = 0;
	for( int y=0; y<hsv->height; y++ ) {
		uchar* ptr = (uchar*) (hsv->imageData + y * hsv->widthStep);
		for( int x=0; x < hsv->width; x++ ) {
			if (ptr[3*x+2] < fmin) {
				fmin = ptr[3*x+2];
			}
			if (ptr[3*x+2] > fmax) {
				fmax = ptr[3*x+2];
			}
		}
	}
	//создание желаемых значений порогов €ркости
	int gmin = 0, gmax = 255;
	//вычисление новой €ркости каждого пиксел€
	for( int y=0; y<hsv->height; y++ ) {
		uchar* ptr = (uchar*) (hsv->imageData + y * hsv->widthStep);
		for( int x=0; x < hsv->width; x++ ) {
			ptr[3*x+2] = (int) (
				(double)(
						(double)((ptr[3*x+2] - fmin)) / 
						((double)(fmax - fmin))
						) * (gmax - gmin) + 
				gmin);
		}
	}
	
	cvCvtColor( hsv, dst, CV_HSV2BGR );
	
	//освобождаем ресурсы
	cvReleaseImage(&hsv);
}

int getWeightArc (CvPoint startPoint, CvPoint finishPoint, IplImage *image) {
	startPoint.x = 0;
	startPoint.y = 0;
	finishPoint.x = 0;
	finishPoint.y = 0;
	
	int length = 0;
	return length;
}

vector <Arch> getSkeletArc(IplImage *image) {
	vector <Arch> skeletArches;
	IplImage *tempImage = cvCloneImage(image);
	bool black_pixel_is_find = false, second_black_pixel_is_found = false;
	//int y, x;
	int x_black, y_black;

	do {
		//поиск чЄрного пиксел€ в верхней строке
		uchar* ptr = (uchar*) (tempImage->imageData);
		uchar* ptr2 = (uchar*) (tempImage->imageData + tempImage->widthStep);
		for(int x=0; (x < tempImage->width) && (black_pixel_is_find == false); x++ ) {
			if (ptr[x] == 255) {
				//0x1
				//000
				for (int i = -1; i < 2; i++) {
					if (
						((x + i) != -1) || 
						((x + i) != (tempImage->width - 1))
						) {
						if (ptr [x + i] == 0) {
							black_pixel_is_find = true;
							x_black = x + i;
							y_black = 0;
						}
					
						if (ptr2 [x + i] == 0) {
							if (black_pixel_is_find == true || second_black_pixel_is_found == true) {
								second_black_pixel_is_found = true;
							}
							else {
								black_pixel_is_find = true;
								x_black = x + i;
								y_black = 1;
							}
						}
					}
				}
			}
		}

		if (black_pixel_is_find == false) {
			//поиск чЄрного пиксел€ в левом столбце
			for(int y = 1; (y < tempImage->height) && (black_pixel_is_find == false); y += 2 ) {
				uchar* ptr = (uchar*) (tempImage->imageData + y * tempImage->widthStep);
				for(int x=0; (x < tempImage->width) && (black_pixel_is_find == false); x++ ) {
					if (ptr[x] == 255) {
						if (ptr[x+1] == 0) {
							black_pixel_is_find = true;
							x_black = x + 1;
							y_black = 0;
						}
						else {
							if ((uchar*) (tempImage->imageData + tempImage->widthStep)[x] == 0) {
								black_pixel_is_find = true;
								x_black = x;
								y_black = 1;
							}
							else {
								if (x != 0) {
									if (ptr[x - 1] == 0) {
										black_pixel_is_find = true;
										x_black = x - 1;
										y_black = 0;
									}
								}
							}
						}
					}
				}
			}
		}
		//поиск чЄрного пиксел€ в правом столбце

		//поиск чЄрного пиксел€ в нижней строке
	} while (black_pixel_is_find == true);
	
	//поиск пиксел€ с одним чЄрным соседом
	for(int y=0; (y < tempImage->height) && (black_pixel_is_find == false); y += 2 ) {
		uchar* ptr1 = (uchar*) (tempImage->imageData + y * tempImage->widthStep);
		uchar* ptr2 = (uchar*) (tempImage->imageData + (y + 1) * tempImage->widthStep);
		uchar* ptr3 = (uchar*) (tempImage->imageData + (y + 2) * tempImage->widthStep);
		for(int x=0; x < tempImage->width; x++ ) {
			if (ptr1[x] == 0) {
				black_pixel_is_find = true;

				//поиск единственного чЄрного соседа
				bool black_neighbor_is_found = false, second_black_neighbor_is_found = false;
				int x_neighbor = -1, y_neighbor = -1;
				for (int h = y; h < (y+2); h++) {
					uchar* ptr = (uchar*) (tempImage->imageData + h * tempImage->widthStep);
					for (int w = (h == y? x+1: x); w < (x+2); w++) {
						if (ptr[w] == 0) {
							if (black_neighbor_is_found == false) {
								black_neighbor_is_found = true;
								x_neighbor = w;
								y_neighbor = h;
							}
							else {
								second_black_neighbor_is_found = true;
							}
						}
						if (second_black_neighbor_is_found  = true) {
							break;
						}
					}
					if (second_black_neighbor_is_found  = true) {
						break;
					}
				}
				if (black_neighbor_is_found == true && second_black_neighbor_is_found  == false) {
					CvPoint newPoint;
					newPoint.x = x_neighbor;
					newPoint.y = y_neighbor;
					Arch currentArch;
					currentArch.point.insert(newPoint);
					uchar* ptr = (uchar*) (tempImage->imageData + y_neighbor * tempImage->widthStep);
					ptr[x_neighbor] = 2;
					//ищем следующего соседа
					for (int h = x_neighbor; h < (x_neighbor + 2); h++) {
						uchar* ptr = (uchar*) (tempImage->imageData + h * tempImage->widthStep);
						for (int w = (h = x_neighbor? y_neighbor + 1 : y_neighbor); w < (y_neighbor + 2); w++) {
							
						}
					}
				}
			}
		}
		if(black_pixel_is_find == true) {
			break;
		}
	}


	cvReleaseImage(&tempImage);
	return skeletArches;
}

#endif //SKELETONIZATION_H