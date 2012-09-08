#include "stdafx.h"
#ifndef UI_H
#define UI_H
#include <vector>

using namespace std;
struct ImageWithExif {
	IplImage *image;
	char *dateTimeOriginal; // date/time string of image
	focalLenght; //эффективное фокусное расстрояние
	coefHorScaleFactor; //горизонтальный масштабный коэффициент
	coefVertScaleFactor; //вертикальный масштабный коэффициент
	XResolution; //число пикселей по горизонтали
	YResolution; //число пикселей по вертикали
};

vector <vector <ObjectPhoto>> outputData;
struct Photo {
	int id_photo;
	string photo;
	tm date_time;
};

struct ObjectPhoto {
	unsigned int id_photo, id_object;
	float speed, distance;
	double gps_lat, gps_lon, path_x, path_y;
};
#endif