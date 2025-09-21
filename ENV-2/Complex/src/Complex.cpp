#include "../include/Complex.h"
#include <cmath>
#include <iostream>

Complex::Complex(double real, double imag) : _real(real), _imag(imag){}

Complex Complex::operator+(const Complex& other) const{
	return Complex(_real + other._real, _imag + other._imag);
	}
Complex Complex::operator-(const Complex& other) const {
	return Complex(_real - other._real, _imag - other._imag);
	}

double Complex::abs() const{
	return std::sqrt(_real * _real + _imag * _imag);
}
double Complex::getReal() const {
return _real;
}
double Complex::getImag()const {
return _imag;
}

std::ostream& operator<< (std::ostream& os, const Complex& c) {
	os << c._real;
	if(c._imag >= 0) {
		os << "+" << c._imag <<"i";
	}else{
		os << "-" << c._imag << "i";
	}
	return os;
}
Complex operator*(double k, const Complex& c ) {
	return Complex(k * c._real, k * c._imag);
}
