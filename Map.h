#pragma once
#include "MyString.h"
#include <iostream>
#define CITY_CHAR '*'
#define MAP_EMPTY '.'
#define ROAD_CHAR '#'
bool isAlpha(char c);

class Map {
public:
	int n, m;
	String* cityNameList;
	int* cityXpos;
	int* cityYpos;
	int noOfCities;
	bool hasRoads;
	char** grid;
	Map(int n, int m);
	~Map();
	void getMap();
	String* getCityNames();
	bool pointIsValid(int x, int y);
	String* findNameNearPoint(int x, int y);
	int getCityIndexByCoords(int x, int y);
	int getCityIndexByName(String& name);
};
