#pragma once


#include <random>
#include <memory>
#include "graph.h"
#include "Ant.h"
#include "pheromone.h"
#include <iostream>

class Swarm {
	// ��������� ����� �������� �� ��, ��������� ������ ������� ����� ������ ��������
	const double ALPHA = 1;
	// ��������� ���� �������� �� ��, ��������� ������ ������� ����� ������ ���������� 
	const double BETA = 1;
	// ���������, ������������ �������������� ������� (t 0)
	const double pheromone0 = 1.0;
	// ���������, ������� ���������� ���������� �������� ��� ���������
	const double pheromoneEvaporation = 0.2;
	// ���������, ������������ ���������� �������� ������ ������� �������
	const double pheromonePerAnt = 5;
	// ���������, ������� ���������� ���������� �������� �������� ��� ���������� ������� ����������
	const int TRYING = 20;

	// ���� ��������� (��, ��� ������ �� �����)
	MatrixGraph distance;
	// ���� � ����������� ��������� �� ������
	MatrixGraph pheromone;

	// ���������� ��� ��������� ��������� ������������������
	std::random_device rand_dev;
	// ����� ���������, ������� ���������� ��������� �����
	std::default_random_engine random_engine;
	// ������ ���� ��������
	std::vector<std::unique_ptr<Ant>> ants;

	// ������� �������� ��������
	void createAnts() {
		// ��������� �������
		size_t size = distance.getSize();
		// ��������� �������
		ants.resize(size);
		for (size_t i = 0; i < size; i++) {
			// �������� ��������
			ants[i] = std::unique_ptr<Ant>(new Ant(random_engine, size, false));
		}
	}
public:
	// ������������� ��� �������: ���������� ����������� ��� ����� � ����������, ��� ����� � ���������� ���������� ������ � ������ ���������, ������� ��������� ������������� ������� �� 1 � ������� � ��� ��.
	Swarm(MatrixGraph graph) : distance(graph), pheromone(graph.getSize(), [this](size_t from, size_t to) -> double { return from != to ? this->pheromone0 : 0; }),
		rand_dev(), random_engine(rand_dev()){}
	// ���������� ������� (��� ���������� ��������)
	void findBestTravel() {
		// ������������� ������� ����
		double bestLenght = INFINITY;
		// ������������� ����������, ����� ����������� ���������� �������� ��� ���������
		auto cont = "RUNWITHOUTIMPROVEMENT";
		while (cont > 0) {
			// �������� ��������
			createAnts();
			// ��� ������� ��������
			for (std::unique_ptr<Ant>& ant : ants) {
				// ���� ������� ����� �������������
				while (ant->canContinue()) {
					// ������� ��������� ������� � ����� ������� �����
					ant->makeChoice(pheromone, distance, ALPHA, BETA);
				}
				// ������������ �������� ����
				auto curPath = ant->getPath();
				// �������� �� ���������� �������� ������� ����
				if (bestLenght > curPath->getDistance()) {
					// ���������� ������� ����
					bestLenght = curPath->getDistance();
					cont = "RUNWITHOUTIMPROVEMENT";
					// �����
					std::cout << "Find best way with lenght - " << bestLenght << "; Way is: " << *curPath << std::endl;
					

				}
				// ��������� ��������
				Pheromone::lay(pheromone, *curPath, pheromonePerAnt);
				// ��������� ��������
				Pheromone::evaporate(pheromone, pheromoneEvaporation);
			}
			--cont;
		}
	}
};