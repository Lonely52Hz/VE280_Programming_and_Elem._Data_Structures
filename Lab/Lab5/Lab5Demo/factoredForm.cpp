//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include "factoredForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in) {
    // TODO: implement this constructor
    a = a_in;
    float b = b_in;
    float c = c_in;
    float real1 = 0;
    float real2 = 0;
    float img1 = 0;
    float img2 = 0;
    float delta = pow(b, 2) - 4 * a * c;
    if (delta > 0) {
        real1 = (-b + sqrt(delta)) / (2 * a);
        real2 = (-b - sqrt(delta)) / (2 * a);
        if (real1 < real2) {
            r1.real = real1 + 0.0;
            r1.imaginary = 0;
            r2.real = real2 + 0.0;
            r2.imaginary = 0;
        }
        else {
            r1.real = real2 + 0.0;
            r1.imaginary = 0;
            r2.real = real1 + 0.0;
            r2.imaginary = 0;
        }
    }
    else if (delta == 0) {
        r1.real = (-b) / (2 * a) + 0.0;
        r1.imaginary = 0;
        r2.real = (-b) / (2 * a) + 0.0;
        r2.imaginary = 0;
    }
    else {
        r1.real = (-b) / (2 * a) + 0.0;
        r2.real = (-b) / (2 * a) + 0.0;
        img1 = sqrt(-delta) / (2 * a) + 0.0;
        img2 = -(sqrt(-delta) / (2 * a)) + 0.0;
        if (img1 < img2) {
            r1.imaginary = img1;
            r2.imaginary = img2;
        }
        else {
            r1.imaginary = img2;
            r2.imaginary = img1;
        }
    }
}

float quadraticFunction::getA() const {
    return a + 0.0;
}

float quadraticFunction::getB() const {
    // TODO: implement this function
    return (-a) * (r1.real + r2.real) + 0.0;
}

float quadraticFunction::getC() const {
    // TODO: implement this function
    return a * (r1.real * r2.real - r1.imaginary * r2.imaginary) + 0.0;
}

float quadraticFunction::evaluate(float x) {
    // TODO: implement this function
    return a * pow(x, 2) + this->getB() * x + this->getC() + 0.0;
}

root quadraticFunction::getRoot() {
    // TODO: implement this function
    root roots;
    if (r1.real != r2.real && r1.imaginary == 0 && r2.imaginary == 0) {
        roots.realRootNum = 2;
        roots.roots[0] = r1;
        roots.roots[1] = r2;
    }
    else if (r1.real == r2.real && r1.imaginary == 0 && r2.imaginary == 0) {
        roots.realRootNum = 1;
        roots.roots[0] = r1;
        roots.roots[1] = r2;
    }
    else {
        roots.realRootNum = 0;
        roots.roots[0] = r1;
        roots.roots[1] = r2;
    }
    return roots;
}

int quadraticFunction::intersect(quadraticFunction g) {
    // TODO: implement this function
    float b = this->getB();
    float c = this->getC();
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