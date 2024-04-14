#pragma once
#include <vector>
#include <ostream>
// класс пути
class Path {
	// сам путь
	std::vector<size_t> path;
	// дистанция
	double distance;
public:
	// инициализация пути
	Path(size_t initial);
	// получение дистанции
	double getDistance() const;
	// получение шагов
	size_t getNumOfSteps() const;
	// оператор получения нужного элемента
	size_t operator[](size_t element) const;
	// добавить шаг до конкретного пути (vertex) и с конкретной дистанцией
	void addStep(int vertex, double dist);
	// содержит ли пройденный путь данную вершину
	bool contains(size_t location);
	// вывод пути
	friend std::ostream& operator <<(std::ostream& os, const Path& path);
};

