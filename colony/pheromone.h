#pragma once
#include "graph.h"
#include "Path.h"
// обработчик феромона
namespace Pheromone {
	// нанесение феромона
	void lay(MatrixGraph& pheromone, const Path& path, double pheromonePerAnt);
	// испарение феромона
	void evaporate(MatrixGraph& pheromone, double pheromoneEvaporation);
}