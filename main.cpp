#include <iostream>
#include "LinkedList.h"
#include "Map.h"
using namespace std;

struct Point {
	int x, y;
};

struct graphNode {
	int nodeId, weight;
};


struct stackElement {
	int x, y, distance;
};


LinkedList<graphNode>* getCityNeighbours(Map& map, int x, int y) {
	LinkedList<graphNode>* adjacencyList = new LinkedList<graphNode>;
	LinkedList<stackElement> stack;

	bool** visitedCells = new bool* [map.n];
	for (int i = 0; i < map.n; i++) {
		visitedCells[i] = new bool[map.m];
		for (int j = 0; j < map.m; j++) {
			visitedCells[i][j] = false;
		}
	}
	visitedCells[x][y] = true;
	stackElement toPush = { x,y,0 };
	stack.push(toPush);

	while (!stack.empty()) {
		stackElement* current = stack.pop();

		int currentX = current->x;
		int currentY = current->y;
		int currentDistance = current->distance;

		delete current;
		// Visit neighbours of the current cell
		Point neighbours[4] = { {currentX - 1, currentY}, {currentX + 1, currentY}, {currentX, currentY - 1}, {currentX, currentY + 1} };
		for (int i = 0; i < 4; i++) {
			int neighbourX = neighbours[i].x;
			int neighbourY = neighbours[i].y;

			if (map.pointIsValid(neighbourX, neighbourY)) {

				if (visitedCells[neighbourX][neighbourY]) {
					continue;
				}				
				char neighbourChar = map.grid[neighbourX][neighbourY];
					// Check if neighbour is a city
				if (neighbourChar == CITY_CHAR) {
					graphNode toPush = { map.getCityIndexByCoords(neighbourX, neighbourY), currentDistance + 1 };
					adjacencyList->push(toPush);
				}
				else if (neighbourChar == ROAD_CHAR) {
					// add it to the stack of visited cells
					visitedCells[neighbourX][neighbourY] = true;
					stackElement neighbourStackElement = { neighbourX, neighbourY, currentDistance + 1 };
					stack.push(neighbourStackElement);
				}
			}
		}
	}
	for (int i = 0; i < map.n; i++) {
		delete[] visitedCells[i];
	}
	delete[] visitedCells;
	return adjacencyList;
}


int** getMatrix(Map& map) {
	return nullptr;
}



int main() {
	int n, m;
	cin >> n;
	cin >> m;
	Map map(n, m);
	map.getMap();
	/*for (int j = 0; j < map.m; j++) {
		for (int i = 0; i < map.n; i++) {
			cout << map.grid[i][j];
		}
		cout << endl;
	}*/
	map.getCityNames();
	/*for (int i = 0; i < map.noOfCities; i++) {
		cout << map.cityNameList[i] << " " << map.cityXpos[i] << " " << map.cityYpos[i] << "  ";
	}*/
	LinkedList<graphNode>** adjacencyList = new LinkedList<graphNode>*[map.noOfCities];
	for (int i = 0; i < map.noOfCities; i++) {
		adjacencyList[i] = getCityNeighbours(map, map.cityXpos[i], map.cityYpos[i]);
	}

	// upewnic sie ze bfs to bfs a nie dfs
	//int** mapMatrix = getMatrix(map);
	return 0;
}