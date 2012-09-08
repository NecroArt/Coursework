#include "stdafx.h"

#define MyCode
#ifdef MyCode

#include <Windows.h>
#include <highgui.h>
#include <cv.h>
#include "skeletonization.h"
#include "analysis.h"


using namespace std;

void sleep () {
	Sleep(3000);
}

void pause () {
	printf("%s", "press any key to continue\n");
	_gettch();
}

#define MyCode1
#ifdef MyCode1
int main (int argc, char** argv) {
	IplImage *inputImage = 0;
	// имя картинки задаётся первым параметром
    //char* filename = argc == 2 ? argv[1] : "Image0.jpg";
	//char* outputname
    // получаем картинку
	char* filename = argc == 2 ? argv[1] : "Image0.jpg";
	inputImage = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	//inputImage = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED);
	//IplImage *Igray = cvLoadImage( argv[6], CV_LOAD_IMAGE_GRAYSCALE);
    printf("[i] image: %s\n", filename);
    if (!inputImage) {
		printf("%s", "image not found\n");
		pause();
		exit(0);
	}

	//узнаем разрешение экрана по горизонтали
	//int width = GetSystemMetrics(0);
	//и вертикали
	//int height = GetSystemMetrics(1);

	/*//создадим окно для вывода входного изображения
	cvNamedWindow( "original", 0 );
	//установим размер окна
	cvResizeWindow("original", width*0.6, height*0.6);
	//сдвинем окно
	cvMoveWindow("original", width*0.15, height*0.2);
	//выведем входное изображение в это окно
	cvShowImage("original", inputImage);*/
	

	//выделим место в памяти под бинаризованное изображение
	IplImage *outputImage1 = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
	//создадим бинаризованное изображение в выделенном месте
	//cvAdaptiveThreshold(inputImage, outputImage1, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 99, 15);
	//создадим бинаризованное изображение в выделенном месте
	cvAdaptiveThreshold(inputImage, outputImage1, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 29, 15);

	//выведем несколько изображений с разными размером блока и коэффициентом
	//выделим место в памяти под бинаризованное изображение
	/*IplImage *outputImage = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
	for (int i = 3; i <= 50; i += 2) {
		for (int j = 13; j <= 24; j += 1) {
			cvAdaptiveThreshold(inputImage, outputImage, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, i, j);
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
	/*//создадим окно для вывода выходного изображения
	cvNamedWindow( "outptut1", 0 );
	//установим размер окна
	cvResizeWindow("outptut1", width*0.95, height*0.95);
	//сдвинем окно
	//cvMoveWindow("outptut1", width-500-width*0.6, height-height*0.6-100);
	cvMoveWindow("outptut1", 0, 0);
	//выведем выходное изображение в это окно
	cvShowImage("outptut1", outputImage1);*/
	

	//создадим изображение с утонченым скелетом
	IplImage *skeletImage = buildSkeleton(outputImage1);
	bool n = true;
	for( int y=0; y<skeletImage->height; y++ ) {
		uchar* ptr = (uchar*) (skeletImage->imageData + y * skeletImage->widthStep);
		for( int x=0; x < skeletImage->width; x++ ) {
			if (ptr[x] != 0 && ptr[x] != 255) {
				printf ("%s%d%s%d%s%d\n", "found ", ptr[x], " at string ", y, " on position ", x);
				n = false;
			}
			if (!n) break;
		}
		if (!n) break;
	}
	/*//создадим окно для вывода выходного изображения
	cvNamedWindow( "skelet", 0 );
	//установим размер окна
	cvResizeWindow("skelet", width*0.4, height*0.4);
	//сдвинем окно
	cvMoveWindow("skelet", width-200-width*0.6, height-height*0.6+100);
	//выведем выходное изображение в это окно
	cvShowImage("skelet", skeletImage);*/
	//сохраним выходное изображение в это окно
	cvSaveImage("output.jpg", skeletImage);
	//освободим память из под изображения скелета
	cvReleaseImage(&skeletImage);

	/*//создадим текстовый файл, в которым будет записано изображение попиксельно
	FILE *f;
    f = fopen("data.txt","w");
	fwrite(, 1, strlen(), f);
	fclose(f);*/
	
	/*IplImage *outputImage2;

	outputImage2 = cvCreateImage(cvSize(inputImage->width,inputImage->height), IPL_DEPTH_8U, 1);
	cvAdaptiveThreshold(inputImage, outputImage2, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 71, 15);
		
	cvNamedWindow( "outptut2", 0 );
	cvResizeWindow("outptut2", width*0.4, height*0.4);
	cvMoveWindow("outptut2", width-width*0.5, height-height*0.5);
	cvShowImage("outptut2", outputImage2);
	//cvSaveImage("output.jpg", outputImage);*/
	
	printf("All done\n");
	pause();
	/*while( 1 )
	{
		if( cvWaitKey( 100 ) == 27 )
		break;
	}*/
	cvDestroyAllWindows();
	//cvReleaseImage(&inputImage);
	//cvReleaseImage(&outputImage1);
	//cvReleaseImage(&outputImage);
	/*cvReleaseImage(&outputImage2);*/
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

        // конвертируем в градации серого
        cvConvertImage(_image, bin, CV_BGR2GRAY);
        // находим границы
        cvCanny(bin, bin, 50, 200);

        cvNamedWindow( "bin", 1 );
        cvShowImage("bin", bin);

        // хранилище памяти для контуров
        CvMemStorage* storage = cvCreateMemStorage(0);
        CvSeq* contours=0;

        // находим контуры
        int contoursCont = cvFindContours( bin, storage,&contours,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));

        assert(contours!=0);

        // обходим все контуры
        for( CvSeq* current = contours; current != NULL; current = current->h_next ){
                CvPoint2D32f center;
                float radius=0;
                // находим параметры окружности
                cvMinEnclosingCircle(current, & center, &radius);
                // рисуем
                cvCircle(_image, cvPointFrom32f(center), radius, CV_RGB(255, 0, 0), 1, 8);
        }

        // освобождаем ресурсы
        cvReleaseMemStorage(&storage);
        cvReleaseImage(&bin);
}

