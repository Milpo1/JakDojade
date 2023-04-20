#include <iostream>
#include "LinkedList.h"
#include "Map.h"
using namespace std;

#define BUFFER_SIZE 64;
const int MAXINT = 2147483647;

struct Point {
	int x, y;
};

struct graphNode {
	int nodeId, weight;
};


struct gridElement {
	int x, y, distance;
};

typedef LinkedList<graphNode>** MainAdjacencyList;

LinkedList<graphNode>* getCityNeighbours(Map& map, int x, int y) {
	LinkedList<graphNode>* adjacencyList = new LinkedList<graphNode>;
	if (!map.hasRoads) return adjacencyList;

	LinkedList<gridElement> stack;

	bool** visitedCells = new bool* [map.n];
	for (int i = 0; i < map.n; i++) {
		visitedCells[i] = new bool[map.m];
		for (int j = 0; j < map.m; j++) {
			visitedCells[i][j] = false;
		}
	}
	visitedCells[x][y] = true;
	gridElement toPush = { x,y,0 };
	stack.push(toPush);

	while (!stack.empty()) {
		gridElement* current = stack.pop();

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
				visitedCells[neighbourX][neighbourY] = true;
				char neighbourChar = map.grid[neighbourX][neighbourY];
					// Check if neighbour is a city
				if (neighbourChar == CITY_CHAR) {
					int cityId = map.getCityIndexByCoords(neighbourX, neighbourY);
					graphNode toPush = { cityId, currentDistance + 1 };
					adjacencyList->put(toPush);
				}
				else if (neighbourChar == ROAD_CHAR) {
					// add it to the stack of visited cells
					gridElement neighbourGridElement = { neighbourX, neighbourY, currentDistance + 1 };
					stack.put(neighbourGridElement);
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

void dijkstra(Map& map, MainAdjacencyList adjacencyList, int sourceCityId, int destCityId) {
	int noOfCities = map.noOfCities;
	int* distances = new int[noOfCities];
	int* predecessors = new int[noOfCities];
	bool* visited = new bool[noOfCities];
	LinkedList<graphNode> stack;

	for (int i = 0; i < noOfCities; i++) {
		distances[i] = MAXINT;
		predecessors[i] = -1;
		visited[i] = false;
	}

	distances[sourceCityId] = 0;
	graphNode toPush = { sourceCityId, 0 };
	stack.push(toPush);
	
	while (!stack.empty()) {
		graphNode* current = stack.pop();
		int currentCityId = current->nodeId;
		int currentWeight = current->weight;

		delete current;
		if (visited[currentCityId]) {
			continue;
		}
		visited[currentCityId] = true;
		LinkedList<graphNode>* neighbours = adjacencyList[currentCityId];
		Node<graphNode>* ptr = neighbours->head;
		for (int i = 0; i < neighbours->size; i++) {
			int neighbourCityId = ptr->data.nodeId;
			int edgeWeight = ptr->data.weight;
			if (!visited[neighbourCityId] && distances[currentCityId] != MAXINT
				&& distances[currentCityId] + edgeWeight < distances[neighbourCityId]) {

				distances[neighbourCityId] = distances[currentCityId] + edgeWeight;
				predecessors[neighbourCityId] = currentCityId;
				graphNode toPush = { neighbourCityId, distances[neighbourCityId] };
				stack.put(toPush);
			}
			ptr = ptr->next;
		}
	}
	for (int i = 0; i < noOfCities; i++) {
		cout << map.cityNameList[i] << " " << distances[i] << " "
			 << predecessors[i] << endl;
	}
}


int main() {
	int n, m;
	cin >> n;
	cin >> m;
	Map map(n, m);
	map.getMap();
	map.getCityNames();

	MainAdjacencyList adjacencyList = new LinkedList<graphNode>*[map.noOfCities];
	for (int i = 0; i < map.noOfCities; i++) {
		adjacencyList[i] = getCityNeighbours(map, map.cityXpos[i], map.cityYpos[i]);

		// Print the adjacency list (city id, weight)
		cout << "City " << map.cityNameList[i] << " is adjacent to: ";
		Node<graphNode>* ptr = adjacencyList[i]->head;
		for (int j = 0; j < adjacencyList[i]->size; j++) {
			int cityId = ptr->data.nodeId;
			cout << "(" << map.cityNameList[cityId] << ", " << ptr->data.weight << ") ";
			ptr = ptr->next;
		}
		cout << std::endl;

	}
	int noOfQueries;
	cin >> noOfQueries;
	char c;
	cin.get();
	for (int i = 0; i < noOfQueries; i++) {
		String sourceCity = "", destCity = "";
		while (cin.get(c) && c != ' ') {
			char toAppend[] = { c, '\0' };
			sourceCity = sourceCity + toAppend;
		}
		while (cin.get(c) && c != ' ') {
			char toAppend[] = { c, '\0' };
			destCity = destCity + toAppend;
		}
		int printRoute = cin.get() - '0';
		//dijkstra(map, adjacencyList, 0, 6);
	}

	for (int i = 0; i < map.noOfCities; i++) {
		delete adjacencyList[i];
	}
	delete[] adjacencyList;
	return 0;
}