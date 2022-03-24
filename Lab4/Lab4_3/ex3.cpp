#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
	string line;
	char letter;
	string name = {};
	int number_name = 1;


	getline(cin, line);
	istringstream iStream;
	iStream.str(line);
	while (iStream.get(letter)) {
		if ((letter != ' ') && (letter != ',')) {
			name = name + letter;
		}
		if (letter == ',') {
			cout << name << endl;
			name = {};
			number_name++;
		}
	}
	cout << name << endl;
	cout << number_name << endl;
}