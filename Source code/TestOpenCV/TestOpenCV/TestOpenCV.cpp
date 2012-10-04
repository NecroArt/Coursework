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
	// ��� �������� ������� ������ ����������
    char* filename = argc == 2 ? argv[1] : "Image0.jpg";
    // �������� ��������
	//inputImage = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	//inputImage = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED);
	//IplImage *Igray = cvLoadImage( argv[6], CV_LOAD_IMAGE_GRAYSCALE);
	inputImage = cvLoadImage(filename, 1);
	//cvShowImage("original", inputImage);
    printf("[i] image: %s\n", filename);
    if (!inputImage) {
		printf("%s", "image not found\n");
		pause();
		exit(0);
	}
	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	
	//��������� �������
	IplImage *improvedImage = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 3 );
	
	printf("improve Image Quality started\n");
	improveImageQuality(inputImage, improvedImage);
	printf("improve Image Quality finished\n");
	cvNamedWindow("improved",0/*CV_WINDOW_AUTOSIZE*/);
	cvShowImage("improved", improvedImage);
    

	//����������� �����������
	//IplImage *erode = cvCloneImage(newImage);
	//IplImage *dilate = cvCloneImage(newImage);
	IplImage *sum = cvCloneImage(improvedImage);
	IplImage *gray = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
	IplImage *dst = cvCreateImage( cvGetSize(improvedImage), IPL_DEPTH_8U, 1 );
	
	
	//IplImage *bin = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 1 );
	
	
	
	cvCreateTrackbar("Radius", "original", &radius, radius_max, myTrackbarRadius);
	cvCreateTrackbar("Iterations", "original", &iterations, iterations_max, myTrackbarIterations);
