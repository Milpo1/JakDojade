#include <iostream>
#include "Map.h"
#include <chrono>
using namespace std::chrono;
using namespace std;

#define BUFFER_SIZE 32
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
		if (currentCityId == destCityId) {
			break;
		};
		LinkedList<graphNode>* neighbours = adjacencyList[currentCityId];
		Node<graphNode>* ptr = neighbours->head;
		for (int i = 0; i < neighbours->size; i++) {
			int neighbourCityId = ptr->data.nodeId;
			int edgeWeight = ptr->data.weight;
			int currentDistance = distances[currentCityId];
			int neighbourDistance = distances[neighbourCityId];
			bool neighbourVisited = visited[neighbourCityId];
			if (!neighbourVisited && currentDistance != MAXINT
				&& currentDistance + edgeWeight < neighbourDistance) {

				distances[neighbourCityId] = distances[currentCityId] + edgeWeight;
				predecessors[neighbourCityId] = currentCityId;
				graphNode toPush = { neighbourCityId, distances[neighbourCityId] };
				stack.priority_push(toPush, toPush.weight); // make it priority push
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
			cout << " " << map.cityNameListIndexed[*route.pop()]->name;
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

void fastscan(char* str) {
	char c = getchar();
	int i = 0;
	while (c != ' ' && c != '\n') {
		str[i] = c;
		i++;
		c = getchar();
	}
	str[i] = '\0';
}

int stringToInteger(char* str) {
	int result = 0;
	int sign = 1;

	// handle negative numbers
	if (*str == '-') {
		sign = -1;
		str++;
	}

	// convert each digit in the string to an integer
	while (*str != '\0') {
		if (*str >= '0' && *str <= '9') {
			result = result * 10 + (*str - '0');
		}
		else {
			// invalid character
			return 0;
		}
		str++;
	}

	// apply the sign to the result
	result *= sign;

	return result;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
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
	//auto start = high_resolution_clock::now(); 
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(stop - start); 
	getchar();
	for (int i = 0; i < noOfAirlines; i++) {
		//stop = high_resolution_clock::now();
		//duration = duration_cast<microseconds>(stop - start);
		//cout << duration.count() << " ";
		char sourceCityName[BUFFER_SIZE], destCityName[BUFFER_SIZE], airlineWeightStr[BUFFER_SIZE];
		fastscan(sourceCityName);
		fastscan(destCityName);
		fastscan(airlineWeightStr);
		int airlineWeight = stringToInteger(airlineWeightStr);


		int sourceCityId = map.getCityIndexByName(sourceCityName);
		int destCityId = map.getCityIndexByName(destCityName);
		LinkedList<graphNode>* cityNeighbourList = adjacencyList[sourceCityId];
		Node<graphNode>* node = cityNeighbourList->head;
		bool found = false;
		while (node != nullptr) { // PRZYSPIESZYC !!!
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
		} //
		graphNode toAppend = { destCityId,airlineWeight };
		//start = high_resolution_clock::now();
		cityNeighbourList->priority_push(toAppend, destCityId);
	}
	int noOfQueries;
	cin >> noOfQueries;
	getchar();
	for (int i = 0; i < noOfQueries; i++) {
		char sourceCityName[BUFFER_SIZE], destCityName[BUFFER_SIZE], printRouteStr[BUFFER_SIZE];
		fastscan(sourceCityName);
		fastscan(destCityName);
		fastscan(printRouteStr);
		int printRoute = stringToInteger(printRouteStr);
		dijkstra(map, adjacencyList, map.getCityIndexByName(sourceCityName), map.getCityIndexByName(destCityName), printRoute);
	}

	for (int i = 0; i < map.noOfCities; i++) {
		delete adjacencyList[i];
	}
	delete[] adjacencyList;
	return 0;
}