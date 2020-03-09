#ifndef LIB_H
#define LIB_H
#pragma warning(suppress : 4996)

#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <fstream>
#include <cmath>
using namespace std;

const int ALLOWED_BORROW = 3;

class libTable {
	public:
		libTable(string);
		~libTable();
		/* 
		Variables vs use cases:
		Variable          | User          | Borrow          | Book
		name              | userName      | userName        | bookName
		date              | borrowedDate  | borrowedDate    | purchaseDate
		count             | canLendCount  | transactionCount| booksRemaining

		When count = 0, no books will be allowed in any case.
		During any transaction, the last transaction will be added to the end of the linked list.
		Every transaction consists of userName, date, book.

		*/

		// String for column description.
		string strName;
		string strAttribName;
		string strCount;
		string strDate;

		fstream file;

		// Main structure description.
		struct entry {
			int id;
			string name;
			string attribName;
			double year;
			double month;
			double day;
			double hour;
			double minute;
			double second;
			double dateTimeInt;
			entry* next = NULL;
			entry* prev = NULL;
		};
		entry myEntry;

		// Internal counters
		int count;
		int idCount;
		int maxID();

		// File manipulation methods
		void fileInput();
		void fileInput(string);
		void exportEntries();

		// Pointer manipulation methods
		void resetPointer();
		void jumpLastEntry();

		// Methods for entries
		void entryInsert(int);
		void entryDelete();
		void entrySwap(entry*, entry*);
		void newEntry();
		void dataOutput();
		void dataOutput(bool);
		void dateTimeInput();
		void dateTimeOutput();
		double dateTimeFunc(entry*);
		void sort(char);

		void attribList();

		// Entry pointers
		entry* headEntry = 0;
		entry* currEntry;
		entry* prevEntry;

	private:

};

// Initializes strName, strCount and strDate
libTable::libTable(string i) {
	idCount = 0;
	if (i == "user") {
		strName = "User Name";
		strCount = ALLOWED_BORROW;
		strDate = "User Creation";
	} else if (i == "borrow") {
			strName = "User Name";
			strCount = "Transaction Count";
			strDate = "Transaction Date";
			strAttribName = "Book Name";
		} else if (i == "book") {
			strName = "Book Name";
			strCount = "Books Remaining";
			strDate = "Purchase Date";
		}
		char temp;
		string fileLocation;
		cout << "Do you want to place input file for " << i << "? (y/n/d) ";
		cin >> temp;
		temp = tolower(temp);
		switch (temp) {
		case 'd':
			fileLocation = "D:\\test.txt";
			cout << fileLocation << endl;
			fileInput(fileLocation);
			break;
		case 'y':
			cout << "File location? ";
			cin >> fileLocation;
			fileInput(fileLocation);
			break;
		default:
			break;
		}

}

// Destructor for libTable.
libTable::~libTable() {}

// Creates a new entry, then calls other methods to insert actual information.
void libTable::newEntry() {
	if (idCount == 0) {
		headEntry = new entry;
		resetPointer();
		entryInsert(idCount);
	} else {
		jumpLastEntry();
		currEntry->next = new entry;
		currEntry->next->prev = currEntry;
		currEntry = currEntry->next;
		entryInsert(idCount);
	}
}

// Method that resets the currentEntry and headEntry pointer, head is defined as the entry where prev = NULL.
void libTable::resetPointer() {
	currEntry = headEntry;
	entry* temp = currEntry;
	while (temp->prev != NULL) {
		temp = temp->prev;
	}
	currEntry = temp;
	headEntry = temp;
}

// Jumps the current pointer to the last entry.
void libTable::jumpLastEntry() {
	resetPointer();
	while (currEntry->next != NULL) {
		currEntry = currEntry->next;
	}
}

// Inputs data from file to struct.
void libTable::fileInput(string path) {
	cout << "Opening file\n";
	file.open(path);
	cout << "File opened\n";
	if (!file) {
		cout << "File does not exist! Exiting program.";
		system("pause");
		exit(1);
	} else {
		headEntry = new entry;
		currEntry = headEntry;
		resetPointer();
		int loop = 0;
		// If not 1st time then search for last entry to add data.
		do {
			if (loop != 0) {
				jumpLastEntry();
				currEntry->next = new entry;
				currEntry->next->prev = currEntry;
				currEntry = currEntry->next;
			} 
			fileInput();
			loop++;
		} while (!file.eof());
	}
	file.close();
	cout << "File closed\n";
	idCount = maxID() + 1;
}

