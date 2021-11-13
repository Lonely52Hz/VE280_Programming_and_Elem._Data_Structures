/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
using namespace std;


// EFFECTS: return the trace of the Laplacian of the weight matrix.
int traceLaplacian(int weight[][50], int size) {
    int calculate[50] = { 0 };
    int ans = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            calculate[i] = calculate[i] + weight[i][j];
        }
    }
    for (int i = 0; i < size; i++)
        calculate[i] = calculate[i] - weight[i][i];
    for (int i = 0; i < size; i++)
        ans = ans + calculate[i];
    return ans;
}


int main() {
    int size, trace;
    int weight[50][50] = {};
    cin >> size;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            cin >> weight[i][j];
    trace = traceLaplacian(weight, size);
    cout << trace << endl;
}
