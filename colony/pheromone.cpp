#include "pheromone.h"
// нанесение феромона
void Pheromone::lay(MatrixGraph& pheromone, const Path& path, double pheromonePerAnt) {
	// количество феромона, которое нужно нанести
	double pheromoneToLay = pheromonePerAnt / path.getNumOfSteps();
	for (size_t i = 1, n = path.getNumOfSteps(); i < n; i++) {
		// нанесение феромона
		pheromone.set(path[i - 1], path[i], pheromone.get(path[i - 1], path[i]) + pheromoneToLay);
		//pheromone.alter(path[i - 1], path[i], [pheromoneToLay](double& val) { val += pheromoneToLay; }
		//pheromone.alter(path[i - 1], path[i], [pheromoneToLay](double& val) {val += pheromoneToLay; });
	}
}
// испарение феромона
void Pheromone::evaporate(MatrixGraph& pheromone, double pheromoneEvaporation) {
	for (size_t i = 0, n = pheromone.getSize(); i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			pheromone.set(i, j, pheromone.get(i, j) * (1 - pheromoneEvaporation));
			//pheromone.alter(i, j, [pheromoneEvaporation](double& val) { val *= 1 - pheromoneEvaporation; });
			
		}
	}
}