int main(int argc, char* argv[])
{
        IplImage *src=0, *dst=0;

        // имя картинки задаётся первым параметром
        char* filename = argc >= 2 ? argv[1] : "Image0.jpg";
        // получаем картинку
        src = cvLoadImage(filename, 1);

        printf("[i] image: %s\n", filename);
        assert( src != 0 );

        // покажем изображение
        cvNamedWindow( "original", 1 );
        cvShowImage( "original", src );

        dst = cvCloneImage(src);

        // показываем
        EnclosingCircle(dst);

        cvNamedWindow( "circles", 1 );
        cvShowImage( "circles", dst);

        // ждём нажатия клавиши
        cvWaitKey(0);

        // освобождаем ресурсы
        cvReleaseImage(&src);
        cvReleaseImage(&dst);
        // удаляем окна
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
        // Загружаем Bitmap - BMP файл
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

                // Переводим Bitmap в Image (извиняюсь что коряво - делал очень быстро)
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
                // Делаем для теста перевод в монохромное
                IplImage* Gray=cvCreateImage(cvSize(x,y),8,1);
                cvCvtColor(img, Gray, CV_RGB2GRAY );
                cvThreshold( Gray, Gray, 128, 255, CV_THRESH_BINARY );

                //Обратно в 24 бит
                cvCvtColor(Gray,img, CV_GRAY2RGB );
                memcpy(&out_bitmap[offset],ptr,img->widthStep*img->height);

                cvReleaseImage(&img);
                cvReleaseImage(&Gray);

                //Ну а теперь сохраняем в выходной файл
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

#define camera
#ifndef camera
#include <highgui.h>
#include <cv.h>

int _tmain(int argc, _TCHAR* argv[])
{
	int c;
	// allocate memory for an image
	IplImage *img;
	// capture from video device #1
	CvCapture* capture = cvCaptureFromCAM(1);
	// create a window to display the images
	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);
	// position the window
	cvMoveWindow("mainWin", 5, 5);
	while(1)
	{
		// retrieve the captured frame
		img=cvQueryFrame(capture);
		// show the image in the window
		cvShowImage("mainWin", img );
		// wait 10 ms for a key to be pressed
		c=cvWaitKey(10);
		// escape key terminates program
		if(c == 27)
		break;
	}
	return 0;
}
#endif

//#define adaptiveAndThreshold
#ifdef adaptiveAndThreshold
IplImage *Igray=0, *It = 0, *Iat;
int main( int argc, char** argv )
{
	if(argc != 7){return -1; }
 
	// Командная строка
	double threshold = (double)atof(argv[1]);
	int threshold_type = atoi(argv[2]) ?
		CV_THRESH_BINARY : CV_THRESH_BINARY_INV;
	int adaptive_method = atoi(argv[3]) ?
	CV_ADAPTIVE_THRESH_MEAN_C : CV_ADAPTIVE_THRESH_GAUSSIAN_C;
	int block_size = atoi(argv[4]);
	double offset = (double)atof(argv[5]);
 
	// Загружаем изображение в чёрно-белом формате
	if((Igray = cvLoadImage( argv[6], CV_LOAD_IMAGE_GRAYSCALE)) == 0){
	return -1;}
 
	// Создаём чёрно-белые выходные изображения
	It = cvCreateImage(cvSize(Igray->width,Igray->height),
	IPL_DEPTH_8U, 1);
	Iat = cvCreateImage(cvSize(Igray->width,Igray->height),
	IPL_DEPTH_8U, 1);
 
	// Порог
	cvThreshold(Igray,It,threshold,255,threshold_type);
	cvAdaptiveThreshold(Igray, Iat, 255, adaptive_method,
	threshold_type, block_size, offset);
 
	// Создаём окна для результатов
	cvNamedWindow("Raw",1);
	cvNamedWindow("Threshold",1);
	cvNamedWindow("Adaptive Threshold",1);
 
	// Выводим результаты
	cvShowImage("Raw",Igray);
	cvShowImage("Threshold",It);
	cvShowImage("Adaptive Threshold",Iat);
	cvWaitKey(0);
 
	// Освобождаем ресурсы
	cvReleaseImage(&Igray);
	cvReleaseImage(&It);
	cvReleaseImage(&Iat);
	cvDestroyWindow("Raw");
	cvDestroyWindow("Threshold");
	cvDestroyWindow("Adaptive Threshold");
	return(0);
}
#endif