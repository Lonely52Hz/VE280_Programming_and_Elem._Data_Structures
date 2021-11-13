#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

void trangle(int num) {
	int temp = sqrt(8 * num + 1);
	if (temp * temp == 8 * num + 1)
		cout << "1" << endl;
	else
		cout << "0" << endl;
}

void palindrome(int num) {
	int temp = num;
	int new_num = 0;
	while (temp > 0) {
		new_num = new_num * 10 + temp % 10;
		temp = temp / 10;
	}
	if (new_num == num)
		cout << "1" << endl;
	else
		cout << "0" << endl;

}

void power(int num) {
	bool a = true;
	if (num == 1) {
		cout << "1" << endl;
		a = false;
	}
	else if (num >= 4) {
		for (int i = 2; i <= sqrt(num) && a == true; i++) {
			for (int j = 2; pow(i,j) <= num && a == true; j++) {
				if (pow(i,j) == num) {
					cout << "1" << endl;
					a = false;
				}
			}
		}
	}
	if (a)
		cout << "0" << endl;
}

void abundant(int num) {
	int sum = 1;
	for (int i = 2; i < sqrt(num); i++) {
		if (num % i == 0) {
			if ((num / i) != i)
				sum = sum + i + (num / i);
			else
				sum = sum + i;
		}
	}
	if (sum > num)
		cout << "1" << endl;
	else
		cout << "0" << endl;
}

int main() {
	bool a = true;
	int num = 0;
	int test = 0;
	while (a) {
		cout << "Please enter the integer and the test number: ";
		cin >> num >> test;
		if (num > 0 && num <= 10000000 && test >= 1 && test <= 4)
			a = false;
	}
	if (test == 1)
		trangle(num);
	else if (test == 2)
		palindrome(num);
	else if (test == 3)
		power(num);
	else if (test == 4)
		abundant(num);
	return 0;
}