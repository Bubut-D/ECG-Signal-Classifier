#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

// Every aspect of this code was dicussed in meetings between the members of the group,
// the general idea of the code was a collective effort.

// The code was gathered into a single source file, managed and polished by Bulut DEMİR.

int _patientCount = 0;// To keep count of patients.
// The "Pulse" class was written by Alperen Melih GÖNCÜ.

// The "Pulse" class is used to keep the information of the pulses
// in an ECG signal and to use as nodes of a singly linked list.
class Pulse {
public:
	Pulse* next = nullptr;
	float Rpeak;
	float Pstart;
	float Tfinish;
	Pulse(float Rpeak, float Pstart, float Tfinish) {
		this->Rpeak = Rpeak;
		this->Pstart = Pstart;
		this->Tfinish = Tfinish;
	}
};

// The "Signal" class except for the member function analyse() was written by Alperen Melih GÖNCÜ.

// The "Signal" class is a singly linked list data structure 
// that is used to manage a single patient's ECG signal.
class Signal {
private:
	Pulse* head = nullptr;
	ofstream fileT;
	ofstream fileN;
	ofstream fileB;
public:
	Signal(const Signal& other) {}
	//Every time a new patient is recorded the patientCount variable is increased via the constructor.
	Signal() {
		_patientCount++;
	}
	// isEmpty() member function is used to check if the list is empty.
	bool isEmpty() {
		return head == nullptr;
	}
	// pushBack() member function is used to add a new pulse to the linked list.
	void pushBack(float Rpeak, float Pstart, float Tfinish) {
		Pulse* newNode = new Pulse(Rpeak, Pstart, Tfinish);
		Pulse* temp = head;
		if (isEmpty()) {
			head = newNode;
		}
		else {
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newNode;
			newNode->next = nullptr;
		}
	}

	// analyse() member function was written by Mehmet DÜNDAR.

