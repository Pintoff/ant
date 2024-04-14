
#include <iostream>
#include "Path.h"
// ���������� � ������ ���������� ������
Path::Path(size_t initial) {
	path.push_back(initial);
}
// ��������� ���������
double Path::getDistance() const{
	return distance;
}
// ��������� ���������� �����
size_t Path::getNumOfSteps() const {
	return sizeof(path);
}
// �������� �� ���� ������������ �������
bool Path::contains(size_t location) {
	for (size_t i = 0; i < path.size(); i++)
	{
		if (path[i] == location) {
			return true;
		}
	}
	return false;
}
// �������� ������� � ������ ����������
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