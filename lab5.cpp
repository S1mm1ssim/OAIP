//4) В одномерном массиве, состоящем из n элементов, найти сумму элементов между первым и последним положительными элементами 

#include <iostream>
#include <ctime>
#include <iomanip>
#include <conio.h>

int ReadNumber();
int GetRandomNumber(int min, int max);

using namespace std;

int main() {
	int n, A[10]{}, bord1, bord2, pos1 = -1, pos2 = -1, s = 0, i, counter = 0;
	
	srand(static_cast<unsigned int>(time(nullptr)));

	cout << "Give the size of the array(from 1 to 10): ";
	n = ReadNumber();
	while (n < 1 || n > 10) {
		std::cout << "Wrong input, try again!\n";
		n = ReadNumber();
	}

	cout << " Type 1 to fill the array manually, else it will be filled randomly." << endl;
	if (_getch() == '1') {
		cout << "You've chosen manual fill.\n" << endl;
		for (i = 0; i < n; i++) {
			cout << "Give the value of " << i + 1 << "th element: ";
			A[i] = ReadNumber();
			if (A[i] > 0) {
				if (pos1 == -1) {
					pos1 = i;
				}
				pos2 = i;
				counter++;
			}
		}
		cout << "\nYour array: \n" << endl;
		for (i = 0; i < n; ++i) {
			cout << setw(10) << A[i];
		}
		cout << "\n" << endl;
	}
	else {
		cout << "Give the borders for randomizer:" << endl;
		bord1 = ReadNumber();
		bord2 = ReadNumber();
		cout << endl;

		for (i = 0; i < n; ++i) {
			A[i] = GetRandomNumber(bord1, bord2);
			if (A[i] > 0) {
				if (pos1 == -1) {
					pos1 = i;
				}
				pos2 = i;
				counter++;
			}
			cout << setw(10) << A[i];
		}
		cout << "\n" << endl;
	}
	if (counter == 0) {
		cout << "There's no positive numbers in the array." << endl;
	}
	else if (counter == 1) {
		cout << "There's only 1 positive number in the array." << endl;
	}
	else if (A[pos1 + 1] > 0 && counter == 2) {
		cout << "There's only 2 positive numbers in the array and they are placed next to each other." << endl;
	}
	else {
		for (i = pos1 + 1; i < pos2; i++) {  // Calculating the sum of elements
			s += A[i];
		}
		cout << "Sum of elements bettween first and last positive elements equals to " << s << endl;
	}
	system("pause");
	return 0;
}

int ReadNumber() {
	int t;
	while (!(std::cin >> t) || std::cin.get() != '\n')
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Wrong input, try again!\n";
	}
	return t;
}

int GetRandomNumber(int min, int max) {
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}