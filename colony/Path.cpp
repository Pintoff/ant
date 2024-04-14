
#include <iostream>
#include "Path.h"
// добавление в список пройденных вершин
Path::Path(size_t initial) {
	path.push_back(initial);
}
// получение дистанции
double Path::getDistance() const{
	return distance;
}
// получение количества шагов
size_t Path::getNumOfSteps() const {
	return sizeof(path);
}
// содержит ли путь определенную вершину
bool Path::contains(size_t location) {
	for (size_t i = 0; i < path.size(); i++)
	{
		if (path[i] == location) {
			return true;
		}
	}
	return false;
}
// добавить вершину в список пройденных
void Path::addStep(int vertex, double dist) {
	path.push_back(vertex);
	distance += dist; // w1
}

size_t Path::operator[](size_t element) const {
	for (size_t i = 0; i < path.size(); i++)
	{
		if (path[i] == element) {
			return i;
		}
	}
	return 1;
}


std::ostream& operator <<(std::ostream& os, const Path& path) {
	for (size_t i = 0; i < path.path.size(); i++)
	{
		os << path[i] << " ";
	}
	return os;
}