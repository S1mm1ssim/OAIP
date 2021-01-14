// 4) Print personal data of students
// Make a function to print data of students who got 8 or 9 grades in maths
// Each registration must contain the following data fields:
// - Surname, name and patronymic
// - Birth date
// - Group number
// - Marks in maths, physics, chemistry, information technology
// - Average mark

#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <stdio.h>

// Max number of symbols of data fields in the structure Student
const int kNameSize = 25;
const int kGroupNumDigits = 7;
const int kBirthNumDigits = 11;

// File that data will be written in
const char* const kDataFile = "D:\\studentsList.txt";
// Buffer output file that will be renamed to kDataFile
const char* const kBufFile = "D:\\studentsListOut.txt";

struct Student {
	char surname[kNameSize];
	char name[kNameSize];
	char group[kGroupNumDigits];
	char date_of_birth[kBirthNumDigits];
	int maths, physics, chemistry, informtech;
	double averagemark;
};

const int kByteSizeStudent = sizeof(Student);

void WriteFileStudents();
void AppendFileStudents();
void ReadFileStudents(const char* const);
void SearchFileStudents();  // Individual task
void PrintStudent(const Student&);
void CorrectStudentData();
void DeleteFileStudents();
void SortFileStudents();
Student ReadStudent();
int ReadNumber();
int GetNumStud();
int GetMark();

