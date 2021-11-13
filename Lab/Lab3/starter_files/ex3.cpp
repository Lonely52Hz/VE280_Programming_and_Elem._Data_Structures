#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
	int n = 0;
	int m = 0;
	int a = 0;
	int isAdd = 0;
	int isSmall = 0;
	int isVerbose = 0;
	int smallPosition = 0;
	int addResult = 0;
	int smallResult = 0;

	cin >> n;
	cin >> addResult;
	smallResult = addResult;
	for (int i = 1; i < n; ++i) {
		cin >> m;
		addResult += m;
		if (m < smallResult) {
			smallResult = m;
		}
	}

	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "--help") == 0) {
			cout << "Hey, I love Integers." << endl;
			return 0;
		}
	}

	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "--add") == 0) {
			isAdd = 1;
			break;
		}
	}

	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "--small") == 0) {
			smallPosition = i + 1;
			isSmall = 1;
			int len = strlen(argv[smallPosition]);
			if (len == 1) {
				a = argv[smallPosition][0] - '0';
			}
			else {
				a = atoi(argv[smallPosition]);
			}
			smallResult += a;
			break;
		}
	}

	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "--verbose") == 0) {
			isVerbose = 1;
			break;
		}
	}

	if (isAdd == 1 && isVerbose == 1) {
		cout << "This is add operation." << endl;
		cout << addResult << endl;
	}
	else if (isAdd == 1 && isVerbose == 0) {
		cout << addResult << endl;
	}

	if (isSmall == 1 && isVerbose == 1) {
		cout << "This is small operation." << endl;
		cout << smallResult << endl;
	}
	else if (isSmall == 1 && isVerbose == 0) {
		cout << smallResult << endl;
	}

	if (isAdd == 0 && isSmall == 0) {
		cout << "No work to do!" << endl;
	}

	return 0;
}