//#define com
#ifdef com
	IplConvKernel* Kern = cvCreateStructuringElementEx(radius*2+1, radius*2+1, radius, radius, CV_SHAPE_ELLIPSE);
	cvDilate(newImage, sum, Kern, iterations);
	cvErode(sum, sum, Kern, iterations);
	
	IplImage *smoothImage = cvCloneImage(newImage);
	cvSmooth(sum, smoothImage, CV_BILATERAL, 100, 100, 100, 50);
	//����� �������� ��� ������� ���� �������
	//IplImage *smoothImage = cvLoadImage("smooth.jpg", 1);
	cvCvtColor(smoothImage, gray, CV_RGB2GRAY);

	IplImage *outputImage1 = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
	//cvAdaptiveThreshold(gray, outputImage1, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, block, pixels);
	cvInRangeS(gray, cvScalar(40), cvScalar(150), outputImage1/*bin*/);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours=0;
	int contoursCont = cvFindContours( /*bin*/outputImage1, storage,&contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
	printf("%d\n", contoursCont);
	IplImage *dst1 = cvCloneImage(newImage);
	for(CvSeq* seq0 = contours;seq0!=0;seq0 = seq0->h_next){
		cvDrawContours(dst1, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8);
	}
	cvNamedWindow("contours", 0);
	cvShowImage("contours", dst1);
	cvReleaseImage(&dst1);
	cvReleaseImage(&outputImage1);
	//�������� �������

	IplImage *outputImage = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
	cvAdaptiveThreshold(gray, outputImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, block, pixels);
	cvNamedWindow("bin", 1);
	cvShowImage("bin", outputImage);
#endif
	cvCreateTrackbar("Pix", "original", &pixels, pixels_max, myTrackbarPixels);
	cvCreateTrackbar("Block", "original", &block, block_max, myTrackbarBlock);
	cvCreateTrackbar("HeightF", "original", &filter_height, filter_height_max, myTrackbarFilterHeight);
	cvCreateTrackbar("WidthF", "original", &filter_width, filter_width_max, myTrackbarFilterWidth);
	cvCreateTrackbar("Sigma 1", "original", &sigma1, sigma1_max, myTrackbarSigma1);
	cvCreateTrackbar("Sigma 2", "original", &sigma2, sigma2_max, myTrackbarSigma2);
	cvShowImage("original", inputImage);
	cvNamedWindow("canny200-250", 1); //��� �� ��� ��������� ���������
	//cvNamedWindow("SUM", CV_WINDOW_AUTOSIZE);
	
#define comment
#ifdef comment
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

				//���������� ������� ���� �������
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
#endif
#ifdef com
	cvReleaseImage(&smoothImage);
	cvReleaseStructuringElement(&Kern);
#endif

	//��������� �������� �� �������
	//���������� ������ ��� ������� ��� ������ ��������

	//����� ������� �������� �� �������
	//���������� 2 ������ �� ������� ������� �������� � ��������

	//���������� �������������� ������ ������
	
	//���������� ���������� �� ������ �� �������� �� ������ ������

	//���������� �������������� ��������� �������� �� ������ ������

	//����������� ����������� �������� �������� �� ������ ������

	//���������� ���������� �������� ��������

	//����� �������� �������� �������� �� ������ ������
	//����� �����, ����������� ��������� ������ � ���� �� �������
	/*cvNamedWindow("Erode", 0);
	cvShowImage("Erode", gray);
	cvCvtColor(erode, gray, CV_RGB2GRAY);
	improveImageQuality(inputImage, erode);*/
	/*cvNamedWindow("Dilate", CV_WINDOW_AUTOSIZE);
	cvShowImage("Dilate", dst);*/
	
	
	/*cvSmooth(inputImage, smoothImage, CV_GAUSSIAN, 3, 3);
	cvNamedWindow("smooth", 0);
	cvShowImage("smooth", smoothImage);
	cvCvtColor(inputImage, gray, CV_RGB2GRAY);
	//cvSmooth(inputImage, smoothImage, CV_BILATERAL, 100, 100, 100, 50);
	cvSaveImage("temp.jpg", smoothImage);
	cvCvtColor(smoothImage, gray, CV_RGB2GRAY);*/

	//���������� ��������
	/*cvCanny(gray, dst, 10, 250, 3);
	cvNamedWindow("erode10-250", 0);
	cvShowImage("erode10-250", dst);
	cvCanny(gray, dst, 200, 250, 3);
	cvNamedWindow("erode200-250", 0);
	cvShowImage("erode200-250", dst);
	cvCanny(gray, dst, 150, 200, 3);
	cvNamedWindow("erode150-200", 0);
	cvShowImage("erode150-200", dst);*/

	/*cvCvtColor(dilate, gray, CV_RGB2GRAY);
	cvCanny(gray, dst, 10, 250, 3); //���� ��� ������� ��������� ��� ��������� ������
	cvNamedWindow("dilate10-250", 0);
	cvShowImage("dilate10-250", dst);
	cvReleaseImage(&newImage);*/
	/*cvCanny(gray, dst, 200, 250, 3);
	cvNamedWindow("dilate200-250", 0); //��� �� ��� ��������� ���������
	cvShowImage("dilate200-250", dst);
	cvSaveImage("fairWeather.jpg", dst);*/
	/*cvCanny(gray, dst, 150, 200, 3);
	cvNamedWindow("dilate150-200", 0);
	cvShowImage("dilate150-200", dst);*/
	
	
	/*cvSmooth(inputImage, outputImage, CV_BILATERAL, 9, 9, 100, 0);
	cvSaveImage("temp.jpg", outputImage);
	outputImage = cvLoadImage("temp.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cvAdaptiveThreshold(outputImage, outputImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 29, 15);*/
	
	/*inputImage = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	cvAdaptiveThreshold(inputImage, outputImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 29, 15);
	cvSaveImage("withoutSmooth.jpg", outputImage);*/
	
	
	/*cvReleaseImage(&bin);
	cvReleaseImage(&smoothImage);*/
	//cvReleaseImage(&smoothImage);
	//��������� ������
	//IplImage *gray = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 1 );
	//IplImage *dst = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 1 );
	////cvCvtColor(inputImage, gray, CV_RGB2GRAY);
	//cvCanny(bin, dst, 10, 100, 3);
	//cvSaveImage("kontur.jpg", dst);
	//cvReleaseImage(&dst);


	/*IplImage* bin = cvCreateImage( cvGetSize(inputImage), IPL_DEPTH_8U, 1);
	cvConvertImage(inputImage, bin, CV_BGR2GRAY);*/
	
	//������ ���������� ������ �� �����������
	//int width = GetSystemMetrics(0);
	//� ���������
	//int height = GetSystemMetrics(1);

	/*//�������� ���� ��� ������ �������� �����������
	cvNamedWindow( "original", 0 );
	//��������� ������ ����
	cvResizeWindow("original", width*0.6, height*0.6);
	//������� ����
	cvMoveWindow("original", width*0.15, height*0.2);
	//������� ������� ����������� � ��� ����
	cvShowImage("original", inputImage);*/
	

	//������� ����� � ������ ��� �������������� �����������
	//IplImage *outputImage1 = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 3);
	/*IplImage *outputImage1 = cvCloneImage(inputImage);
	cvSmooth(inputImage, outputImage1, CV_GAUSSIAN, 9, 9);
	cvSaveImage("smooth.jpg", outputImage1);*/
	
	//�������� �������������� ����������� � ���������� �����
	//cvAdaptiveThreshold(inputImage, outputImage1, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 99, 15);
	//�������� �������������� ����������� � ���������� �����
	//cvConvertImage(inputImage, outputImage1, CV_BGR2GRAY);
	//cvThreshold(outputImage1,outputImage1,(double) 15,155,CV_THRESH_BINARY);
	
	/*cvNamedWindow( "original gray", 0 );
	cvShowImage("original gray", outputImage1);
	cvResizeWindow("original gray", width*0.95, height*0.95);*/
	/*cvAdaptiveThreshold(outputImage1, outputImage1, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 79, 15);
	cvAdaptiveThreshold(outputImage1, outputImage1, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 29, 15);*/

	//������� ��������� ����������� � ������� �������� ����� � �������������
	//������� ����� � ������ ��� �������������� �����������
	/*IplImage *outputImage = cvCreateImage(cvSize(gray->width,gray->height), IPL_DEPTH_8U, 1);
	for (int i = 3; i <= 101; i += 2) {
		for (int j = 0; j <= 12; j += 1) {
			cvAdaptiveThreshold(gray, outputImage, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, i, j);
			char *fileName = new char [10];
			strcpy(fileName, "output");
			char *number = new char [2];
			itoa(i, number, 10);
			strcat(fileName, number);
			strcat(fileName, "_");
			itoa(j, number, 10);
			strcat(fileName, number);
			strcat(fileName, ".jpg");
			cvSaveImage(fileName, outputImage);
		}
		printf("%s%d\n", "block size finished: ", i);
	}*/
	//cvResize(inputImage, outputImage1, CV_INTER_AREA);
	/*//�������� ���� ��� ������ ��������� �����������
	cvNamedWindow( "outptut1", 0 );
	//��������� ������ ����
	cvResizeWindow("outptut1", width*0.95, height*0.95);
	//������� ����
	//cvMoveWindow("outptut1", width-500-width*0.6, height-height*0.6-100);
	cvMoveWindow("outptut1", 0, 0);
	//������� �������� ����������� � ��� ����
	cvShowImage("outptut1", outputImage1);*/
	

	//�������� ����������� � ��������� ��������
	//IplImage *skeletImage = buildSkeleton(outputImage1);
	
	

	/*//�������� ���� ��� ������ ��������� �����������
	cvNamedWindow( "skelet", 0 );
	//��������� ������ ����
	cvResizeWindow("skelet", width*0.4, height*0.4);
	//������� ����
	cvMoveWindow("skelet", width-200-width*0.6, height-height*0.6+100);
	//������� �������� ����������� � ��� ����
	cvShowImage("skelet", skeletImage);*/
	//�������� �������� ����������� � ��� ����
	//cvSaveImage("output.jpg", skeletImage);
	//��������� ������ �� ��� ����������� �������
	//cvReleaseImage(&skeletImage);
		
	/*cvNamedWindow( "outptut2", 0 );
	cvResizeWindow("outptut2", width*0.4, height*0.4);
	cvMoveWindow("outptut2", width-width*0.5, height-height*0.5);
	cvShowImage("outptut2", outputImage2);*/
	
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
	//cvReleaseImage(&erode);
	//cvReleaseImage(&dilate);
	cvReleaseImage(&gray);
	cvReleaseImage(&dst);
	cvReleaseImage(&sum);
	cvReleaseImage(&improvedImage);
	//cvReleaseImage(&outputImage);
	//cvReleaseImage(&outputImage1);
	//cvReleaseImage(&outputImage1);
	//cvReleaseImage(&outputImage3);
	return 1;
}
#endif
#endif


