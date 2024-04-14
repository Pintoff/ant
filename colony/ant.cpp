#include "Ant.h"

#include <cmath>
// ������������� �������
Ant::Ant(std::default_random_engine &e, size_t loc, bool exact)
	: random_engine(e), canMove(true) {
	// ���������� �������������� �������
	if (exact) {
		location = loc;
	}
	else {
		// �������� ��������� ���������, ������� ����� ������������ �� ������� �� 0 �� loc-1
		std::uniform_int_distribution<size_t> dis(0, loc - 1);
		// ������������ �������������� �������
		location = dis(random_engine);
	}
	// ������������ ��������� ������� �������
	start = location;
	// ������������� ������ ���������� ������
	path = std::unique_ptr<Path>(new Path(location));
}

// ����� ��� �������� ������� ��������, � ����� ������� ����� �������
size_t Ant::makeChoice(const MatrixGraph &pheromone, const MatrixGraph &distance, double alpha, double beta) {
	size_t from = location;
	// ��������� ������������, ������ ������
	if (path->getNumOfSteps() == distance.getSize()) {
		// ������� ������ �� ����� ���������
		canMove = false;
		// ������������ ������� ������� �� ������
		location = start;
		// ���������� ������� � ���������� ����
		path->addStep(start, distance.get(from, start));
		return start;
	}

	// ����� �������
	std::vector<double> neighbourProbabilityMarkers;
	double maxProbability = 0.0;
	double curProbability;
	for (size_t i = 0, size = distance.getSize(); i < size; i++) {
		// �����������, ����� ������� ������� � �� �� �������
		if (i == from) { 
			neighbourProbabilityMarkers.push_back(0);
		}
		// �����������, ����� ������� ������� ���� ������� ������
		else if (path->contains(i)) {
			neighbourProbabilityMarkers.push_back(0);
		}
		else {
			// ������������ ����������� ������� ������� � �������
			curProbability = std::pow(pheromone.get(from, i), alpha) * std::pow(distance.get(from, i), beta);
			maxProbability += curProbability;
			neighbourProbabilityMarkers.push_back(maxProbability);
		}
	}
	// �������� �����
	if (maxProbability == 0) {
		canMove = false;
		return SIZE_MAX;
	}
	// �������� ���������� ����� �� ������� ��� ������, � ����� ������� ������� �������
	std::uniform_real_distribution<double> dis(0.0, maxProbability);
	double choice = dis(random_engine);
	for (size_t i = 0; i < neighbourProbabilityMarkers.size(); i++) {
		if (choice < neighbourProbabilityMarkers[i]) {
			// ������� ������� � �������� ��������� �������
			location = i;
			// ���������� ������� � ������ ����������
			path->addStep(i, distance.get(from, i));
			return i;
		}
	}
}
// ��������� �������
size_t Ant::getLocation() const {
	return location;
}
// ����� �� ������� ����������
bool Ant::canContinue() const {
	return canMove;
}
// ��������� ����������� ���� �������
std::unique_ptr<Path> Ant::getPath() {
	return std::move(path);
}
// ��������� �� ������� � ������
bool Ant::isOnStart() const {
	if (location == start) {
		return true;
	}
	else {
		return false;
	}
}


