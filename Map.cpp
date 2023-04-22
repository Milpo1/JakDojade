#include "Map.h"
using namespace std;
bool isAlpha(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) return true;
	return false;
}
Map::Map(int n, int m) {
	this->n = n;
	this->m = m;
	this->noOfCities = 0;
	this->cityXpos = nullptr;
	this->cityYpos = nullptr;
	this->cityNameListIndexed = nullptr;
	this->hasRoads = false;
	this->grid = new char* [n];
	for (int i = 0; i < n; i++) this->grid[i] = new char[m];
	this->cityNameList = new LinkedList<City>[NUMBER_OF_CHARS * NUMBER_OF_CHARS * NUMBER_OF_CHARS];
}
bool Map::pointIsValid(int x, int y) {
	if (x < 0 || x >= this->n || y < 0 || y >= this->m) return false;
	return true;
}
String* Map::findNameNearPoint(int x, int y) {
	String* name = new String;
	int nameX = -1;
	int nameY = -1;
	int candidateX[] = { -1,0,1,-1,0,1,-1,1 };
	int candidateY[] = { -1,-1,-1,1,1,1,0,0 };
	int noCandidates = sizeof(candidateX) / sizeof(int);
	for (int i = 0; i < noCandidates; i++) {
		if (this->pointIsValid(x+candidateX[i], y+candidateY[i]) && isAlpha(this->grid[x+candidateX[i]][y+candidateY[i]])) {
			nameX = x+candidateX[i];
			nameY = y+candidateY[i];
			break;
		}
	}
	if (nameX == -1 || nameY == -1) {
		return name;
	}
	int oldNameX = nameX;
	while (this->pointIsValid(nameX - 1, nameY) && isAlpha(this->grid[nameX - 1][nameY])) {
		nameX--;
	}
	while (this->pointIsValid(oldNameX + 1, nameY) && isAlpha(this->grid[oldNameX + 1][nameY])) {
		oldNameX++;
	}

	for (int n = nameX; n <= oldNameX; n++) {
		char toAppend[] = { this->grid[n][nameY],'\0' };
		*name = *name + toAppend;
		this->grid[n][nameY] = MAP_EMPTY;
	}
	return name;
}
int Map::hashStr(char* str)
{
	int hash;
	if (str[0] == '\0') return NUMBER_OF_CHARS - 1;
	hash = NUMBER_OF_CHARS*NUMBER_OF_CHARS*(str[0]-'0');
	if (str[1] == '\0') return hash + NUMBER_OF_CHARS*NUMBER_OF_CHARS - 1;
	hash += NUMBER_OF_CHARS*(str[1] - '0');
	if (str[2] == '\0') return hash + NUMBER_OF_CHARS - 1;
	hash += str[2] - '0';
	return hash;
}
int Map::getCityIndexByName(char* name)
{
	LinkedList<City>* cityNameList = &this->cityNameList[this->hashStr(name)];
	Node<City>* ptr = cityNameList->head;
	while (ptr != nullptr) {
		char* nameToCmp = ptr->data.name.str;
		if (strcmp(nameToCmp, name) == 0) {
			return ptr->data.id;
		}
		ptr = ptr->next;
	}
	return -1;
}
void Map::getCityNames() {
	this->cityNameListIndexed = new City*[this->noOfCities];
	this->cityXpos = new int[this->noOfCities];
	this->cityYpos = new int[this->noOfCities];
	int foundCities = 0;
	for (int j = 0; j < this->m; j++) {
		for (int i = 0; i < this->n; i++) {
			if (this->grid[i][j] == CITY_CHAR) {
				String* namePtr = findNameNearPoint(i, j);
				City toPush = { *namePtr, foundCities };
				int hash = this->hashStr(namePtr->str);
				this->cityNameListIndexed[foundCities] = this->cityNameList[hash].put(toPush);
				delete namePtr;
				this->cityXpos[foundCities] = i;
				this->cityYpos[foundCities] = j;
				foundCities++;
			}
			else if (!this->hasRoads && this->grid[i][j] == ROAD_CHAR) {
				this->hasRoads = true;
			}
		}
	}
}

void Map::getMap() {
	int mode = 0;
	int pos = 0;
	cin.get();
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			this->grid[i][j] = cin.get();
			if (this->grid[i][j] == CITY_CHAR) {
				this->noOfCities++;
			}
		}
		if (j != m-1) cin.get();
	}
}
Map::~Map() {
	for (int i = 0; i < n; i++) delete this->grid[i];
	delete[] this->grid;
	delete[] this->cityNameListIndexed;
	delete[] this->cityNameList;
	delete[] this->cityXpos;
	delete[] this->cityYpos;
}

int Map::getCityIndexByCoords(int x, int y) {
	for (int i = 0; i < noOfCities; i++) {
		if (cityXpos[i] == x && cityYpos[i] == y) {
			return i;
		}
	}
	return -1; // City not found
}