#define MyComment1
#ifndef MyComment1
#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

void EnclosingCircle(IplImage* _image)
{
        assert(_image!=0);

        IplImage* bin = cvCreateImage( cvGetSize(_image), IPL_DEPTH_8U, 1);

        // ������������ � �������� ������
        cvConvertImage(_image, bin, CV_BGR2GRAY);
        // ������� �������
        cvCanny(bin, bin, 50, 200);

        cvNamedWindow( "bin", 1 );
        cvShowImage("bin", bin);

        // ��������� ������ ��� ��������
        CvMemStorage* storage = cvCreateMemStorage(0);
        CvSeq* contours=0;

        // ������� �������
        int contoursCont = cvFindContours( bin, storage,&contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));

        assert(contours!=0);

        // ������� ��� �������
        for( CvSeq* current = contours; current != NULL; current = current->h_next ){
                CvPoint2D32f center;
                float radius=0;
                // ������� ��������� ����������
                cvMinEnclosingCircle(current, & center, &radius);
                // ������
                cvCircle(_image, cvPointFrom32f(center), radius, CV_RGB(255, 0, 0), 1, 8);
        }

        // ����������� �������
        cvReleaseMemStorage(&storage);
        cvReleaseImage(&bin);
}

int main(int argc, char* argv[])
{
        IplImage *src=0, *dst=0;

        // ��� �������� ������� ������ ����������
        char* filename = argc >= 2 ? argv[1] : "Image0.jpg";
        // �������� ��������
        src = cvLoadImage(filename, 1);

        printf("[i] image: %s\n", filename);
        assert( src != 0 );

        // ������� �����������
        cvNamedWindow( "original", 1 );
        cvShowImage( "original", src );

        dst = cvCloneImage(src);

        // ����������
        EnclosingCircle(dst);

        cvNamedWindow( "circles", 1 );
        cvShowImage( "circles", dst);

        // ��� ������� �������
        cvWaitKey(0);

        // ����������� �������
        cvReleaseImage(&src);
        cvReleaseImage(&dst);
        // ������� ����
        cvDestroyAllWindows();
        return 0;
}
#endif

