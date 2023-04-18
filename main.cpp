#include <iostream>
#include "Map.h"
using namespace std;

int** getMatrix(Map& map) {
	return nullptr;
}

int main() {
	int n, m;
	cin >> n;
	cin >> m;
	Map map(n, m);
	map.getMap();
	cout << isAlpha('.');
	for (int j = 0; j < map.m; j++) {
		for (int i = 0; i < map.n; i++) {
			cout << map.grid[i][j];
		}
		cout << endl;
	}
	map.getCityNames();
	for (int i = 0; i < map.noOfCities; i++) {
		cout << map.cityNameList[i] << " ";
	}

	//int** mapMatrix = getMatrix(map);
	return 0;
}