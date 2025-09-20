#include "Complex.h"


Complex::Complex(double r, double i) : real(r), imag(i) {}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(double mul) const {
    return Complex(real * mul, imag * mul);
}

Complex Complex::operator*(const Complex& other) const {
    double new_real = real * other.real - imag * other.imag;
    double new_imag = real * other.imag + imag * other.real;
    return Complex(new_real, new_imag);
}

bool Complex::operator<(const Complex& other) const {
    return (real * real + imag * imag) < (other.real * other.real + other.imag * other.imag);
}

bool Complex::operator>(const Complex& other) const {
    return (real * real + imag * imag) > (other.real * other.real + other.imag * other.imag);
}

std::ostream& operator<<(std::ostream& os, const Complex& num) {
    os << num.real << (num.imag >= 0 ? "+" : "") << num.imag << "i";
    return os;
}
