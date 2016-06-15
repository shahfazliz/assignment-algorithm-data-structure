#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

class Student{
	private:
		string fullName;
		string matrixId;
		double cpa;
		int totalCreditsTaken;
		string appointmentDate;
		string problem;
	
	public:
		Student(string fullName, string matrixId, double cpa, int totalCreditsTaken, string appointmentDate, string problem) {
			this -> fullName = fullName;
			this -> matrixId = matrixId;
			this -> cpa = cpa;
			this -> totalCreditsTaken = totalCreditsTaken;
			this -> appointmentDate = appointmentDate;
			this -> problem = problem;
		}
		
		string get(string columnName) {
			if (columnName == "Full Name") return fullName;
			
			if (columnName == "Matrix ID") return matrixId;
			
			if (columnName == "CPA") {
				stringstream temp;
				temp << cpa;
				return temp.str();
			}
			
			if (columnName == "Credits") {
				stringstream temp;
				temp << totalCreditsTaken;
				return temp.str();
			}
			
			if (columnName == "Appointment") return appointmentDate;
			
			else return "";
		}
		
		void updateFullName() {
			cout << "Full Name (" << fullName << ")?: ";
			string temp;
			getline(cin, temp);
			if (temp != "") fullName = temp;
		}
		
		void updateMatrixId() {
			cout << "Matrix ID (" << matrixId << ")?: ";
			string temp;
			getline(cin, temp);
			if (temp != "") matrixId = temp;
		}
		
		void updateCPA() {
			cout << "CPA (" << cpa << ")?: ";
			string temp;
			getline(cin, temp);
			if (temp != "") cpa = atof(temp.c_str());
		}
		
		void updateTotalCredisTaken() {
			cout << "Total credits taken (" << totalCreditsTaken << ")?: ";
			string temp;
			getline(cin, temp);
			if (temp != "") totalCreditsTaken = atoi(temp.c_str());
		}
		
		void updateAppoitmentDate() {
			cout << "Appointment Date (" << appointmentDate << ")?: ";
			string temp;
			getline(cin, temp);
			if (temp != "") appointmentDate = temp;
		}
		
		void updateProblem() {
			cout << "Problem (" << problem << ")?: ";
			string temp;
			getline(cin, temp);
			if (temp != "") problem = temp;
		}
		
		void updateAll() {
			updateFullName();
			updateMatrixId();
			updateCPA();
			updateTotalCredisTaken();
			updateAppoitmentDate();
			updateProblem();
		}
		
		void print() {
			cout << setw(25) << "Full name : " << fullName << endl;
			cout << setw(25) << "Matrix ID : " << matrixId << endl;
			cout << setw(25) << "CPA : " << cpa << endl;
			cout << setw(25) << "Total credits taken : " << totalCreditsTaken << endl;
			cout << setw(25) << "Appointment date : " << appointmentDate << endl;
			cout << setw(25) << "Problem : " << problem << endl;
		}
		
		void printLine() {
			cout << setw(20) << fullName 
				 << setw(20) << matrixId 
				 << setw(5) << cpa 
				 << setw(8) << totalCreditsTaken 
				 << setw(12) << appointmentDate << endl;
		}
		
		string writeLine() {
			
			ostringstream oss;
			oss << fullName << "\t"
				<< matrixId << "\t"
				<< cpa << "\t"
				<< totalCreditsTaken << "\t"
				<< appointmentDate << "\t"
				<< problem;
			return oss.str();
		}
};

class Node{
	public:
		Node *next;
		Node *prev;
		Student *student;
		
		Node(Student *student) {
			this -> student = student;
			next = NULL;
			prev = NULL;
		}
};

class Queue{
	public:
		Node *front;
		Node *back;
		
		int size;
		
		Queue() {
			createQueue();
		}
		
		void createQueue() {
			front = NULL;
			back = NULL;
			size = 0;
		}
		
		void destroyQueue() {
			Node *temp = front;
			while (temp) {
				front = temp -> next;
				delete temp;
				temp = front;
			}
		}
		
		bool isEmpty() {
			return front == NULL && back == NULL;
		}
		
		void enQueue(Node *node) {
			if (isEmpty()){
				front = node;
				back = node;
			} else {
				node -> prev = back;
				back -> next = node;
				back = node;
			}
			size += 1;
		}
		
		void deQueue() {
			if (!isEmpty()) {
				Node *temp = back;
				back = back -> prev;
				back -> next = NULL;
				delete temp;
			}
			size -= 1;
		}
		
		Node *getFront() {
			return front;
		}
		
		Node *getRear() {
			return back;
		}
		
		// Simple bubble sort in ascending
		void sortAsc(string columnName) {
			if (!isEmpty()) {
				
				for (int pass = 1; pass < size; pass += 1) {
					Node *node = front;
					
					for (int x = 0; x < size - pass; x += 1) {
			
						// Compare
						Node *first = node;
						Node *second = node -> next;
						if (first -> student -> get(columnName) > second -> student -> get(columnName)) {
							// swap student
							Student *temp = first -> student;
							first -> student = second -> student;
							second -> student = temp;
						}
						
						node = node -> next;
					}
				}
			}
		}
};

