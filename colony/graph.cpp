#include "graph.h"

#include <fstream>
#include <iostream>

MatrixGraph::MatrixGraph(std::string filename) {
	// получение дескриптора файла
	std::ifstream fin(filename);
	// получение размера графа
	fin >> size;
	// изменение размера вектора
	matrix.resize(size);
	for (size_t i = 0; i < size; i++) {
		matrix[i].resize(size);
		for (size_t j = 0; j < size; j++) {
			// считывание из файла
			fin >> matrix[i][j];
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	fin.close();
}



MatrixGraph::MatrixGraph(size_t theSize, std::function<double(size_t, size_t)> generation) {
	// инициализация размера
	size = theSize;
	// изменение размера
	matrix.resize(size);
	for (size_t i = 0; i < size; i++) {
		// изменение размера
		matrix[i].resize(size);
		for (size_t j = 0; j < size; j++) {
			// генерация
			matrix[i][j] = generation(i, j);
		}
	}
}

void MatrixGraph::print() {
	std::cout << "size : " << size << std::endl;
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if (j) {
				std::cout << '\t';
			}
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
}

size_t MatrixGraph::getSize() const {
	return size;
}

double MatrixGraph::get(size_t from, size_t to) const {
	return matrix[from][to];
}

void MatrixGraph::set(size_t from, size_t to, double value) {
	matrix[from][to] = value;
}

void MatrixGraph::alter(size_t from, size_t to, std::function<void(double&)> alterator) {
	alterator(matrix[from][to]);
}

