#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    // Constructors
    Complex();
    Complex(double re, double im);

    // Getter methods
    double getReal() const;
    double getImaginary() const;

    // Setter methods
    void setReal(double re);
    void setImaginary(double im);

    // Arithmetic operations
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Comparison operators
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    bool operator<(const Complex& other) const;
    bool operator>(const Complex& other) const;

    // Output stream operator
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#endif // COMPLEX_HPP
