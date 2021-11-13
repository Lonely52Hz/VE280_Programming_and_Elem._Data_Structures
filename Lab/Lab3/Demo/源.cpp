/*
 * VE280 Lab 3, SU2020.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;

bool canWin(int count, int arr[], int position, int label[]) {
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence

    // TODO: implement this function
    if (arr[position] == 280) {
        return true;
    }
    else {
        label[position] = 1;
        if (position + arr[position] <= count - 1 && position - arr[position] >= 0) {
            if (label[position + arr[position]] == 0 && label[position - arr[position]] == 0) {
                return canWin(count, arr, position + arr[position], label) || canWin(count, arr, position - arr[position], label);
            }
            else if (label[position + arr[position]] == 0 && label[position - arr[position]] != 0) {
                return canWin(count, arr, position + arr[position], label);
            }
            else if (label[position + arr[position]] != 0 && label[position - arr[position]] == 0) {
                return canWin(count, arr, position - arr[position], label);
            }
            else {
                return false;
            }
        }
        else if (position + arr[position] <= count - 1 && position - arr[position] < 0) {
            if (label[position + arr[position]] == 0) {
                return canWin(count, arr, position + arr[position], label);
            }
            else {
                return false;
            }
        }
        else if (position + arr[position] > count - 1 && position - arr[position] >= 0) {
            if (label[position - arr[position]] == 0) {
                return canWin(count, arr, position - arr[position], label);
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
}

int main() {
    int count;
    cin >> count;
    int arr[MAXSIZE];
    int label[MAXSIZE] = { 0 };
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position, label);
    return 0;
}