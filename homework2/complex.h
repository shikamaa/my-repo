
#include <iostream>
#include <cmath>
#include <vector>

class Complex {
public:
	Complex(double re = 0, double im = 0): re(re), im(im) {}
	Complex(const Complex* other) {
		re = other->re;
		im = other->im;
	}
	friend std::ostream& operator<<(std::ostream& out, const Complex& obj) {
		out << obj.re << " " << obj.im << "i";
		return out;
	}
	double abs() const {
		return sqrt(re * re + im * im);
	}
	Complex& operator+=(const Complex& other) {
		re += other.re;
		im += other.im;
		return *this;
	}
	Complex& operator-=(const Complex& other) {
		re -= other.re;
		im -= other.im;
		return *this;
	}
	Complex& operator*=(const Complex& other) {
		double old_re = re;
		re = (re * other.re) - (im * other.im);
		im = (old_re * other.im) + (im * other.re);
		return *this;
	}
	Complex& operator/=(const Complex& other) {
		double old_re = re;
		double _denom = other.re * other.re + (other.im * other.im);
		re = ((re * other.re) + (other.im * im)) / _denom;
		im = ((im * other.re) - (other.im * old_re)) / _denom;
		return *this;
	}
	Complex operator+(const Complex& other) {
		Complex result;
		result.re = re + other.re;
		result.im = im + other.im;
		return result;
	}
	Complex operator-(const Complex& other) {
		Complex result;
		result.re = re - other.re;
		result.im = im - other.im;
		return result;
	}
	Complex operator*(const Complex& other) {
		Complex result;
		result.re = re * other.re - im * other.im;
		result.im = re * other.im + im * other.re;
		return result;
	}
	Complex operator/(const Complex& other) {
		Complex result = *this;
		result /= other;
		return result;
	}
	Complex& operator=(const Complex& other) {
		if (this != &other) {
			re = other.re;
			im = other.im;
		}
		return *this;
	}
	bool operator==(const Complex& other) {
		return re == other.re && im == other.im;
	}
	bool operator!=(const Complex& other) {
		return !(re == other.re && im == other.im);
	}
	double arg() const {
		return std::atan2(im, re);
	}

	Complex conjugate() const {
		return Complex(re, -im);
	}
	~Complex() {}
private:
	double re;
	double im;
};

void sortComplexNumbers(std::vector<Complex>& vec);
