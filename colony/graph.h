#pragma once
#include <vector>
#include <string>
#include <functional>

class MatrixGraph {
	// ������ �����
	size_t size;
	std::vector<std::vector<double>> matrix;
public:
	// ���������� ����� �� �����
	MatrixGraph(std::string filename);
	// ���������
	MatrixGraph(size_t theSize, std::function<double(size_t, size_t)> generation);
	// ����������� �� ��������� ��������
	MatrixGraph() = delete;
	// ��������� �������
	size_t getSize() const;
	// ��������� ����� ����� ����� �� ������� from � ������� to
	double get(size_t from, size_t to) const;
	// ���������� ����� ����� �� ������� from � ������� to
	void set(size_t from, size_t to, double value);

	void alter(size_t from, size_t to, std::function<void(double&)> alterator);
	// ��� ������� ���������
	void print();
};



