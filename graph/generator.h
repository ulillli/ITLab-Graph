#pragma once
#include <fstream> 
#include <string>
int START = 0;
int END = 100000;
int K1 = 900000;
int K2 = K1%100000+1;
double K3 = K1 * 1.5;
class generator {
public:

	std::pair<int,int> parsString(const std::string s) {
		std::pair<int, int> result;
		int j = 0;
		std::string first, second;
		while (s[j] != 32 && !s.empty() && (j < s.size())) {
			first += s[j];
			j++;
			}
		result.first = stoi(first);
		if (j + 1 < s.size()) {
			j++;
			while (j < s.size()) {
				second += s[j];
				j++;
			}
			result.second = stoi(second);
		}
		else result.second = -1;
		return result;

	}
	void addWeightForVertices(std::ifstream& file_out, std::ofstream& file_in) {
		if (file_out.is_open()&&file_in.is_open()) {
			int x=0, y=0;
			int count;
			std::string str;
			getline(file_out, str);
			count = (int)parsString(str).first; //считали число вершин
			file_in << K1 << "\n"; //записали число вершин
			int m = 0;
			while (m<K3) {
				getline(file_out, str);
				m++;
				x = (int)parsString(str).first;
				y = (int)parsString(str).second;
				if (y >= K1) {
					y = y % K2+1234;
					
				}
				if (x >= K1) {
					x = x % K2+1234;
				}
				if (y == -1) {
					y = (x+10)%K2+1;
				}
				srand(time(0));
				double r = rand() % (END - START + 1) + x%END;
				file_in << x << " " << y << " " << r << "\n";
			}
		}
	}
};
