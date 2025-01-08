#pragma once
#include <fstream> 
#include <queue>
#include "priority_queue.h"
#include <omp.h>

const int initializConstI = -100000;
const double initializConstD = -100000.;
class DijkstraAlgorithm {
public: 
	std::vector<double> Algorithm1(const std::vector<std::vector<std::pair<int, double>>> adjList, int start) { //отправить вершину с индексом [0,adjList.size()-1]
		int countV(adjList.size());
		std::vector<double> path(countV, -initializConstD);

		std::vector<bool> visited(countV);
		path[start] = 0; //обработка стартовой вершины

		for (int i = 0; i < countV; i++) {
			int near = -1;
			for (int j = 0; j < countV; j++) { //поиск ближайшей вершины
				if (!visited[j] && ((near == -1) || (path[j] < path[near]))) {
					near = j;
				}
			}
			visited[near] = true;
			for (int v = 0; v < adjList[near].size(); v++) { // релаксация 
				int currV = adjList[near][v].first;
				double currW = adjList[near][v].second;
				if (path[near] + currW < path[currV]) {
					path[currV] = path[near] + currW;
				}
			}
			if (i % 10000 == 0) {
				std::cout << i << std::endl;
			}
		}
		return path;
	}
	std::vector<double> Algorithm2(const std::vector<std::vector<std::pair<int, double>>> adjList, int start) { //отправить вершину с индексом [0,adjList.size()-1]
		int countV(adjList.size());
		std::vector<std::pair<double, double>> data = {{0,start}};

		std::vector<double> path(countV, -initializConstD);

		priority_queue<double, double> Q(data);
		path[start] = 0;

		for (int i = 0; i < countV; i++) {
			int near = Q.top().second;
			if (near != INFINIT) {
				Q.pop();
				for (int v = 0; v < adjList[near].size(); v++) { // релаксация 
					int currV = adjList[near][v].first;
					double currW = adjList[near][v].second;

					if (path[near] + currW < path[currV]) {
						path[currV] = path[near] + currW;
						Q.push(std::make_pair(path[currV], currV));
					}
				}
			}
			else break;
		}
		return path;
	}
	std::vector<double> Algorithm3(const std::vector<std::vector<std::pair<int, double>>> adjList, int start) { //отправить вершину с индексом [0,adjList.size()-1]
		int countV(adjList.size());
		std::vector<std::pair<double, double>> data = { {0,start} };

		std::vector<double> path(countV, -initializConstD);
		std::priority_queue<std::pair<double, double>, std::vector<std::pair<double, double>>, CompareForStdQueue<std::pair<double, double>>> Q;
		Q.push({ 0,start });
		path[start] = 0;
		for (int i = 0; i < countV; i++) {
				int near = Q.top().second;
				if (near != INFINIT) {
					{
					Q.pop(); 
					}
					for (int v = 0; v < adjList[near].size(); v++) { // релаксация 
						int currV = adjList[near][v].first;
						double currW = adjList[near][v].second;
						{
							if (path[near] + currW < path[currV]) {
								path[currV] = path[near] + currW; 
								Q.push(std::make_pair(path[currV], currV)); 
							}
						}
				}
			}
		}
		return path;
	}
}; 


class fileParsing {
public:
	void ParsingInMatrix(std::ifstream& file) {
		int countV = 0;
		file >> countV;
		int v1 = initializConstI, v2 = initializConstI;
		double weight = initializConstD;
		std::vector<std::vector<double>> matrix(countV);
		for (int i = 0; i < countV; i++) matrix[i] = std::vector<double>(countV);

		while (file >> v1 >> v2 >> weight) {
			matrix[v1][v2] = weight;
		}
		/*for (int i = 0; i < countV; i++) {
		 for (int j = 0; j < countV; j++) {
		  std::cout << i << " " << j << " " << matrix[i][j] << "\n";
		 }
		}*/
	}
	std::vector<std::vector<std::pair<int, double>>> ParsingInAdjList(std::ifstream& file) {
		int countV = 0;
		file >> countV;
		int v1 = initializConstI, v2 = initializConstI;
		double weight = initializConstD;
		std::vector<std::vector<std::pair<int, double>>> data(countV);
		std::cout << countV << std::endl;
		while (file >> v1 >> v2 >> weight) {
			//while (file >> v1 >> v2) {
			data[v1 - 1].push_back(std::make_pair(v2 - 1, weight));
			data[v2 - 1].push_back(std::make_pair(v1 - 1, weight));
		}
		return data;
	}
};
class graph {
	std::vector<std::vector<std::pair<int, double>>> adjList;
	int countV;
public:
	int getVertices() {
		return countV;
	}
	graph(std::ifstream& file) {
		fileParsing Pars;
		if (file.is_open()) {
			adjList = Pars.ParsingInAdjList(file);
			countV = adjList.size();
		}
	}
	void printAdjList() {
		for (int i = 0; i < countV; i++) {
			std::cout << i << " ";
			for (int j = 0; j < adjList[i].size(); j++) {
				std::cout << adjList[i][j].first << " ";
			}
			std::cout << std::endl;
		}
	}
	std::vector<double> findShortWays(int start) { //находит короткие пути от start до всех остальных вершин
		DijkstraAlgorithm D;
		return D.Algorithm2(adjList, start);
	}
};
