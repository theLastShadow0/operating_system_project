#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

struct Student {

	int id;
	int result; 

};

double percentage(int size, Student array[]) {

	double passed = 0;
	//keeps track on how many students passed.

	for (int i = 0; i < size; i++) { 
		if (array[i].result == 1) {
			passed++;
		}
	}
	//In this for loop it checks the result array
	//If its equal to one the passed variable is increased

	return ((passed / size) * 100);

}

int main() {

	int const size = 6; 
	//number of students

	Student arr[size];

	string myText;

	ifstream MyReadFile("filename.txt");

	if (!MyReadFile.is_open()) {

		cout << "ERROR FILE DID NOT OPEN" << endl;

	}
	else {

		int i = 0;

		while (!MyReadFile.eof()) {
			getline(MyReadFile, myText, ' ');
			//cout << myText << endl;
			//This will read the file until it detects a space.
			//In this case it is getting the student ID.
			stringstream(myText) >> arr[i].id; 
			//stores the text into the array.

			getline(MyReadFile, myText, '\n');
			//cout << myText << endl;
			//Continues to read the file after the space
			//which will get the result of pass or fail.
			stringstream(myText) >> arr[i].result; 
			//stores the result into the array

			i++;
		}

		for (int i = 0; i < size; i++) {
			cout << arr[i].id << " " << arr[i].result << endl;
		}
		
		double per = percentage(size, arr);

		cout << "Percentage of students who passed: " << setprecision(3) << per << "%" << endl; 
		
	}

	MyReadFile.close();

}
