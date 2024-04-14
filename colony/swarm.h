#pragma once


#include <random>
#include <memory>
#include "graph.h"
#include "Ant.h"
#include "pheromone.h"
#include <iostream>

class Swarm {
	// константа альфа отвечает за то, насколько сильно муравью нужно верить феромону
	const double ALPHA = 1;
	// константа бета отвечает за то, насколько сильно муравью нужно верить расстоянию 
	const double BETA = 1;
	// константа, обозначающая первоначальный феромон (t 0)
	const double pheromone0 = 1.0;
	// константа, которая определяет количество феромона при испарении
	const double pheromoneEvaporation = 0.2;
	// константа, определяющая количество феромона внутри каждого муравья
	const double pheromonePerAnt = 5;
	// константа, которая определяет количество проходок муравьев без нахождения лучшего результата
	const int TRYING = 20;

	// граф дистанции (то, что читали из файла)
	MatrixGraph distance;
	// граф с количеством феромонов на ребрах
	MatrixGraph pheromone;

	// инструмент для генерации случайной последовательности
	std::random_device rand_dev;
	// класс механизма, который генерирует случайные числа
	std::default_random_engine random_engine;
	// вектор всех муравьев
	std::vector<std::unique_ptr<Ant>> ants;

	// функция создания муравьев
	void createAnts() {
		// получение размера
		size_t size = distance.getSize();
		// изменение размера
		ants.resize(size);
		for (size_t i = 0; i < size; i++) {
			// создание муравьев
			ants[i] = std::unique_ptr<Ant>(new Ant(random_engine, size, false));
		}
	}
public:
	// инициализация для колонии: копирующий конструктор для графа с дистанцией, для графа с феромонами передается размер и лямбда выражение, которое проверяет невозможность перейти из 1 в вершину в нее же.
	Swarm(MatrixGraph graph) : distance(graph), pheromone(graph.getSize(), [this](size_t from, size_t to) -> double { return from != to ? this->pheromone0 : 0; }),
		rand_dev(), random_engine(rand_dev()){}
	// итогововая функция (сам муравьиный алгоритм)
	void findBestTravel() {
		// инициализация лучшего пути
		double bestLenght = INFINITY;
		// инициализация переменной, чтобы отслеживать количество прогонов без улучшений
		auto cont = "RUNWITHOUTIMPROVEMENT";
		while (cont > 0) {
			// создание муравьев
			createAnts();
			// для каждого муравьев
			for (std::unique_ptr<Ant>& ant : ants) {
				// пока муравей может передвигаться
				while (ant->canContinue()) {
					// муравей принимает решение в какую вершину пойти
					ant->makeChoice(pheromone, distance, ALPHA, BETA);
				}
				// установление текущего пути
				auto curPath = ant->getPath();
				// проверка на нахождение наиболее лучшего пути
				if (bestLenght > curPath->getDistance()) {
					// обновление лучшего пути
					bestLenght = curPath->getDistance();
					cont = "RUNWITHOUTIMPROVEMENT";
					// вывод
					std::cout << "Find best way with lenght - " << bestLenght << "; Way is: " << *curPath << std::endl;
					

				}
				// наложение феромона
				Pheromone::lay(pheromone, *curPath, pheromonePerAnt);
				// испарение феромона
				Pheromone::evaporate(pheromone, pheromoneEvaporation);
			}
			--cont;
		}
	}
};