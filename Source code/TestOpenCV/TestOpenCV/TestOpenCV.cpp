#include "stdafx.h"

#define MyCode
#ifdef MyCode

#include <Windows.h>
#include <highgui.h>
#include <cv.h>
#include "skeletonization.h"
#include "analysis.h"

using namespace std;

#define MyCode1
#ifdef MyCode1
void sleep () {
	Sleep(3000);
}

void pause () {
	printf("%s", "press any key to continue\n");
	_gettch();
}

int radius = 7;
int radius_max=10;
void myTrackbarRadius(int pos) {
        radius = pos;
}
int iterations = 6;
int iterations_max = 10;
void myTrackbarIterations(int pos) {
        iterations = pos;
}
int block = 11;
int block_max = 100;
void myTrackbarBlock(int pos) {
        block = (pos%2 == 0 && pos != 0 ? pos + 1 : (pos < 3 ? 3 : pos));
}

int pixels = 8;
int pixels_max = 55;
void myTrackbarPixels(int pos) {
        pixels = pos;
}

//bilateral
int filter_height = 10, filter_height_max = 200, filter_width = 10, filter_width_max = 200, sigma1 = 0, sigma1_max = 500, sigma2 = 0, sigma2_max = 500;
void myTrackbarFilterHeight(int pos) {filter_height = pos;}
void myTrackbarFilterWidth(int pos) {filter_width = pos;}
void myTrackbarSigma1(int pos) {sigma1 = pos;}
void myTrackbarSigma2(int pos) {sigma2 = pos;}

