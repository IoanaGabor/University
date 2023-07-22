//
// Created by ioana on 26.05.2023.
//

#ifndef T3_913_GABOR_IOANA_EQUATION_H
#define T3_913_GABOR_IOANA_EQUATION_H


class Equation {
private:
    double a,b,c;
public:
    bool operator<(const Equation &rhs) const;

public:
    double getA() const;

    double getB() const;

    double getC() const;

public:
    Equation(double a, double b, double c);
    std::string toString();
    std::string solutionsAsString();
    bool operator==(const Equation &rhs) const;
    int degree() const;
    bool operator!=(const Equation &rhs) const;
};


#endif //T3_913_GABOR_IOANA_EQUATION_H
