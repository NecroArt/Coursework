#include "stdafx.h"
#ifndef ANALISYS_H
#define ANALISYS_H
#include <vector>

using namespace std;

	struct point {
		int x, y;
	};

class object {
private:
	struct coordinates {
		float latitude, longitude;
	};

public:
	tm imageTime;
	vector <point> skeleton;
	coordinates gps;

	object();
	void addSkelPoint(point newSkeleton);	
	
	void calculateCoordinates(float cameraLatitude, float cameraLongitude);
	void calculateDistance();
};

object::object () {
}

void object::addSkelPoint(point newPoint) {
	point addingPoint;
	addingPoint.x = newPoint.x;
	addingPoint.y = newPoint.y;
	skeleton.push_back(addingPoint);
}

vector<object> findObjects (IplImage *binImage) {
	vector<object> objects;
	return objects;
}

float calculateSpeed(object firstObject, object secondObject);
vector <point> calculatePath(vector <object> objects);

#endif