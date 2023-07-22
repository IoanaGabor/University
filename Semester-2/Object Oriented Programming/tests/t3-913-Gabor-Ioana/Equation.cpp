//
// Created by ioana on 26.05.2023.
//

#include <string>
#include <cmath>
#include "Equation.h"

Equation::Equation(double a, double b, double c) : a(a), b(b), c(c) {}

double Equation::getA() const {
    return a;
}

double Equation::getB() const {
    return b;
}

double Equation::getC() const {
    return c;
}

bool Equation::operator<(const Equation &rhs) const {
    if (a < rhs.a)
        return true;
    if (rhs.a < a)
        return false;
    if (b < rhs.b)
        return true;
    if (rhs.b < b)
        return false;
    return c < rhs.c;
}


std::string Equation::toString() {
    return std::to_string(a) + "*x^2 + " + std::to_string(b) + "*x +" + std::to_string(c);
}

bool Equation::operator==(const Equation &rhs) const {
    return a == rhs.a &&
           b == rhs.b &&
           c == rhs.c;
}

bool Equation::operator!=(const Equation &rhs) const {
    return !(rhs == *this);
}

std::string Equation::solutionsAsString() {
    if(a==0 && b== 0 && c == 0){
        return "0";
    }
    if(a==0 && b== 0){
        return "does not exist";
    }
    if(a == 0 && b!=0){
        return std::to_string(-c/b);
    }
    double delta = b*b - 4*a*c;
    double real1, real2;
    double imag;
    if(delta>=0){
        real1 = (-b - sqrt(delta) )/(2*a);
        real2 = (-b + sqrt(delta) )/(2*a);
        return std::to_string(real1) + ", " + std::to_string(real2);
    }else{
        imag = sqrt(-delta) / (2*a);
        real1 = -b / (2*a);
        return std::to_string(real1) + "-i" +std::to_string(imag) + ", " + std::to_string(real1) + "+i" +std::to_string(imag);
    }
    return "";
}

int Equation::degree() const {
    if(a!=0){
        return 2;
    }
    if(b!=0){
        return 1;
    }
    return 0;
}
