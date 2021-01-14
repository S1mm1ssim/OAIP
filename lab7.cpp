// In a string consisting of groups of zeros and ones print groups containing even amount of elements

#include <iostream>
#include <conio.h>

using namespace std;

void Input(char*);
void Output(char*);

int main() {
	char str[256];
	cout << "Input string consisting of zeros, ones and space" << endl;
	Input(str);
	cout << "Groups containing even number of characters are: " << endl;
	Output(str);
	system("pause");
	return 0;
}

void Input(char* s) {
	int i = 0;
	while (1) {
		s[i] = _getch();
		if (s[i] == 13) { break; }
		if (!(s[i] == '0' || s[i] == '1' || s[i] == ' ')) { continue; }
		cout << s[i];
		i++;
	}
	s[i] = '\0';
	cout << endl;
}

void Output(char* str) {
	bool FOUND_BLOCK = false;
	int len = strlen(str);
	int begin = 0, end = 0;
	int block_length = 0;
	int i = 0;
	for (int i = 0; i <= len; ++i) {
		if (FOUND_BLOCK == false) {
			block_length = 0;
			if (str[i] != ' ' && str[i] != '\0') {
				FOUND_BLOCK = true;
				begin = i;
			}
		}
		if (str[i] != ' ' && str[i] != '\0') {
			block_length++;
			continue;
		}
		if (FOUND_BLOCK == true) {
			if (str[i] == ' ' || str[i] == '\0') {
				FOUND_BLOCK = false;
				end = i;
			}
		}
		if (block_length != 0 && block_length % 2 == 0) {
			for (int k = begin; k < end; ++k) {
				cout << str[k];
			}
			cout << endl;
		}
	}
}