	// analyse() member function is used to classify the pulses in an ECG signal.
	void analyse() {
		Pulse* temp = head;
		float bpm, pulseTime;
		int check = -1;// to check what file was written into last.

		// The following three lines of code open the record files of the new patient for writing.
		fileT.open("Person-" + to_string(_patientCount) + "-Tachycardia.txt", ios::out);
		fileB.open("Person-" + to_string(_patientCount) + "-Bradycardia.txt", ios::out);
		fileN.open("Person-" + to_string(_patientCount) + "-Normal.txt", ios::out);

		// If any of the files couldn't be opened an exception is thrown.
		if (!fileT.is_open() || !fileB.is_open() || !fileN.is_open())
			throw exception("Couldn't open files.");

		// In the while loop the time difference between the current pulse and the next one is 
		// being calculated, the difference is being used to calculate the BPM of the pulses 
		// which is used to check if the pulse belongs to the tachycardia, bradycardia or 
		// normal file of the patient then the pulse gets written into the appropriate file  
		// and at the end of the loop the current pulse is switched to the next pulse.
		while (temp->next != nullptr) {
			pulseTime = (temp->next->Rpeak) - (temp->Rpeak);
			bpm = 60 / pulseTime;
			if (bpm > 100) {
				fileT << temp->Pstart << " " << temp->Rpeak << " " << temp->Tfinish << endl;
				check = 0;
			}
			else if (bpm >= 60) {
				fileN << temp->Pstart << " " << temp->Rpeak << " " << temp->Tfinish << endl;
				check = 1;
			}
			else {
				fileB << temp->Pstart << " " << temp->Rpeak << " " << temp->Tfinish << endl;
				check = 2;
			}
			temp = temp->next;
		}

		// In the previous loop the last pulse can't be classified because there isn't a pulse that comes 
		// after to calculate the BPM with. So in order to write the last pulse into the file that was
		// written into last we use the check variable.
		switch (check) {
		case 0:
			fileT << temp->Pstart << " " << temp->Rpeak << " " << temp->Tfinish << endl;
			break;
		case 1:
			fileN << temp->Pstart << " " << temp->Rpeak << " " << temp->Tfinish << endl;
			break;
		case 2:
			fileB << temp->Pstart << " " << temp->Rpeak << " " << temp->Tfinish << endl;
			break;
		}
		fileT.close();
		fileB.close();
		fileN.close();
	}
	void erase() {
		Pulse* temp;
		while (head)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
	~Signal() {
		erase();
	}
};

// genNumStr() function was written by Bulut DEMİR.

// genNumStr() function is used to generate a string of numbers up to the number of patients seperated by hyphens.
string genNumStr() {
	stringstream ss;
	string str;
	for (size_t k = 1; k <= _patientCount; k++)
	{
		ss << "-" << k;
	}
	getline(ss, str);
	return str;
}

// groupFiles() function was written by Bulut DEMİR, Umut Boray DEMİR and Zeynep Sude İMDAT.

// groupFiles() function is used to group the same ECG signals belonging to
// different people into three seperate files consisting of bradycardia, normal
// and tachycardia signals by reading the files that were divided in the previous stage.
void groupFiles() {

	string typeNames[] = { "Normal", "Tachycardia", "Bradycardia" };
	string pulse;

	for (size_t i = 0; i <= 2; i++) {

		// The name of the combined file is generated by appending the appropriate strings.
		ofstream combined(typeNames[i] + "-Person" + genNumStr() + ".txt", ios::out);
		for (size_t j = 1; j <= _patientCount; j++)
		{
			ifstream file;
			// The name of the file to be read is generated by appending the appropriate strings.
			file.open("Person-" + to_string(j) + "-" + typeNames[i] + ".txt", ios::in);

			while (getline(file, pulse)) {
				combined << pulse << endl;
			}
			combined << "*************************" << endl;
		}
		combined.close();
	}

}

// The main() function was written by Alperen Melih GÖNCÜ with additions from Bulut DEMİR.

int main() {
	string str;
	float arr[3];
	string input;
	vector<Signal> signals;

	cout << "Enter File Names Seperated By Spaces (Example: file1.csv files2.csv ... fileN.csv)" << endl;
	cout << "(After entering the file names and making sure the program does not encounter any errors enter 0 to end the program.)" << endl;
	cin >> input;

	while (input != "0")
	{
		ifstream file(input);
		if (!file.is_open())
		{
			cout << "ERROR : The file " << input << " does not exist!!!" << endl;
			cout << "Please enter the name of the file " << input << " again correctly: " << endl;
			cin >> input;
			continue;
		}
		getline(file, str); // This line is to get rid of the top row in the .csv file which contains the column names.

		Signal pulse;
		signals.push_back(pulse); // The code records the signal into the vector.

		// At the start of each while loop a row from the opened file gets recorded into the str variable.
		while (getline(file, str))
		{
			// This for loop gets rid of the commas or semicolons in the .csv file. The reason as 
			// to why we aren't only looking for commas is because depending on the type of .csv 
			// file the seperation of collumns in a row can be done with either commas or semicolons.
			for (int i = 0; i != str.length(); i++)
			{
				if (str[i] == ';')
				{
					str[i] = ' ';
				}
				else if (str[i] == ',')
				{
					str[i] = ' ';
				}
			}

			stringstream ss(str); // The edited row of information gets inserted into the string stream.

			// In this for loop the values in the string stream gets inserted into an array one by one.
			for (int i = 0; i < 3; i++)
				ss >> arr[i];

			signals[_patientCount - 1].pushBack(arr[1], arr[0], arr[2]); // The values get inserted into a linked list node which is inserted from the back into a linked list.
		}
		signals[_patientCount - 1].analyse(); // The ECG signal of the current patient gets analysed.
		cin >> input;
	}

	groupFiles(); // The divided files get grouped.
	cout << "The program succesfully ended.";
	return 0;
}