#define MyComment2
#ifndef MyComment2
#include "D:\OpenCV2.3.1x32\modules\core\include\opencv2\core\core_c.h"
#include "D:\OpenCV2.3.1x32\modules\imgproc\include\opencv2\imgproc\imgproc_c.h"
#include <stdio.h>
#include <windows.h>
#include <highgui.h>

int main()
{
        // ��������� Bitmap - BMP ����
        long s=10000000;
        unsigned char* out_bitmap=new unsigned char [s];
        FILE *f;
        f=fopen("out.bmp","rb");        
        if (f!=NULL)
        {
			printf("%s", "sss");
                long i=0;
                do{
                        out_bitmap[i]=fgetc(f);
                        i++;
                }while(!feof(f));
                fclose(f);

                // ��������� Bitmap � Image (��������� ��� ������ - ����� ����� ������)
                DWORD offset=0;
                DWORD x=0,y=0;
                WORD Bit=0;
                DWORD a,Size=0;
                int pointer=10;
                memcpy(&offset,&out_bitmap[pointer],4);pointer+=8;
                memcpy(&x,&out_bitmap[pointer],4);pointer+=4;
                memcpy(&y,&out_bitmap[pointer],4);pointer+=6;
                memcpy(&Bit,&out_bitmap[pointer],2);pointer+=2;

                IplImage* img = 0;  

                if (Bit!=24) return 0;
                memcpy(&a,&out_bitmap[pointer],4);pointer+=4;
                if (a!=0) return 0;
                img=cvCreateImage(cvSize(x,y),8,3);             
                uchar* ptr = (uchar*) (img->imageData);
                memcpy(ptr,&out_bitmap[offset],img->widthStep*img->height-10000); 
                // ������ ��� ����� ������� � �����������
                IplImage* Gray=cvCreateImage(cvSize(x,y),8,1);
                cvCvtColor(img, Gray, CV_RGB2GRAY );
                cvThreshold( Gray, Gray, 128, 255, CV_THRESH_BINARY );

                //������� � 24 ���
                cvCvtColor(Gray,img, CV_GRAY2RGB );
                memcpy(&out_bitmap[offset],ptr,img->widthStep*img->height);

                cvReleaseImage(&img);
                cvReleaseImage(&Gray);

                //�� � ������ ��������� � �������� ����
                f=fopen("out2.bmp","wb");       
                fwrite(out_bitmap,1,i,f);
                fclose(f);
        }       
        delete out_bitmap;
		int c;
		//while(1) {
			c=cvWaitKey(10);
			// escape key terminates program
			//if(c == 27)
			//break;
		//}
		return 0;
}
#endif