int libTable::maxID() {
	int i = 0;
	resetPointer();
	while (currEntry->next != NULL) {
		if (i < currEntry->id) {
			i = currEntry->id;
		}
		currEntry = currEntry->next;
	}
	return i;
}

// Inputs data from file.
void libTable::fileInput() {
	file >> currEntry->id;
	file >> currEntry->name;
	file >> currEntry->attribName;
	file >> currEntry->year;
	file >> currEntry->month;
	file >> currEntry->day;
	file >> currEntry->hour;
	file >> currEntry->minute;
	file >> currEntry->second;
	currEntry->dateTimeInt = dateTimeFunc(currEntry);
}

// Method that provides an interface to input data.
void libTable::entryInsert(int id) {
	cout << strName << " ? ";
	cin >> currEntry->name;
	cout << strAttribName << " ? ";
	cin >> currEntry->attribName;
	dateTimeInput();
	cout << "Date/Time: ";
	dateTimeOutput();
	cout << endl << endl;
	currEntry->id = id;
	idCount++;
}

// Method that deletes an entry.
void libTable::entryDelete() {
	dataOutput();
	resetPointer();
	int delID;
	cout << "Please select the ID to delete: ";
	cin >> delID;
	while ((currEntry->id != delID) && (currEntry != NULL)) {
		if (currEntry->next == NULL) {
			break;
		}
		currEntry = currEntry->next;
	}
	if (currEntry->id == delID) {
		currEntry->prev->next = currEntry->next;
		currEntry->next->prev = currEntry->prev;
		delete currEntry;
		resetPointer();
		cout << "Entry with ID " << delID << " deleted." << endl;
	} else if (!currEntry->next) {
		cout << "ID not found! Exiting to main menu." << endl;
	}
}

// Method that inputs the date and time to the record.
void libTable::dateTimeInput() {
	time_t rawtime = time(&rawtime);
	struct tm now;
	localtime_s(&now, &rawtime);
	currEntry->year = now.tm_year + 1900;
	currEntry->month = now.tm_mon;
	currEntry->day = now.tm_mday;
	currEntry->hour = now.tm_hour;
	currEntry->minute = now.tm_min;
	currEntry->second = now.tm_sec;
	currEntry->dateTimeInt = dateTimeFunc(currEntry);
}

// Method that converts date and time into an integer, then returns it.
double libTable::dateTimeFunc(entry* ent) {
	double temp = 0;
	temp = 
		(ent->year * 10000000000) + 
		(ent->month * 100000000) +
		(ent->day * 1000000) +
		(ent->hour * 10000) +
		(ent->minute * 100) +
		(ent->second)
		;
	return temp;
}

// Method that outputs the recorded date and time in human readable form.
void libTable::dateTimeOutput() {
	cout << right << currEntry->year << "/" << setfill('0') << setw(2) << currEntry->month << "/" << setfill('0') << setw(2) << currEntry->day << " " << setfill('0') << setw(2) << currEntry->hour << ":" << setfill('0') << setw(2) << currEntry->minute << ":" << setfill('0') << setw(2) << currEntry->second;
	cout << setfill(' ') << left;
}

// Method that lists the attributes with their respective options and names.
void libTable::attribList() {
	cout << "N\t" << strName << endl;
	cout << "I\tID" << endl;
	cout << "D\t" << strDate << endl;
	cout << "B\t" << strAttribName << endl << endl;
	cout << "Any\tGo back to main menu" << endl << endl << endl;
}

// Exports all entries to a file that can be read back later on.
void libTable::exportEntries() {
	string path;
	cout << "Output file? (Enter the filename of type 'd' for default path.)\n";
	cin >> path;
	if (path == "d") {
		path = "D:\\testExport.txt";
	}
	ofstream file;
	file.open(path);
	resetPointer();
	while (currEntry->next != NULL) {
		file << currEntry->id << " ";
		file << currEntry->name << " ";
		file << currEntry->attribName << " ";
		file << currEntry->year << " ";
		file << currEntry->month << " ";
		file << currEntry->day << " ";
		file << currEntry->hour << " ";
		file << currEntry->minute << " ";
		file << currEntry->second << endl;
		currEntry = currEntry->next;
	}
	file.close();
	dataOutput();
	cout << "Export to \"" << path << "\" complete." << endl;
}

