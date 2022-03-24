#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main (int argc, char* argv[]) {
	ifstream iFile;
	istringstream iStream;
	string filename/*argv[1]*/;
	string variety, comp_variety;
	char ch;
	double price = 100, comp_price = 0;
	double weight = 1, comp_weight = 0;
	
	iFile.open(filename);
	while (iFile) {
		iFile >> comp_variety >> comp_price >> comp_weight;
		iFile.get(ch);
			if (comp_price / comp_weight < price / weight) {
				price = comp_price;
				weight = comp_weight;
				variety = comp_variety;
			}
		}
	iFile.close();
	cout << variety << ' ' << price << ' ' << weight << endl;
}