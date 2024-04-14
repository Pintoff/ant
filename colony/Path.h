#pragma once
#include <vector>
#include <ostream>
// ����� ����
class Path {
	// ��� ����
	std::vector<size_t> path;
	// ���������
	double distance;
public:
	// ������������� ����
	Path(size_t initial);
	// ��������� ���������
	double getDistance() const;
	// ��������� �����
	size_t getNumOfSteps() const;
	// �������� ��������� ������� ��������
	size_t operator[](size_t element) const;
	// �������� ��� �� ����������� ���� (vertex) � � ���������� ����������
	void addStep(int vertex, double dist);
	// �������� �� ���������� ���� ������ �������
	bool contains(size_t location);
	// ����� ����
	friend std::ostream& operator <<(std::ostream& os, const Path& path);
};

