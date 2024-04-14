#pragma once


#include <cmath>
#include <memory>
#include <random>
#include "graph.h"
#include "Path.h"

// ����� ���������� �������
class Ant {
	// ������� ������������� ������, ����� ���������� ���
	std::default_random_engine &random_engine;
	// ������� ������� �������
	size_t location;
	// �������, � ������� ����� �������
	size_t start;
	// ������ ���� ������(������� ������� ��� ������� ��� �������-������)
	std::unique_ptr<Path> path;
	// ����� �� ������� ��������� ����-����
	bool canMove;
public:
	// ���������� �������
	Ant(std::default_random_engine &e, size_t loc, bool exact);
	// �������, ������� ������ ��������� ��� ��������
	size_t makeChoice(const MatrixGraph &pheromone, const MatrixGraph &distance, double alpha, double beta);
	// ��������� ������� �������
	size_t getLocation() const;
	// ��������� ������ ������, ������� ������� ��� �������
	std::unique_ptr<Path> getPath();
	// ����� �� ������� ���������� ��������
	bool canContinue() const;
	// ��������� �� ������� � ������
	bool isOnStart() const;
};
