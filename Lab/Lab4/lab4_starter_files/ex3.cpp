#include <iostream>
#include <istream>
#include <sstream>

using namespace std;

int num = 0;

//EFFECTS: if the string has no comma inside, just cout; else split it to two strings. Do it recersively.
void split(string name) {
	int len = name.length();
	int comma_position = 0;
	int isComma = 0;

	for (int i = 0; i < len; ++i) {
		if (name[i] == ',') {
			comma_position = i;
			isComma = 1;
			break;
		}
	}
	if (isComma == 0) {
		cout << name << endl;
		num++;
	}
	else {
		cout << name.substr(0, comma_position) << endl;
		num++;
		split(name.substr(comma_position + 1, len - comma_position - 1));
	}
}

int main() {
	istringstream iStream;
	string line;
	string name;
	int len;

	getline(cin, line);
	iStream.str(line);
	
	while (iStream >> name) {
		len = name.length();
		if (len == 1) {
			if (name[0] != ',') {
				cout << name << endl;
				num++;
			}

		}
		else if (len == 2) {
			if (name[0] == ',') {
				cout << name.substr(1, 1) << endl;
				num++;
			}
			else if (name[1] == ',') {
				cout << name.substr(0, 1) << endl;
				num++;
			}
		}
		else {
			if (name[0] == ',' && name[len - 1] == ',') {
				split(name.substr(1, len - 2));
			}
			else if (name[0] != ',' && name[len - 1] == ',') {
				split(name.substr(0, len - 1));
			}
			else if (name[0] == ',' && name[len - 1] != ',') {
				split(name.substr(1, len - 1));
			}
			else if (name[0] != ',' && name[len - 1] != ',') {
				split(name);
			}
		}

	}
	cout << num << endl;
	return 0;
}