class StudentFile{
	public:
		// Read from File
		static Queue *read(string filename) {
			string line;
			ifstream studentFile (filename.c_str());
			Queue *list = new Queue();
			
			if (studentFile.is_open()) {
			 	while (getline(studentFile, line)) {
					
					stringstream linestream(line);
					string fullName;
					string matrixId;
					string cpa;
					string totalCreditsTaken;
					string appointmentDate;
					string problem;
					string token;
					
					getline(linestream, fullName, '\t');
					getline(linestream, matrixId, '\t');
					getline(linestream, cpa, '\t');
					getline(linestream, totalCreditsTaken, '\t');
					getline(linestream, appointmentDate, '\t');
					getline(linestream, problem, '\t');
					
					list -> enQueue(new Node(new Student(fullName, matrixId, atoi(cpa.c_str()), atof(totalCreditsTaken.c_str()), appointmentDate, problem)));
				}
				studentFile.close();
			}

  			else cout << "Error: Unable to open file"; 
			return list;
		}
		
		// Write into File
		static void write(string filename, Queue *list) {
			ofstream studentFile;
			studentFile.open(filename.c_str());
			
			Node *node = list -> front;
			while (node != NULL) {
				studentFile << node -> student -> writeLine();
				node = node -> next;
				if (node != NULL) studentFile << "\n";
			}
			
			studentFile.close();
		}
};

// For display purpose, a horizontal line
void horizontalLine() {
	for(int i = 0; i < 68; i += 1) cout << "-";
	cout << endl;
}

// For display purpose, Main Menu
string *mainMenu() {
	horizontalLine();
	cout << "Please enter command: " << endl
		 << "   1. sortby < comumn header name >" << endl
		 << "   3. select < number in list >" << endl
		 << "   4. exit" << endl;
	horizontalLine();
	cout << "> ";
	
	// Loop until user input the right command
	while (true) {
		// Get user input
		string inputLine;
		getline(cin, inputLine);
		
		// Parse/Split string by delimiter ' '
		// and save the first parameter into parameters[0]
		// as command
		stringstream linestream(inputLine);
		string *parameters = new string[10];
		getline(linestream, *parameters, ' ');
		
		// Get the rest of parameters
		int i = 0;
		while (linestream) {
			i += 1;
			linestream >> *(parameters + i);
		}
		
		// Return pointer to array if correct command is given
		if(*parameters == "sortby" || *parameters == "select" || *parameters == "exit") {
			return parameters;
		}
		else {
			cout << "> Invalid command. Please try again." << endl;
			cout << "> ";
		}
	}
}

// For display purpose, Student Menu
string studentMenu() {
	horizontalLine();
	cout << "Please enter command: " << endl
		 << "   1. update" << endl
		 << "   2. main" << endl
		 << "   3. exit" << endl;
	horizontalLine();
	cout << "> ";
	
	// Loop until user input the right command
	while (true) {
		// Get user input
		string command;
		getline(cin, command);
		
		// Return command string if correct command is given
		if(command == "update" || command == "main" || command == "exit") {
			return command;
		}
		else {
			cout << "> Invalid command. Please try again." << endl;
			cout << "> ";
		}
	}
}

// Program main entry
int main(){
	
	// Load Student data from Data File
	// and Populate Linked List
	Queue *list = StudentFile::read("student.txt");
	
	
	// Loop this application until user enter command exit
	bool exit = false;
	while(!exit){
		// Clear screen
		system("cls");
		
		// Display Linked List
		cout << endl
			 << setw(3) << "#"
			 << setw(20) << "Full Name" 
			 << setw(20) << "Matrix ID" 
			 << setw(5) << "CPA" 
			 << setw(8) << "Credits" 
			 << setw(12) << "Appointment" << endl;
		horizontalLine();
		
		int listNumber = 0;
		Node *node = list -> front;
		while(node != NULL){
			listNumber += 1;
			cout << setw(3) << listNumber;
			node -> student -> printLine();
			node = node -> next;
		}
		cout << endl;
		
		// Display Menu Options
		// and Get user input
		string *parameters = mainMenu();
		
		// Sort Linked List
		if (*parameters == "sortby") {
			
			// Rebuild column name
			string columnName;
			for (int i = 1; i < 10; i +=1) {
				string temp = *(parameters + i);
				if (temp[0] != '\0') {
					if (columnName[0] != '\0') columnName += " ";
					columnName += temp;
				} else {
					break;
				}
			}
			
			// Rebuild linked list sorted by given column name
			list -> sortAsc(columnName);
		}
		
		// Display selected Student
		// and Generate printable version
		if (*parameters == "select") {
			
			// Loop this display until main command or exit is entered
			while (true) {
				
				// The parameter to select should be a number
				string temp = *(parameters + 1);
				int selection = atoi(temp.c_str());
				
				// Display student at number			
				if (selection > 0 && selection <= list -> size) {
					Node *selectNode = list -> front;
					for (int i = 1; i < selection; i++) {
						selectNode = selectNode -> next;
					}
					
					// Clear screen and print Student
					system("cls");
					cout << endl
						 << "  Student" << endl;
					horizontalLine();
					selectNode -> student -> print();
					cout << endl;
					
					// Get user input
					string studentCommand = studentMenu();
					
					if (studentCommand == "update") {
						// Update Student
						// Save Student if there is changes
						// Discard update Student if there no changes
						selectNode -> student -> updateAll();
						
						// Save new Linked List into Data File
						StudentFile::write("student.txt", list);
					}
					
					if (studentCommand == "main") break;
					
					if (studentCommand == "exit") {
						cout << "  Exiting..." << endl;
						exit = true;
						break;
					}
				}
			}
		}
		
		// Exit application
		if (*parameters == "exit") {
			cout << "  Exiting..." << endl;
			exit = true;
		}
	}
}
