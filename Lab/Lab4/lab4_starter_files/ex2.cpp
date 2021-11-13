#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//EFFECTS: define the struct that includes name, price, and weight
struct apple {
	string name;
	double price;
	double weight;
};

int main(int argc, char* argv[]) {
	ifstream iFile;
	iFile.open(argv[1]);
	apple lowest;
	apple temp;
	
	// read the first one
	iFile >> lowest.name >> lowest.price >> lowest.weight;
	
	// compare to ger the lowest
	while (iFile >> temp.name) {
		iFile >> temp.price >> temp.weight;
		if (temp.price / temp.weight < lowest.price / lowest.weight) {
			lowest = temp;
		}
	}

	cout << lowest.name << ' ';

	// set precision
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << lowest.price << ' ' << lowest.weight << endl;

	iFile.close();
	return 0;
}
