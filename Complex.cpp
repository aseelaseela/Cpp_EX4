#include "Complex.hpp"

// Constructors
Complex::Complex() : real(0.0), imaginary(0.0) {}

Complex::Complex(double re, double im) : real(re), imaginary(im) {}

// Getter methods
double Complex::getReal() const {
    return real;
}

double Complex::getImaginary() const {
    return imaginary;
}

// Setter methods
void Complex::setReal(double re) {
    real = re;
}

void Complex::setImaginary(double im) {
    imaginary = im;
}

// Arithmetic operations
Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imaginary + other.imaginary);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imaginary - other.imaginary);
}

Complex Complex::operator*(const Complex& other) const {
    double result_real = real * other.real - imaginary * other.imaginary;
    double result_imaginary = real * other.imaginary + imaginary * other.real;
    return Complex(result_real, result_imaginary);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    double result_real = (real * other.real + imaginary * other.imaginary) / denominator;
    double result_imaginary = (imaginary * other.real - real * other.imaginary) / denominator;
    return Complex(result_real, result_imaginary);
}

// Comparison operators
bool Complex::operator==(const Complex& other) const {
    return (real == other.real) && (imaginary == other.imaginary);
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

bool Complex::operator<(const Complex& other) const {
    return (real < other.real) || (real == other.real && imaginary < other.imaginary);
}

bool Complex::operator>(const Complex& other) const {
    return (real > other.real) || (real == other.real && imaginary > other.imaginary);
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real << " + " << c.imaginary << "i";
    return os;
}
