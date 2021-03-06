#include <iostream>
#include <cmath>
#include <conio.h>
#include <iomanip>

typedef double (*Func)(double, int);

double readNumber();
double Calc_Func_S(double x, int n);
double Calc_Func_Y(double x, int call);
double Calc_Diff(double x, int n);
void Out_Result(Func, double a, double b, double h, int n);

using namespace std;

int main() {
	double a, b, h, x;
	int n;
	cout << "Would you like to use standard input? Type 1 to agree." << endl;
	if (_getch() == '1') {
		cout << "You've chosen [a;b] = [0.1; 1], step h = 0.1, n = 20" << endl;
		a = 0.1;
		b = 1.0;
		h = 0.1;
		n = 20;
	}
	else {
		cout << "Give the value of a: ";
		a = readNumber();
		cout << "Give the value of b: ";
		b = readNumber();
		cout << "Give the value of step h: ";
		h = readNumber();
		cout << "Give the value of n: ";
		n = readNumber();
	}
	cout << "What function would you like to calculate?\n" <<
		"Type 1 -> Y(x) \nType 2 -> S(x) \nType 3 -> |Y(x) - S(x)| \nElse -> both functions " << endl;
	switch (_getch()) {
	case '1':
		cout << "You've chosen Y(x). " << endl;
		Out_Result(Calc_Func_Y, a, b, h, n);
		break;
	case '2':
		cout << "You've chosen S(x). " << endl;
		Out_Result(Calc_Func_S, a, b, h, n);
		break;
	case '3':
		cout << "You've chosen |Y(x) - S(x)|. " << endl;
		Out_Result(Calc_Diff, a, b, h, n);
		break;
	default:
		cout << "You've chosen all functions.\n" << endl;
		cout << "\tFunction S(x)" << endl;
		Out_Result(Calc_Func_S, a, b, h, n);
		cout << "\tFunction Y(x)" << endl;
		Out_Result(Calc_Func_Y, a, b, h, n);
		cout << "\tFunction |Y(x) - S(x)|\n" << endl;
		Out_Result(Calc_Diff, a, b, h, n);
		break;
	}
	system("pause");
	return 0;
}

double readNumber() {
	double t;
	while (!(std::cin >> t) || std::cin.get() != '\n') {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Wrong input, try again!\n";
	}
	return t;
}

double Calc_Func_S(double x, int n) {
	double r = 1, s = 1;
	for (int k = 1; k <= n; ++k) {
		r = -r * x * x / ((k * 2 - 1) * 2 * k);
		s += r;
	}
	return s;
}

double Calc_Func_Y(double x, int call) {
	return cos(x);
}

double Calc_Diff(double x, int n) {
	return (Calc_Func_Y(x, n) - Calc_Func_S(x, n));
}

void Out_Result(Func F, double a, double b, double h, int n) {
	double x;
	for (x = a; x <= b; x += h) {
		cout << setw(10) << "x = " << x << setw(10) << "F(x) = " << F(x, n) << endl;
	}
}