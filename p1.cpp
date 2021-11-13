#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	int* numbers = new int[argc - 1];
	int max = 0;
	int min = 0; 
	int position = 0;
	if (argc == 2 || argc == 3) {
		return 0;
	}
	for (int i = 1; i < argc; ++i) {
		numbers[i - 1] = atoi(argv[i]);
		cout << numbers[i - 1] << endl;
	}
	for (int i = 0; i < argc - 1; ++i) {
		if (numbers[i] > max) {
			max = numbers[i];
		}
	}
	for (int i = 0; i < argc - 1; ++i) {
		if (numbers[i] < min) {
			min = numbers[i];
		}
	}
	for (int i = 0; i < argc - 1; ++i) {
		if (numbers[i] != min && numbers[i]!=max) {
			cout << numbers[i];
			position = i + 1;
			break;
		}
	}
	for (int i = position; i < argc - 1; ++i) {
		if (numbers[i] != min && numbers[i] != max) {
			cout << " " << numbers[i];
		}
	}
	delete[]numbers;
	return 0;
}
