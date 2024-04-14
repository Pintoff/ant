#pragma once
#include "graph.h"
#include "Path.h"
// ���������� ��������
namespace Pheromone {
	// ��������� ��������
	void lay(MatrixGraph& pheromone, const Path& path, double pheromonePerAnt);
	// ��������� ��������
	void evaporate(MatrixGraph& pheromone, double pheromoneEvaporation);
}