int main (int argc, char** argv) {
	IplImage *inputImage = 0;
	// им€ картинки задаЄтс€ первым параметром
    char* filename = argc == 2 ? argv[1] : "test_find_pixel.bmp";
    // получаем картинку
	inputImage = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	//inputImage = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED);
	//inputImage = cvLoadImage(filename, 1);
	//cvShowImage("original", inputImage);
    printf("[i] image: %s\n", filename);
    if (!inputImage) {
		printf("%s", "image not found\n");
		pause();
		exit(0);
	}
	inputImage = buildSkeleton(inputImage);
	cvNamedWindow("temp", 0);
	cvShowImage("temp", inputImage);
	vector <Skelet> skelets;
	skelets = getSkelets(inputImage);
	Skelet t = skelets[0];
	sortSkelet(t.arch);
	//Skelet skelet1, skelet2;
	//compareSkelets(skelet1, skelet2);
//#define main_action
#ifdef main_action
	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	//улучшение снимков
	IplImage *improvedImage = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 3 );
	
	printf("improve Image Quality started\n");
	improveImageQuality(inputImage, improvedImage);
	printf("improve Image Quality finished\n");
	cvNamedWindow("improved",0/*CV_WINDOW_AUTOSIZE*/);
	cvShowImage("improved", improvedImage);
    

	//сглаживание изображени€
	//IplImage *erode = cvCloneImage(newImage);
	//IplImage *dilate = cvCloneImage(newImage);
	IplImage *sum = cvCloneImage(improvedImage);
	IplImage *gray = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
	IplImage *dst = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
	
	
	//IplImage *bin = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 1 );
	
	
	
	cvCreateTrackbar("Radius", "original", &radius, radius_max, myTrackbarRadius);
	cvCreateTrackbar("Iterations", "original", &iterations, iterations_max, myTrackbarIterations);
	cvCreateTrackbar("Pix", "original", &pixels, pixels_max, myTrackbarPixels);
	cvCreateTrackbar("Block", "original", &block, block_max, myTrackbarBlock);
	cvCreateTrackbar("HeightF", "original", &filter_height, filter_height_max, myTrackbarFilterHeight);
	cvCreateTrackbar("WidthF", "original", &filter_width, filter_width_max, myTrackbarFilterWidth);
	cvCreateTrackbar("Sigma 1", "original", &sigma1, sigma1_max, myTrackbarSigma1);
	cvCreateTrackbar("Sigma 2", "original", &sigma2, sigma2_max, myTrackbarSigma2);
	cvShowImage("original", inputImage);
	cvNamedWindow("canny200-250", 1); //вот он дал наилучший результат
	
	cvNamedWindow("bin", 1);
	int source_radius = radius, source_iterations = iterations, source_block = block, source_pixels = pixels;
	while(1) {
		//if () {
				IplConvKernel* Kern = cvCreateStructuringElementEx(radius*2+1, radius*2+1, radius, radius, CV_SHAPE_ELLIPSE);
				printf("dilate started\n");
				cvDilate(improvedImage, sum, Kern, iterations);
				printf("dilate finished\n");
				printf("erode started\n");
				cvErode(sum, sum, Kern, iterations);
				printf("erode finished\n");
				//cvShowImage("SUM", sum);
				cvReleaseStructuringElement(&Kern);
		
				printf("Smoothing started\n");	
				IplImage *smoothImage = cvCloneImage(sum);
				cvSmooth(sum, smoothImage, CV_BILATERAL, filter_height, filter_width, sigma1, sigma2);
				cvNamedWindow("smooth", 0);
				cvShowImage("smooth", smoothImage);
				printf("Smoothing finished\n");
			//IplImage *dst = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
			//IplImage *smoothImage = cvLoadImage("smooth.jpg", 1);
			
				IplImage *gray = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
				cvCvtColor(smoothImage, gray, CV_RGB2GRAY);
				IplImage *bin = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
				printf("Adaptive Threshold started\n");
				cvAdaptiveThreshold(gray, bin, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, block, pixels);
				printf("Adaptive Threshold finished\n");
				cvShowImage("bin", bin);
				printf("Canny started\n");
				cvCanny(gray, dst, 200, 250, 3);
				printf("Canny finished\n");
				cvShowImage("canny200-250", dst);

				//построение цепного кода фримена
				CvMemStorage* storage = cvCreateMemStorage(0);
				CvSeq* contours=0;
				IplImage *imageInRange = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
				//cvInRangeS(gray, cvScalar(40), cvScalar(150), imageInRange);
				int contoursCont = cvFindContours(bin, storage, &contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
				IplImage *dst1 = cvCloneImage(improvedImage);
				for(CvSeq* seq0 = contours; seq0 != 0; seq0 = seq0->h_next){
					cvDrawContours(dst1, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8);
				}
				cvNamedWindow("contours", 0);
				cvShowImage("contours", dst1);
				cvReleaseImage(&imageInRange);
				cvReleaseImage(&dst1);

				cvReleaseImage(&gray);
				cvReleaseImage(&bin);
				cvReleaseImage(&smoothImage);
		//}
			char c = cvWaitKey(33);
			if (c == 27) {
				break;
			}
			//cvReleaseImage(&smoothImage);

			//cvReleaseImage(&dst);
			system("cls");
		
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&dst);
	cvReleaseImage(&sum);
	cvReleaseImage(&improvedImage);
#endif

	//выделение объектов на снимках
	//используем цепной код ‘римена дл€ поиска контуров

	//поиск похожих объектов на снимках
	//сравниваем 2 снимка на наличие похожих контуров и скелетов

	//построение математической модели камеры
	
	//вычисление рассто€ние от камеры до объектов на каждом снимке

	//вычисление географических координат объектов на каждом снимке

	//определение направлени€ движени€ объектов на каждом снимке

	//построение траектории движени€ объектов

	//вывод объектов контуров объектов на каждый снимок
	//вывод линий, соедин€ющих положение одного и того же объекта
	
	printf("All done\n");
	//pause();
	cvWaitKey(0);
	/*while( 1 )
	{
		if( cvWaitKey( 100 ) == 27 )
		break;
	}*/
	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	return 1;
}
#endif
#endif