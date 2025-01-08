#pragma once
#include <iostream> 
#include <vector> 
const double INFINIT = 100000000;
template<class T>
class CompareForStdQueue {
public:
	bool operator()(T elem1, T elem2) {
		return elem1.first > elem2.first;
	}
};

template<class T>
class Compare {
public:
	bool operator()(T elem1, T elem2) {
		return elem1 < elem2;
	}
};
template<class T1, class T2>
class BinHeap {
	std::vector<std::pair<T1, T2>> data; // приоритет, значение
	size_t size;
	Compare<T1> comp;
public:
	void Print() {
		for (int i = 0; i < size; i++) {
			std::cout << "{" << data[i].first << " " << data[i].second << "}\n";
		}
		std::cout << "\n";
	}
	int leftChild(int index) {
		if (2 * index + 1 < size) {
			return 2 * index + 1;
		}
		else return -1;
	}
	int rightChild(int index) {
		if (2 * index + 2 < size) {
			return 2 * index + 2;
		}
		else return -1;
	}
	int minChild(int index) {
		int rC = rightChild(index);
		int lC = leftChild(index);
		if (rC != -1 && lC != -1) {
			if (comp(data[lC].first,data[rC].first)) {
				return lC;
			}
			else return rC;
		}
		else {
			if (rC == -1) {
				return lC;
			}
			else return rC;
		}
	}
	int parent(int index) {
		if (index != 0) {
			return (index - 1) / 2;
		}
		else return -1;
	}
	void swap(int index1, int index2) {
		std::pair<T1, T2> tmp = data[index1];
		data[index1] = data[index2];
		data[index2] = tmp;
	}
	size_t getSize() {
		return size;
	}
	void diving(int index) {
		int j1 = index;
		int j2 = minChild(index);
		//std::cout << j1 << " " << j2 << std::endl;
		while ((j2 != -1) && (!comp(data[j1].first,data[j2].first))) { //(data[j1].first > data[j2].first)
			swap(j1, j2);
			j1 = j2;
			j2 = minChild(j1);
		}
	}
	void emersion(int index) {
		int j1 = index;
		int j2 = parent(index);
		while ((j2 != -1) && (comp(data[j1].first, data[j2].first))) {
			swap(j1, j2);
			j1 = j2;
			j2 = parent(j1);
		}
	}
	std::pair<T1, T2> getMin() {
		if (size > 0) {
			return data[0];
		}
		else return { INFINIT,INFINIT };
	}
	void push(std::pair<T1, T2> pair) {
		data.push_back(pair);
		size++;
		emersion(size - 1);
	}
	void pop() {
		swap(0, size - 1);
		data.pop_back();
		size--;
		diving(0);
	}
	BinHeap(const std::vector<std::pair<T1, T2>>& data_, Compare<T1> comp_ = Compare<T1>()) {
		size = data_.size();
		comp = comp_;
		data = data_;
		makeHeap();
	}
	void  makeHeap() {
		for (int i = size - 1; i >= 0; i--) {
			diving(i);
		}
	}
	BinHeap& operator=(const BinHeap& B) {
		data = B.data;
		size = B.size;
		comp = B.comp;
		return *this;
	}
};
template<class T1, class T2>
class priority_queue {
	BinHeap<T1, T2> data;
	size_t size;
	Compare<T1> comp;
public:
	priority_queue(std::vector<std::pair<T1, T2>> data_, Compare<T1> comp_ = Compare<T1>()) :data(BinHeap<T1, T2>(data_, comp_)) {
		comp = comp_;
		size = data_.size();
	}
	void push(std::pair<T1, T2> pair) {
		data.push(pair);
		size++;
	}
	std::pair<T1, T2> top() {
		return data.getMin();
	}
	void pop() {
		data.pop();
		size--;
	}
	void printQ() {
		data.Print();
	}

};
