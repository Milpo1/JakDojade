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
	//if (!map.hasRoads) return adjacencyList;

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

void dijkstra(Map& map, MainAdjacencyList adjacencyList, int sourceCityId, int destCityId, bool printRoute) {
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
	cout << distances[destCityId];

	if (printRoute) {

		LinkedList<int> route;
		int routeCityId = destCityId;
		while (routeCityId != sourceCityId) {
			if (route.size >= noOfCities) break;
			routeCityId = predecessors[routeCityId];
			route.push(routeCityId);
		}
		route.pop();

		while (!route.empty()) {
			cout << " " << map.cityNameList[*route.pop()];
		}
	}
	cout << endl;

	delete[] distances;
	delete[] predecessors;
	delete[] visited;
}
void fillString(String* str) {
	char c;
	while (cin.get(c) && c != ' ') {
		char toAppend[] = { c, '\0' };
		*str = *str + toAppend;
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
	}

	int noOfAirlines;
	cin >> noOfAirlines;
	for (int i = 0; i < noOfAirlines; i++) {
		cin.get();
		String sourceCityName = "", destCityName = "";
		fillString(&sourceCityName);
		fillString(&destCityName);

		int airlineWeight;
		cin >> airlineWeight;
		int sourceCityId = map.getCityIndexByName(sourceCityName);
		int destCityId = map.getCityIndexByName(destCityName);

		LinkedList<graphNode>* cityNeighbourList = adjacencyList[sourceCityId];
		Node<graphNode>* node = cityNeighbourList->head;

		bool found = false;
		while (node != nullptr) {
			if (node->data.nodeId == destCityId) {
				if (node->data.weight > airlineWeight) {
					node->data.weight = airlineWeight;
					found = true;
					break;
				}
			}
			node = node->next;
		}
		if (found) {
			continue;
		}
		graphNode toAppend = { destCityId,airlineWeight };
		cityNeighbourList->put(toAppend);
	}

	int noOfQueries;
	cin >> noOfQueries;
	char c;
	for (int i = 0; i < noOfQueries; i++) {
		cin.get();
		String sourceCityName = "", destCityName = "";
		fillString(&sourceCityName);
		fillString(&destCityName);
		int printRoute;
		cin >> printRoute;
		dijkstra(map, adjacencyList, map.getCityIndexByName(sourceCityName), map.getCityIndexByName(destCityName), printRoute);
	}

	for (int i = 0; i < map.noOfCities; i++) {
		delete adjacencyList[i];
	}
	delete[] adjacencyList;
	return 0;
}