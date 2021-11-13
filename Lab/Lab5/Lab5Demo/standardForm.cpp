//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include <cmath>
#include "standardForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in) {
    // TODO: implement this constructor
    a = a_in;
    b = b_in;
    c = c_in;
}

float quadraticFunction::getA() const {
    return a;
}

float quadraticFunction::getB() const {
    return b + 0.0;
}

float quadraticFunction::getC() const {
    return c + 0.0;
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return a * pow(x, 2) + b * x + c + 0.0;
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    float delta = pow(b, 2) - 4 * a * c;
    float real1 = 0;
    float real2 = 0;
    float img1 = 0;
    float img2 = 0;
    root roots;
    if (delta > 0) {
        real1 = (-b + sqrt(delta)) / (2 * a) + 0.0;
        real2 = (-b - sqrt(delta)) / (2 * a) + 0.0;
        if (real1 < real2) {
            roots.realRootNum = 2;
            roots.roots[0].real = real1;
            roots.roots[0].imaginary = 0;
            roots.roots[1].real = real2;
            roots.roots[1].imaginary = 0;
        }
        else {
            roots.realRootNum = 2;
            roots.roots[0].real = real2;
            roots.roots[0].imaginary = 0;
            roots.roots[1].real = real1;
            roots.roots[1].imaginary = 0;
        }
    }
    else if (delta == 0) {
        real1 = (-b) / (2 * a) + 0.0;
        roots.realRootNum = 1;
        roots.roots[0].real = real1;
        roots.roots[0].imaginary = 0;
        roots.roots[1].real = real1;
        roots.roots[1].imaginary = 0;
    }
    else {
        real1 = (-b) / (2 * a) + 0.0;
        img1 = sqrt(-delta) / (2 * a) + 0.0;
        img2 = -(sqrt(-delta) / (2 * a)) + 0.0;
        roots.realRootNum = 0;
        if (img1 < img2) {
            roots.roots[0].real = real1;
            roots.roots[0].imaginary = img1;
            roots.roots[1].real = real1;
            roots.roots[1].imaginary = img2;
        }
        else {
            roots.roots[0].real = real1;
            roots.roots[0].imaginary = img2;
            roots.roots[1].real = real1;
            roots.roots[1].imaginary = img1;
        }
    }
    return roots;
}

int quadraticFunction::intersect(quadraticFunction g){
    // TODO: implement this function
    float ga = g.getA();
    float gb = g.getB();
    float gc = g.getC();
    float new_a = a - ga;
    float new_b = b - gb;
    float new_c = c - gc;
    float delta = pow(new_b, 2) - 4 * new_a * new_c;
    if (new_a == 0) {
        if (new_b != 0) {
            return 1;
        }
        else {
            if (new_c != 0) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    else {
        if (delta >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}