#define no_camera
#ifndef no_camera

int _tmain(int argc, _TCHAR* argv[])
{
	int c;
	IplImage *image;
	CvCapture* capture = cvCaptureFromCAM(1);
	
	/*int width = GetSystemMetrics(0);
	int height = GetSystemMetrics(1);*/
	
	cvNamedWindow("mainWin", 0);
	cvMoveWindow("mainWin", 346, 144);
	cvResizeWindow("mainWin", 640, 480);
	while(1)
	{
		image=cvQueryFrame(capture);
		cvFlip(image, NULL, 1);
		cvShowImage("mainWin", image);
		c = cvWaitKey(10);
		if(c == 27){
			cvSaveImage("camera_frame.jpg", image);
			break;}
	}
	cvDestroyAllWindows();
	cvReleaseImage(&image);
	return 0;
}
#endif

#define no_adaptiveAndThreshold
#ifndef no_adaptiveAndThreshold
IplImage *Igray=0, *It = 0, *Iat;
int main( int argc, char** argv )
{
	if(argc != 7){return -1; }
 
	// ��������� ������
	double threshold = (double)atof(argv[1]);
	int threshold_type = atoi(argv[2]) ?
		CV_THRESH_BINARY : CV_THRESH_BINARY_INV;
	int adaptive_method = atoi(argv[3]) ?
	CV_ADAPTIVE_THRESH_MEAN_C : CV_ADAPTIVE_THRESH_GAUSSIAN_C;
	int block_size = atoi(argv[4]);
	double offset = (double)atof(argv[5]);
 
	// ��������� ����������� � �����-����� �������
	if((Igray = cvLoadImage( argv[6], CV_LOAD_IMAGE_GRAYSCALE)) == 0){
	return -1;}
 
	// ������ �����-����� �������� �����������
	It = cvCreateImage(cvSize(Igray->width,Igray->height),
	IPL_DEPTH_8U, 1);
	Iat = cvCreateImage(cvSize(Igray->width,Igray->height),
	IPL_DEPTH_8U, 1);
 
	// �����
	cvThreshold(Igray,It,threshold,255,threshold_type);
	cvAdaptiveThreshold(Igray, Iat, 255, adaptive_method,
	threshold_type, block_size, offset);
 
	// ������ ���� ��� �����������
	cvNamedWindow("Raw",1);
	cvNamedWindow("Threshold",1);
	cvNamedWindow("Adaptive Threshold",1);
 
	// ������� ����������
	cvShowImage("Raw",Igray);
	cvShowImage("Threshold",It);
	cvShowImage("Adaptive Threshold",Iat);
	cvWaitKey(0);
 
	// ����������� �������
	cvReleaseImage(&Igray);
	cvReleaseImage(&It);
	cvReleaseImage(&Iat);
	cvDestroyWindow("Raw");
	cvDestroyWindow("Threshold");
	cvDestroyWindow("Adaptive Threshold");
	return(0);
}
#endif


