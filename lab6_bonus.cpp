#include <iostream>
#include <iomanip>
#include <conio.h>

int readNumber();
int getRandomNumber(int min, int max);

using namespace std;
int main()
{
	int** A, size, i, j, sum = 0, mult = 1;
	srand(static_cast<unsigned int>(time(nullptr)));

	cout << "Give the size of the array (>0): ";
	do
	size = readNumber();
	while (size < 0);

	A = new int* [size];
	for (i = 0; i < size; i++)
	{
		A[i] = new int[size];
	}
	
	cout << " Type 1 to fill the array manually, else it will be filled randomly." << endl;
	if (_getch() == '1')
	{
		cout << "You've chosen manual fill.\n" << endl;
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				cout << "Give the value of A[" << i << "][" << j << "]: ";
				A[i][j] = readNumber();
			}
		}
		cout << endl;
	}
	else
	{
		cout << "Give the borders for randomizer:" << endl;
		int bord1 = readNumber();
		int bord2 = readNumber();
		cout << endl;
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				A[i][j] = getRandomNumber(bord1, bord2);
			}
		}
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			cout << setw(10) << A[i][j];
		}
		cout << "\n" << endl;
	}
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < i; j++)
		{
			sum += A[i][j];
		}
		for (j = i + 1; j < size; j++)
		{
			mult *= A[i][j];
		}
	}
	cout << "Sum of elements positioned under main diagonal equals to " << sum << endl;
	cout << "Multiplication of elements positioned upper main diagonal equals to " << mult << endl;
	delete[]A;
	system("pause");
	return 0;
}

int readNumber()
{
	int t;
	while (!(std::cin >> t) || std::cin.get() != '\n')
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Wrong input, try again!\n";
	}
	return t;
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}