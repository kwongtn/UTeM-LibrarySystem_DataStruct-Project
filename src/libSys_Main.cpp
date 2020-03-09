// LibrarySystem_DataStruct.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _WIN32_WINNT 0x0502
#include<windows.h>
#include "./libSys.h"

using namespace std;

void line(), line(int);

int main(){
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) {
		SetWindowPos(hwnd, 0, 0, 0, 1000, 600, SWP_SHOWWINDOW | SWP_NOMOVE);
	}
	libTable borrow("borrow");

	while (true) {
		char tableAccess, action;
		line();
		//cout << "\nWhat table do you want to access?\nB\tBorrow\n\nE\tExit Program\n\n\nYour choice : ";
		//cin >> tableAccess;
		//tableAccess = tolower(tableAccess);
		//if (tableAccess == 'e') {
		//	cout << "Exiting program. ";
		//	system("pause");
		//	exit(0);
		//} else if (tableAccess != 'b') {
		//	cout << "Invalid Option, please choose again." << endl << endl;
		//	continue;
		//}
		//line();
		cout << "\n\nWhat action do you want to take?\nI\tInsert Entry\nD\tDelete Entry\nS\tSort Entries\nV\tView Entry\nE\tExport Entries\n\nAny\tExit\n\n\nYour choice : ";
		cin >> action;
		action = tolower(action);
		if (action != 'i' && action != 'd' && action != 'v' && action != 'e' && action != 's') {
			system("pause");
			exit(0);
		}

		if (action == 'i') {
			borrow.newEntry();
		} else if (action == 'd') {
			borrow.entryDelete();
		} else if (action == 'v') {
			borrow.dataOutput();
		} else if (action == 's') {
			line();
			cout << "What criteria do you want to sort by?" << endl;
			borrow.attribList();
			cout << "Sort by ? ";
			char sortChar;
			cin >> sortChar;
			sortChar = tolower(sortChar);
			if (sortChar != 'n' && sortChar != 'i' && sortChar != 'd' && sortChar != 'b') {
				continue;
			} else {
				borrow.sort(sortChar);
			}
		} else if (action == 'e') {
			borrow.exportEntries();
		}

	}
	return 0;
}

// Couts a line.
void line() {
	cout << endl;
	for (int i = 0; i < 50; i++) {
		cout << "=";
	}
	cout << endl;
}

// Couts a specified number of lines.
void line(int k) {
	for (int j = 0; j < k; j++) {
		line();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


/* File for input:
<name> <attrib> <year> <month> <day> <hour> <minute> <second>
*/