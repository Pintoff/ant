#pragma once


#include <cmath>
#include <memory>
#include <random>
#include "graph.h"
#include "Path.h"

// класс отдельного муравья
class Ant {
	// сначала иницилизируем движок, затем используем его
	std::default_random_engine &random_engine;
	// текущая позиция муравья
	size_t location;
	// вершина, с которой начал муравей
	size_t start;
	// список табу вершин(которые муравей уже посетил или вершины-тупики)
	std::unique_ptr<Path> path;
	// может ли муравей двигаться куда-либо
	bool canMove;
public:
	// иницилация муравья
	Ant(std::default_random_engine &e, size_t loc, bool exact);
	// функция, которая делает следующий шаг муравьем
	size_t makeChoice(const MatrixGraph &pheromone, const MatrixGraph &distance, double alpha, double beta);
	// получение позиции муравья
	size_t getLocation() const;
	// получение списка вершин, которые муравей уже посетил
	std::unique_ptr<Path> getPath();
	// может ли муравей продолжать движение
	bool canContinue() const;
	// находится ли муравей в начале
	bool isOnStart() const;
};
