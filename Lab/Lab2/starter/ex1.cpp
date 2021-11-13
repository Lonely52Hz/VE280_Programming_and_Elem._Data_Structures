/*
 * Lab2 Ex1 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <iostream>

using namespace std;

#define RANGE 100000

bool isPrime[RANGE + 1];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime() {
    // TODO: implement Eratosthenes Sieve Algorithm
    for (int i = 0; i < RANGE + 1; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i < RANGE + 1; i++) {
        if (isPrime[i]) {
            for (int j = i; i * j < RANGE + 1; j++) {
                isPrime[i * j] = false;
            }
        }
    }
}

int main() {
    // TODO: generate lookup table
    generateIsPrime();
    // TODO: read input and check if each num is prime
    int n = 0;
    int count = 0;
    int temp = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        if (isPrime[temp]) {
            cout << temp;
            count = i;
            break;
        }
    }
    for (int i = count + 1; i < n; i++) {
        cin >> temp;
        if (isPrime[temp]) {
            cout << ' ' << temp;
        }
    }
    cout << endl;
    return 0;
}