// 11. Дана строка, состоящая из слов на английском языке, разделенных пробелами.Вывести на экран эти слова в порядке алфавита.

// accomodation accident accountant access accompany
// -> access accident accomodation accompany accountant

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>

using namespace std;

void PrintString(char *const *const, int);
void Sort(char**, int, int);
int CountWords(char* const str);
int MaxWordLen(char* const, int);

int main()
{
	char* line = new char[256];
	cout << "Input a string for sort: ";
	cin.getline(line, 256);
	int len = strlen(line);
	int numwords = CountWords(line);
	int maxwordlen = MaxWordLen(line, numwords);

	char** str = new char* [numwords];
	for (int i = 0; i < numwords; ++i) {
		str[i] = new char[maxwordlen + 1];
	}

	int k = 0;
	for (int i = 0; i < numwords; i++) {
		// this buffer string is used to contain words extracted from the string
		char* buf = new char[maxwordlen + 1];
		for (int j = 0; k < len + 1; ++j, ++k) {
			if (line[k] != ' ') {
				buf[j] = line[k];
			} // checking if found the end of the word or if initial string has ended
			else if (line[k] == ' ' || line[k] == '\0') {
				// ending the buffer string with '\0'
				buf[j] = '\0';
				k++;
				break;
			}
		}
		// filling cells of 2d array with extracted words
		strcpy(str[i], buf);
		// freeing memory on each iteration
		delete[] buf;
		buf = nullptr;
	}
	delete[] line; // Freeing memory of initialized string
	line = nullptr;

	Sort(str, numwords, maxwordlen + 1);
	cout << "Sorted string:  ";
	PrintString(str, numwords);
	for (int i = 0; i < numwords; ++i) {
		delete[] str[i];
		str[i] = nullptr;
	}
	delete[] str;
	str = nullptr;
	system("pause");
	return 0;
}

void PrintString(char *const*const str, int numwords) {
	for (int i = 0; i < numwords; i++) {
		cout << str[i] << " ";
	}
	cout << endl;
}

void Sort(char** str, int numwords, int maxwordlen)
{
	char* bufarr = new char[maxwordlen];
	for (int i = 1; i < numwords; ++i) {
		for (int j = 1; j < numwords; ++j) {
			if (strcmp(str[j - 1], str[j]) > 0) {
				strcpy(bufarr, str[j - 1]);
				strcpy(str[j - 1], str[j]);
				strcpy(str[j], bufarr);
			}
		}
	}
	delete[] bufarr;
	bufarr = nullptr;
}

int CountWords(char *const str) {
	int len = strlen(str);
	int number_spaces = 0, number_words = 0;
	for (int i = 0; i < len; ++i) {
		if (str[i] == ' ') {
			number_spaces++;
		}
	}
	number_words = number_spaces + 1;

	return number_words;
}

int MaxWordLen(char *const initialstr, int numberwords) {
	int maxlen = 0, wordlen = 0;
	for (int i = 0; i < numberwords; ++i) {
		int position = 0;
		while (1) {
			if (initialstr[position] != ' ' && initialstr[position] != '\0') {
				wordlen++;
				position++;
			}
			else {
				position++;
				break;
			}
		}
		if (wordlen > maxlen) {
			maxlen = wordlen;
		}
		wordlen = 0;
	}
	return maxlen;
}