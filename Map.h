#pragma once
#include "MyString.h"
#include "LinkedList.h"
#include <iostream>
#define CITY_CHAR '*'
#define MAP_EMPTY '.'
#define ROAD_CHAR '#'
bool isAlpha(char c);

struct City {
	String name;
	int id;
};
#define NUMBER_OF_CHARS ('z' - '0' + 2)

class Map {
public:
	int n, m;
	City** cityNameListIndexed;
	LinkedList<City>* cityNameList;
	int* cityXpos;
	int* cityYpos;
	int noOfCities;
	bool hasRoads;
	char** grid;
	Map(int n, int m);
	~Map();
	void getMap();
	void getCityNames();
	bool pointIsValid(int x, int y);
	String* findNameNearPoint(int x, int y);
	int getCityIndexByCoords(int x, int y);
	int getCityIndexByName(char* name);
	int hashStr(char* str);
};
