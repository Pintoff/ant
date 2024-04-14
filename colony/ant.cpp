#include "Ant.h"

#include <cmath>
// инициализация муравья
Ant::Ant(std::default_random_engine &e, size_t loc, bool exact)
	: random_engine(e), canMove(true) {
	// вычисление местоположения муравья
	if (exact) {
		location = loc;
	}
	else {
		// создание случайных знаечений, которые будут распределены на отрезки от 0 до loc-1
		std::uniform_int_distribution<size_t> dis(0, loc - 1);
		// установление местоположения муравья
		location = dis(random_engine);
	}
	// установление начальной позиции муравья
	start = location;
	// инициализация списка пройденных вершин
	path = std::unique_ptr<Path>(new Path(location));
}

// метод для принятия решений муравьем, в какую вершину графа перейти
size_t Ant::makeChoice(const MatrixGraph &pheromone, const MatrixGraph &distance, double alpha, double beta) {
	size_t from = location;
	// последнее передвижение, особый случай
	if (path->getNumOfSteps() == distance.getSize()) {
		// муравей больше не может двигаться
		canMove = false;
		// установление позиции муравья на начало
		location = start;
		// добавление вершины в пройденный путь
		path->addStep(start, distance.get(from, start));
		return start;
	}

	// поиск соседей
	std::vector<double> neighbourProbabilityMarkers;
	double maxProbability = 0.0;
	double curProbability;
	for (size_t i = 0, size = distance.getSize(); i < size; i++) {
		// недопустимо, чтобы муравей перешел в ту же вершину
		if (i == from) { 
			neighbourProbabilityMarkers.push_back(0);
		}
		// недопустимо, чтобы муравей посетил одну вершину дважды
		else if (path->contains(i)) {
			neighbourProbabilityMarkers.push_back(0);
		}
		else {
			// высчитывание вероятности муравья перейти в вершину
			curProbability = std::pow(pheromone.get(from, i), alpha) * std::pow(distance.get(from, i), beta);
			maxProbability += curProbability;
			neighbourProbabilityMarkers.push_back(maxProbability);
		}
	}
	// возможен тупик
	if (maxProbability == 0) {
		canMove = false;
		return SIZE_MAX;
	}
	// бросание случайного числа на рулетку для выбора, в какую вершину перейти муравью
	std::uniform_real_distribution<double> dis(0.0, maxProbability);
	double choice = dis(random_engine);
	for (size_t i = 0; i < neighbourProbabilityMarkers.size(); i++) {
		if (choice < neighbourProbabilityMarkers[i]) {
			// переход муравья в наиболее вероятную вершину
			location = i;
			// добавление вершины в список пройденных
			path->addStep(i, distance.get(from, i));
			return i;
		}
	}
}
// получение локации
size_t Ant::getLocation() const {
	return location;
}
// может ли муравей продолжать
bool Ant::canContinue() const {
	return canMove;
}
// получение пройденного пути муравья
std::unique_ptr<Path> Ant::getPath() {
	return std::move(path);
}
// находится ли муравей в начале
bool Ant::isOnStart() const {
	if (location == start) {
		return true;
	}
	else {
		return false;
	}
}


