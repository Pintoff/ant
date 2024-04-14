#pragma once
#include <vector>
#include <string>
#include <functional>

class MatrixGraph {
	// размер графа
	size_t size;
	std::vector<std::vector<double>> matrix;
public:
	// считывание графа из файла
	MatrixGraph(std::string filename);
	// генерация
	MatrixGraph(size_t theSize, std::function<double(size_t, size_t)> generation);
	// конструктор по умолчанию отключен
	MatrixGraph() = delete;
	// получение размера
	size_t getSize() const;
	// получение длины ребра графа из вершины from в вершину to
	double get(size_t from, size_t to) const;
	// установить длину ребра из вершины from в вершину to
	void set(size_t from, size_t to, double value);

	void alter(size_t from, size_t to, std::function<void(double&)> alterator);
	// для отладки программы
	void print();
};



