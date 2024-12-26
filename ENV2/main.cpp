#include <iostream>
#include "complex.h"
#include <algorithm>

void sortComplexNumbers(std::vector<Complex>& vec) {
	std::sort(vec.begin(), vec.end(), [](const Complex& a, const Complex& b) {
		return a.abs() < b.abs();
		});
}

int main(int argv, char* argc[]) {
	using std::cout;
	using std::endl;

	// Initialization of the object
	Complex C1(2, 2);
	cout << C1 << endl;

	// Copy constructor usage
	Complex C2(C1);
	Complex C3(3, 5);
	

	cout << "\nOperator += and operator -= usage:\n";
	Complex C4(0, 0);
	cout << C4 << endl;
	C4 += C3 += C3;
	cout << C4 << endl;
	C4 -= C1;
	cout << C4 << endl;

	cout << "\nOperator *= usage:\n";
	Complex multiplier1(3, 4);
	Complex multiplier2(2, 3);
	Complex m1(multiplier1);
	multiplier1 *= multiplier2;
	cout << m1 << " *= " << multiplier2 << " => " << multiplier1 << endl;

	cout << "\nOperator /= usage:\n";
	Complex denom(2, 3);
	Complex nom(8, 6);
	Complex nom1(nom);
	nom /= denom;
	cout << nom1 << " /= " << denom << " => " << nom << endl;

	cout << "\nClass n1 * class n2: \n";
	Complex n1(3, 3);
	Complex n2(4, 4);
	Complex n3 = n1 * n2;
	cout << n1 << " * " << n2 << " = " << n3;

	cout << "\n\nClass n4 / class n5: \n";
	Complex n4(10, 10);
	Complex n5(2, 2);
	Complex n6 = n3 / n4;
	cout << n4 << " / " << n5 << " = " << n6;

	
	cout << "\nChecking equality and inequality of complex numbers:\n";
	Complex f1(2, 3);
	Complex f2(1, 3);
	Complex f3(1, 3);
	cout << f1 << "\n" << f2 << "\n" << f3 << "\n\n";
	cout << "f1 != f2:";
	if (f1 != f2) {
		cout << "\nthey're not equal\n";
	}
	cout << "f2 == f3";
	if (f2 == f3) {
		cout << "\nthey're equal\n";
	}

	cout << "\nMath function usage:\n";
	cout << "abs: " << C2.abs() << endl;
	cout << "conjugate: " << C3.conjugate() << endl;
	cout << "arg:" << C4.arg() << endl;

	std::vector<Complex> complexNumbers = {
		C1,C2,C3,f1,f2,f3
	};

	sortComplexNumbers(complexNumbers);

	cout << "\nSorted complex numbers:\n";
	for (const auto& num : complexNumbers) {
		cout << num << '\n';
	}

	return 0;
}
