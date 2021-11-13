/*
 * Lab2 Ex2 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
    // TODO: complete struct
    char name[16];
    int chinese_score;
    int math_score;
    int english_score;
} Student;

int compare(const void* p1, const void* p2) {
    // TODO: complete compare function for qsort()
    Student* a = (Student*)p1;
    Student* b = (Student*)p2;
    return ((b->chinese_score + b->english_score + b->math_score) - (a->chinese_score + a->english_score + a->math_score));
}

int main() {
    // TODO: read input
    int n = 0;
    Student student[10];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> student[i].name >> student[i].chinese_score >> student[i].math_score >> student[i].english_score;
    }
    // TODO: sort array with qsort()
    qsort(student, n, sizeof(Student), compare);
    // TODO: print result
    for (int i = 0; i < n; i++) {
        cout << student[i].name << " " << student[i].chinese_score << " " << student[i].math_score << " " << student[i].english_score << endl;
    }
    return 0;
}