template <typename T, T Student::* M>
void BubbleSort(Student* arr, int size) {
	Student temp;
	for (int j = 0; j < size - 1; ++j) {
		int flag = 0;
		for (int i = 0; i < size - j - 1; ++i) {
			if (arr[i].*M > arr[i + 1].*M) {
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				flag = 1;
			}
		}
		if (flag == 0) { break; }
	}
}
template <typename T, T Student::* M>
void AlphabeticalSort(Student* arr, int size) {
	Student temp;
	for (int i = 1; i < size; ++i) {
		for (int j = 1; j < size; ++j) {
			if (strcmp(arr[j - 1].*M, arr[j].*M) > 0) {
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

double CountAverageMark(Student& s) {
	return (s.maths + s.physics + s.chemistry + s.informtech) / 4.;
}

int main() {
	std::cout << "The data will be written to " << kDataFile << std::endl;
	while (1) {
		std::cout << "Make a choise.\n"
			<< "\t1 - Create\n"
			<< "\t2 - Append\n"
			<< "\t3 - Correct\n"
			<< "\t4 - View\n"
			<< "\t5 - Task\n"
			<< "\t6 - Delete\n"
			<< "\t7 - Sort\n"
			<< "\tESC - Exit" << std::endl;
		switch (_getch()) {
		case '1':
			std::cout << "You've chosen to create a new file if it hasn't existed yet and to "
				<< "clear old data from the file and further on write new data into it." << std::endl;
			WriteFileStudents();
			break;
		case '2':
			std::cout << "You've chosen to append a student to the list." << std::endl;
			AppendFileStudents();
			break;
		case '3':
			std::cout << "You've chosen to correct data in the file." << std::endl;
			CorrectStudentData();
			break;
		case '4':
			ReadFileStudents(kDataFile);
			break;
		case '5':
			SearchFileStudents();
			break;
		case '6':
			std::cout << "You've chosen to delete data from the file." << std::endl;
			std::cout << "Are you sure you want to delete data? Type '9' to continue." << std::endl;
			if (_getch() == '9') {
				DeleteFileStudents();
			}
			else {
				std::cout << "You've declined to delete data." << std::endl;
			}
			break;
		case '7':
			std::cout << "You've chosen to sort students data." << std::endl;
			SortFileStudents();
			break;
		case 27:
			std::cout << "Exiting the program..." << std::endl;
			system("pause");
			return 0;
		}

	}
}

void WriteFileStudents() {
	std::ofstream fout(kDataFile, std::ios::binary | std::ios::trunc | std::ios::out);
	std::cout << "Give the number of students: ";
	int numstud = ReadNumber();
	while (numstud <= 0) {
		std::cout << "The number of students can't be below 1" << std::endl;
		numstud = ReadNumber();
	}
	for (int i = 0; i < numstud; ++i) {
		Student stud = ReadStudent();
		fout.write((char*)&stud, kByteSizeStudent);
	}
	fout.close();
}

void AppendFileStudents() {
	std::cout << "How many students would you like to append?" << std::endl;
	std::cout << "Input: ";
	int appnum = ReadNumber();
	while (appnum < 0) {
		appnum = ReadNumber();
	}

	std::ofstream fadd(kDataFile, std::ios::binary | std::ios::app);  // Opened the file in append mode
	for (int i = 0; i < appnum; ++i) {
		Student stud = ReadStudent();
		fadd.write((char*)&stud, kByteSizeStudent);  // Appended the structure
	}
	fadd.close();
}

void ReadFileStudents(const char* const file) {
	std::ifstream fin(file, std::ios::in | std::ios::binary);
	if (!fin.is_open()) {
		std::cout << "Unable to open the file!" << std::endl;
	}
	else {
		fin.seekg(0, std::ios::end);
		if (fin.tellg() == 0 && fin.is_open()) {
			std::cout << "\nThe file is empty.\n" << std::endl;
			fin.seekg(0, std::ios::beg);
			fin.close();
		}
		else {
			fin.seekg(0, std::ios::beg);
			Student bufstud{};
			int i = 0;
			std::cout << "----------------------------------------------------------INFORMATION----------------------------------------------------------------------" << std::endl;
			std::cout << std::setw(16) << "SURNAME" << std::setw(14)
				<< "NAME" << std::setw(14)
				<< "GROUP" << std::setw(18)
				<< "DATE OF BIRTH" << std::setw(17)
				<< "MATHS" << std::setw(15)
				<< "PHYSICS" << std::setw(15)
				<< "CHEMISTRY" << std::setw(15)
				<< "INFORMTECH" << std::setw(15)
				<< "AVERAGE_MARK" << std::endl;
			while (fin.read((char*)&bufstud, kByteSizeStudent)) {
				std::cout << i + 1 << std::setw(4);
				PrintStudent(bufstud);
				++i;
			}
			std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
			fin.close();
		}
	}
}

Student ReadStudent() {
	Student stud{};
	std::cout << "Give student's surname: ";
	std::cin.getline(stud.surname, kNameSize);
	std::cout << "Give student's name: ";
	std::cin.getline(stud.name, kNameSize);
	std::cout << "Give student's group number: ";
	std::cin.getline(stud.group, kGroupNumDigits);
	std::cout << "Give student's date of birth: ";
	std::cin.getline(stud.date_of_birth, kBirthNumDigits);
	std::cout << "Give student's mark in maths: ";
	stud.maths = GetMark();
	std::cout << "Give student's mark in physics: ";
	stud.physics = GetMark();
	std::cout << "Give student's mark in chemistry: ";
	stud.chemistry = GetMark();
	std::cout << "Give student's mark in information technology: ";
	stud.informtech = GetMark();
	stud.averagemark = CountAverageMark(stud);
	std::cout << std::endl;
	return stud;
}

void PrintStudent(const Student& stud) {
	std::cout << std::setw(16) << stud.surname << std::setw(14)
		<< stud.name << std::setw(14)
		<< stud.group << std::setw(15)
		<< stud.date_of_birth << std::setw(17)
		<< stud.maths << std::setw(15)
		<< stud.physics << std::setw(15)
		<< stud.chemistry << std::setw(15)
		<< stud.informtech << std::setw(15)
		<< stud.averagemark << std::endl;
}

void SearchFileStudents() {
	std::ifstream finp(kDataFile, std::ios::in | std::ios::binary);
	if (!finp.is_open()) {
		std::cout << "Unable to open the file!" << std::endl;
	}
	else {
		finp.seekg(0, std::ios::end);
		if (finp.tellg() == 0 && finp.is_open()) {
			std::cout << "\n\tThe file is empty.\n" << std::endl;
			finp.seekg(0, std::ios::beg);
			finp.close();
		}
		else {
			finp.seekg(0, std::ios::beg);
			bool isFound = false;
			Student bufstud{};
			int i = 0;
			std::cout << "Information about students whose surnames start with letter 'A' and who have got grades 8 or 9 in maths" << std::endl;
			std::cout << "-----------------------------------------------------------INFORMATION---------------------------------------------------------------------" << std::endl;
			while (finp.read((char*)&bufstud, kByteSizeStudent)) {
				// If surname begins with letter A (including Russian)
				if (bufstud.surname[0] == 'A' || bufstud.surname[0] == 'À') {
					// And marks in maths are 8 or 9
					if (bufstud.maths == 8 || bufstud.maths == 9) {
						isFound = true;
						std::cout << i + 1 << "  ";
						PrintStudent(bufstud);
					}
				}
				++i;
			}
			if (isFound == false) {
				std::cout << "There are no appropriate students." << std::endl;
			}
			std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
			finp.close();
		}
	}
}

void CorrectStudentData() {
	std::ifstream finp(kDataFile, std::ios::in | std::ios::binary);
	finp.seekg(0, std::ios::end);
	if (!finp.is_open()) {
		std::cout << "Unable to open the file!" << std::endl;
	}
	else {
		if (finp.tellg() == 0 && finp.is_open()) {
			std::cout << "\tThe file is empty." << std::endl;
			finp.seekg(0, std::ios::beg);
			finp.close();
		}
		else {
			finp.seekg(0, std::ios::beg);
			std::cout << "Give the index of a student you want to make a correction of: " << std::endl;
			int index = ReadNumber();
			int studnum = GetNumStud();
			while (index < 1 || index > studnum) {
				std::cout << "There are " << studnum << " students in the file" << std::endl;
				index = ReadNumber();
			}
			std::ofstream fout(kBufFile, std::ios::binary | std::ios::out);  // Buffer file, then it will be renamed
			Student bufstud{};
			for (int studind = 0; studind < studnum; studind++) {
				finp.read((char*)&bufstud, kByteSizeStudent);
				if (studind == index - 1) {
					while (1) {
						std::cout << "Choose what data field you would like to correct.\n"
							<< "\t1 - Surname\n"
							<< "\t2 - Name\n"
							<< "\t3 - Group\n"
							<< "\t4 - Date of birth\n"
							<< "\t5 - Mark in maths\n"
							<< "\t6 - Mark in physics\n"
							<< "\t7 - Mark in chemistry\n"
							<< "\t8 - Mark in information science\n"
							<< "\t9 - Exit" << std::endl;
						char count = _getch();
						if (count == '9') {
							std::cout << "You have declined to make a correction." << std::endl;
							break;
						}
						else {
							switch (count) {
							case '1':
								std::cout << "Give new surname: ";
								std::cin.getline(bufstud.surname, kNameSize);
								break;
							case '2':
								std::cout << "Give new name: ";
								std::cin.getline(bufstud.name, kNameSize);
								break;
							case '3':
								std::cout << "Give new group: ";
								std::cin.getline(bufstud.group, kGroupNumDigits);
								break;
							case '4':
								std::cout << "Give new date of birth: ";
								std::cin.getline(bufstud.date_of_birth, kBirthNumDigits);
								break;
							case '5':
								std::cout << "Give new mark in maths: ";
								bufstud.maths = GetMark();
								bufstud.averagemark = CountAverageMark(bufstud);
								break;
							case '6':
								std::cout << "Give new mark in physics: ";
								bufstud.physics = GetMark();
								bufstud.averagemark = CountAverageMark(bufstud);
								break;
							case '7':
								std::cout << "Give new mark in chemistry: ";
								bufstud.chemistry = GetMark();
								bufstud.averagemark = CountAverageMark(bufstud);
								break;
							case '8':
								std::cout << "Give new mark in information science: ";
								bufstud.informtech = GetMark();
								bufstud.averagemark = CountAverageMark(bufstud);
								break;
							}
						}
					}
				}
				fout.write((char*)&bufstud, kByteSizeStudent);
			}
			finp.close();
			fout.close();
			remove(kDataFile);
			if (rename(kBufFile, kDataFile)) {
				std::cout << "Rename error!" << std::endl;
			}
		}
	}
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

int GetNumStud() {
	std::ifstream read(kDataFile, std::ios::in | std::ios::binary);
	std::streampos begin, end;
	begin = read.tellg();  // Returns the position of the current character in the input stream.
	read.seekg(0, std::ios::end);  // Sets the position of the last character of the input stream
	end = read.tellg();
	read.seekg(0, std::ios::beg);
	read.close();
	return static_cast<int>((end - begin) / kByteSizeStudent);  // Finding the number of students through number of written in the file bytes
}

int GetMark() {
	int mark = ReadNumber();
	while (mark < 0 || mark > 10) {
		std::cout << "Marks can't be less than 0 and higher than 10. Try again." << std::endl;
		mark = ReadNumber();
	}
	return mark;
}

void DeleteFileStudents() {
	std::ifstream finp(kDataFile, std::ios::in | std::ios::binary);
	if (!finp.is_open()) {
		std::cout << "Unable to open the file!" << std::endl;
	}
	else {
		finp.seekg(0, std::ios::end);
		if (finp.tellg() == 0 && finp.is_open()) {
			std::cout << "\tThe file is empty." << std::endl;
			finp.seekg(0, std::ios::beg);
			finp.close();
		}
		else {
			finp.seekg(0, std::ios::beg);
			Student bufstud{};
			std::cout << "Give the index of a student you want to delete information about: " << std::endl;
			int index = ReadNumber();
			int studnum = GetNumStud();
			while (index < 1 || index > studnum) {
				std::cout << "There are " << studnum << " students in the file" << std::endl;
				index = ReadNumber();
			}
			std::ofstream fout(kBufFile, std::ios::binary | std::ios::out);  // Buffer file, then it will be renamed

			int studind = 0;
			while (finp.read((char*)&bufstud, kByteSizeStudent)) {
				if (studind == index - 1) {
					++studind;
				}
				else {
					fout.write((char*)&bufstud, kByteSizeStudent);
					++studind;
				}
			}

			finp.close();
			fout.close();
			remove(kDataFile);
			if (rename(kBufFile, kDataFile)) {
				std::cout << "Rename error!" << std::endl;
			}
		}
		std::cout << "Success!" << std::endl;
	}
}

void SortFileStudents() {
	std::ifstream fin(kDataFile, std::ios::in || std::ios::binary);
	if (!fin.is_open()) {
		std::cout << "Unable to open the file!" << std::endl;
	}
	else {
		fin.seekg(0, std::ios::end);
		if (fin.tellg() == 0 && fin.is_open()) {
			std::cout << "\tThe file is empty." << std::endl;
			fin.seekg(0, std::ios::beg);
			fin.close();
		}
		else {
			fin.seekg(0, std::ios::beg);
			int numstud = GetNumStud();
			Student* array = new Student[numstud];
			for (int i = 0; i < numstud; ++i) {
				fin.read((char*)&array[i], kByteSizeStudent);
			}
			fin.close();

			while (1) {
				std::cout << "\tTo sort students in alphabetical order by surnames type 1.\n"
					<< "\tTo sort students in alphabetical order by names type 2.\n"
					<< "\tTo sort students by average mark type 3.\n"
					<< "\tTo sort students by mark in maths type 4.\n"
					<< "\tTo sort students by mark in physics type 5.\n"
					<< "\tTo sort students by mark in information science type 6.\n"
					<< "\tTo sort students by mark in chemistry type 7." << std::endl;
				switch (_getch()) {
				case '1':
					AlphabeticalSort<char[kNameSize], &Student::surname>(array, numstud);
					std::cout << "\nSorted by surnames in alphabetical order: " << std::endl;
					break;
				case '2':
					AlphabeticalSort<char[kNameSize], &Student::name>(array, numstud);
					std::cout << "\nSorted by names in alphabetical order: " << std::endl;
					break;
				case '3':
					BubbleSort<double, &Student::averagemark>(array, numstud);
					std::cout << "\nSorted by average mark in increasing order: " << std::endl;
					break;
				case '4':
					BubbleSort<int, &Student::maths>(array, numstud);
					std::cout << "\nSorted by marks in maths in increasing order: " << std::endl;
					break;
				case '5':
					BubbleSort<int, &Student::physics>(array, numstud);
					std::cout << "\nSorted by marks in physics in increasing order: " << std::endl;
					break;
				case '6':
					BubbleSort<int, &Student::informtech>(array, numstud);
					std::cout << "Sorted by marks in information technology in increasing order: " << std::endl;
					break;
				case '7':
					BubbleSort<int, &Student::chemistry>(array, numstud);
					std::cout << "\nSorted by marks in chemistry in increasing order: " << std::endl;
					break;
				}
				std::ofstream fout(kBufFile, std::ios::binary | std::ios::out);
				for (int i = 0; i < numstud; ++i) {
					fout.write((char*)&array[i], kByteSizeStudent);
				}
				fout.close();
				ReadFileStudents(kBufFile);
				remove(kBufFile);
				std::cout << "To exit viewing sorted file type 0. If any other key's pressed you will be proposed to sort data in one or another way." << std::endl;
				if (_getch() == '0') { break; }
			}
			delete[] array;
			array = nullptr;
		}
	}
}
