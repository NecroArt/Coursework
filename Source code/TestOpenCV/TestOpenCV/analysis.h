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
	
	coordinates calculateCoordinates (float cameraLatitude, float cameraLongitude, float cameraHeight);
	void calculateDistance();
};

object::object () {
}

//сравнивает два вектора скелетов друг с другом и возвращает вектор пар индексов элементов входного вектора
//которые удовлетворяют критерию равенства в функции compare2Skelets
vector <CvPoint> compareSkelets (vector <Skelet> first_skelet_vector, vector <Skelet> second_skelet_vector);

//сравнивает два скелета и возвращает true, если скелеты равны
bool compare2Skelets (Skelet first_skelet, Skelet second_skelet);

float calculateSpeed(object firstObject, object secondObject);
vector <point> calculatePath(vector <object> objects);

//находит дистанцию до объекта current_object
float findDistanceToIbject (object current_object);

//сортирует дуги скелета по длине в возрастающем порядке
void sortSkelet(vector <Arch> &Arches);

//функция для сравнения двух дуг по их длине
bool isFirstArchBigger (Arch arch1, Arch arch2);

bool compare2Skelets (Skelet first_skelet, Skelet second_skelet) {
	bool is_equal = true;
	sortSkelet(first_skelet.arch);
	sortSkelet(second_skelet.arch);
	if (abs((int) first_skelet.arch.size() - (int) second_skelet.arch.size()) > 2) {
		is_equal = false;
	}
	else {
		if ((first_skelet.arch.size() != 1) && (second_skelet.arch.size() != 1)) {
			vector <float> ratio;
			for (int i = 0; (i < first_skelet.arch.size()) && (i < second_skelet.arch.size()); i++) {
				ratio.push_back((float) first_skelet.arch.at(i).points.size() / (float) second_skelet.arch.at(i).points.size());
			}
			for (int i = 1; (i < ratio.size()) && (is_equal == true); i++) {
				float t = abs(ratio.at(i-1) - ratio.at(i));
				if (abs(ratio.at(i-1) - ratio.at(i)) > 0.14) {
					is_equal = false;
				}
			}
		}
		else {
			//сравнение скелетов при условии, что один из них состоит из одной дуги
			if (abs ((int) (first_skelet.arch.at(0).points.size() - second_skelet.arch.at(0).points.size())) > 3) {
				is_equal = false;
			}
		}
	}
	return is_equal;
}

vector <CvPoint> compareSkelets (vector <Skelet> first_skelet_vector, vector <Skelet> second_skelet_vector) {
	vector <CvPoint> values_pairs;
	for (int i = 0; i < first_skelet_vector.size(); i++) {
		for (int j = 0; j < second_skelet_vector.size(); j++) {
			if (compare2Skelets(first_skelet_vector.at(i), second_skelet_vector.at(j))) {
				CvPoint new_pair;
				new_pair.x = i;
				new_pair.y = j;
				values_pairs.push_back(new_pair);
			}
		}
	}
	return values_pairs;
}

vector<object> findObjects (IplImage *binImage) {
	vector<object> objects;
	return objects;
}

bool isFirstArchBigger (Arch arch1, Arch arch2) { 
	return (arch1.points.size() >= arch2.points.size());
}

void sortSkelet(vector <Arch> &Arches) {
	sort (Arches.begin(), Arches.end(), isFirstArchBigger);
}

#endif