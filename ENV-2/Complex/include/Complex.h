#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
private:
        double _real;
        double _imag;
public:
        Complex(double real = 0.0, double imag = 0.0);
		double getReal() const;
		double getImag() const;

        Complex operator+(const Complex& other) const;
        Complex operator-(const Complex& other) const;

        double abs() const;

        friend std::ostream& operator<<(std::ostream& os, const Complex& c);
        friend Complex operator*(double k, const  Complex& c);

};
#endif //COMPLEX_H


