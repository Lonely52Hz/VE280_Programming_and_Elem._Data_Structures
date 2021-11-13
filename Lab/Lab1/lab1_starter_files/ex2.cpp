/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
#include <cstring>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]){
    int judge[3] = { 0 };
    if (strlen(password) > 50) {
        return false;
    }
    else {
        for (int i = 0; password[i] != '\0'; i++) {
            if (password[i] >= '0' && password[i] <= '9') {
                judge[0] = 1;
            }
            else if (password[i] >= 'A' && password[i] <= 'Z') {
                judge[1] = 1;
            }
            else if (password[i] >= 'a' && password[i] <= 'z') {
                judge[1] = 1;
            }
            else {
                judge[2] = 1;
            }
        }
        if (judge[0] == 1 && judge[1] == 1 && judge[2] == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    
}


int main(){
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
}