// Method that outputs all data in list, with ID.
void libTable::dataOutput() {
	if (headEntry == 0) {
		cout << "No Entries yet." << endl;
	} else {
		resetPointer();
		cout << left << setw(7) << "ID" << setw(40) << strName << setw(40) << strAttribName << "Date(YYYY/MM/DD HH:MM:SS)\n";
		while (currEntry->next != NULL) {
			cout << left << setw(7) << currEntry->id << setw(40) << currEntry->name << setw(40) << currEntry->attribName;
			dateTimeOutput();
			cout << endl;
			currEntry = currEntry->next;
		}
		cout << left << setw(7) << currEntry->id << setw(40) << currEntry->name << setw(40) << currEntry->attribName;
		dateTimeOutput();
		cout << endl;
		currEntry = currEntry->next;
	}
	cout << endl << endl;
	system("pause");
}

// Method that outputs all data in list without ID
void libTable::dataOutput(bool i) {
	if (headEntry == 0) {
		cout << "No Entries yet." << endl;
	} else {
		resetPointer();
		cout << left << setw(20) << strName << setw(20) << strAttribName << "Date(YYYY/MM/DD HH:MM:SS)\n";
		while (currEntry->next != NULL) {
			cout << left <<setw(20) << currEntry->name << setw(20) << currEntry->attribName;
			dateTimeOutput();
			cout << endl;
			currEntry = currEntry->next;
		}
		cout << left << setw(20) << currEntry->name << setw(20) << currEntry->attribName;
		dateTimeOutput();
		cout << endl;
		currEntry = currEntry->next;
	}
}

// Sorts via passed column
void libTable::sort(char i) {
	resetPointer();
	int swapCount = 0, count = 0;
	idCount = maxID() + 1;
	if (idCount != 0) {
		if (i == 'n') {
			do {
				swapCount = 0;
				resetPointer();
				while (currEntry->next != NULL) {
					string str1, str2;
					str1 = currEntry->name;
					str2 = currEntry->next->name;
					if (strcmp(str1.c_str(), str2.c_str()) > 0) {
						entrySwap(currEntry, currEntry->next);
						swapCount++;
						count++;
					} else {
						// cout << "No swap." << endl;
						currEntry = currEntry->next;
					}
				}
			} while (swapCount != 0);
			cout << "List sorted by " << strName << " in " << count << " steps. " << endl;
		} else if (i == 'b') {
			do {
				swapCount = 0;
				resetPointer();
				while (currEntry->next != NULL) {
					string str1, str2;
					str1 = currEntry->attribName;
					str2 = currEntry->next->attribName;
					if (strcmp(str1.c_str(), str2.c_str()) > 0) {
						entrySwap(currEntry, currEntry->next);
						swapCount++;
						count++;
					} else {
						// cout << "No swap." << endl;
						currEntry = currEntry->next;
					}
				}
			} while (swapCount != 0);
			cout << "List sorted by " << strName << " in " << count << " steps. " << endl;
		} else if (i == 'i') {
			do {
				swapCount = 0;
				resetPointer();
				while (currEntry->next != NULL) {
					if (currEntry->id > currEntry->next->id) {
						// cout << "Swapping " << currEntry << " and " << currEntry->next << endl;
						entrySwap(currEntry, currEntry->next);
						swapCount++;
						count++;

					} else {
						// cout << "No swap." << endl;
						currEntry = currEntry->next;

					}
				}

			} while (swapCount != 0);
			cout << "\n\nList sorted by ID in " << count << " steps." << endl;
		} else if (i == 'd') {
			do {
				swapCount = 0;
				resetPointer();
				while (currEntry->next != NULL) {
					if (currEntry->dateTimeInt > currEntry->next->dateTimeInt) {
						// cout << "Swapping " << currEntry << " and " << currEntry->next << endl;
						entrySwap(currEntry, currEntry->next);
						swapCount++;
						count++;

					} else {
						// cout << "No swap." << endl;
						currEntry = currEntry->next;
					}
				}

			} while (swapCount != 0);
			cout << "\n\nList sorted by date & time in " << count << " steps." << endl;
		}
		dataOutput();
	} else {
		cout << "Not enough elements to do sort." << endl;
		system("pause");
	}
}

// Swaps 2 elements in a double linked list.
void libTable::entrySwap(entry* i, entry* j) {
	if (i->prev == NULL) {
		i->prev = j;
		j->prev = NULL;
		i->next = j->next;
		j->next->prev = i;
		j->next = i;

	} else {
		i->prev->next = j;
		j->prev = i->prev;
		i->next = j->next;
		if (i->next != NULL) {
			i->next->prev = i;
		}
		j->next = i;
		i->prev = j;
		
	}
}

//// Find the previous entry for the current entry, then write to prevEntry.
//void libTable::findPrev(entry* now) {
//	entry* temp = now;
//	while (temp->next != now) {
//		temp = temp->next;
//	}
//	prevEntry = temp;
//}


#endif  // !LIB_H