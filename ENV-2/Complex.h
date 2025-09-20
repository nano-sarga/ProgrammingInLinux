#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>


class Complex {
private:
    double real;
    double imag;
public:
    Complex(double r = 0, double i = 0);

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(double mul) const;
    Complex operator*(const Complex& other) const;

    bool operator<(const Complex& other) const; 
    bool operator>(const Complex& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& num);
};

#endif
