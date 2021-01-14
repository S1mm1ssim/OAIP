// 4) Given a matrix of size NxM find the number of 'special' elements
// The element is count as 'special' if its value is bigger than the sum the rest column elements

#include <iostream>
#include <iomanip>
#include <stdio.h>

int ReadNumber();
void PrintArray(const int **array, int n, int m);

using namespace std;

int main() {
	int n, m, **Arr, counter = 0, sum = 0, i, j;

	cout << "Give the measurements of the array. N rows x M columns (both must be > 0)" << endl;
	do {
		n = ReadNumber();
	} while (n < 0);
	do {
		m = ReadNumber();
	} while (m < 0);
	Arr = new int* [n];
	for (i = 0; i < n; ++i) {
		Arr[i] = new int[m];
	}

	cout << "The array will be filled by columns for conviniece." << endl;
	for (j = 0; j < m; ++j) {
		for (i = 0; i < n; ++i) {
			cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
			Arr[i][j] = ReadNumber();
			sum += Arr[i][j];
		}
		for (i = 0; i < n; ++i) {
			if (Arr[i][j] > sum - Arr[i][j]) {
				cout << "Your special element: " << Arr[i][j] << endl;
				counter++;
			}
		}
		sum = 0;
	}
	cout << endl;
	PrintArray(Arr, n, m);

	if (counter == 0) {
		cout << "There's no 'special' numbers in the array." << endl;
	}
	else {
		cout << "The number of 'special' numbers is " << counter << endl;
	}

	for (i = 0; i < n; ++i) {
		delete[] Arr[i];
		Arr[i] = nullptr;
	}
	delete[] Arr;
	Arr = nullptr;
	system("pause");
	return 0;
}

int ReadNumber() {
	int t;
	while (!(std::cin >> t) || std::cin.get() != '\n') {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Wrong input, try again!\n";
	}
	return t;
}

void PrintArray(const int **array, int n, int m) {
	if (!array) { return; }
	cout << "Your array:" << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << setw(10) << array[i][j];
		}
		cout << "\n" << endl;
	}
}
