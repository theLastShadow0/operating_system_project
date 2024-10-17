#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <iomanip>
#include <pthread.h> 


using namespace std;

ifstream MyReadFile("filename.txt");


struct Student {

	int id;
	int result; 

};

double percentage(int size, Student array[]) {

	double passed = 0;

	for (int i = 0; i < size; i++) { 
		if (array[i].result == 1) {
			passed++;
		}
	}

	return ((passed / size) * 100);

}

void *func(void * arg){
    
    int const size = 6;

	Student arr[size];

	string myText;


	if (!MyReadFile.is_open()) {

		cout << "ERROR FILE DID NOT OPEN" << endl;

	}
	else {

		int i = 0;

		while (!MyReadFile.eof()) {
			getline(MyReadFile, myText, ' ');
			//cout << myText << endl; 

			stringstream(myText) >> arr[i].id; 

			getline(MyReadFile, myText, '\n');
			//cout << myText << endl;

			stringstream(myText) >> arr[i].result; 

			i++;
		}

		for (int i = 0; i < size; i++) {
			cout << arr[i].id << " " << arr[i].result << endl;
		}
		
		double per = percentage(size, arr);

		cout << "Percentage of students who passed: " << setprecision(3) << per << "%" << endl; 
		
	}
	
	pthread_exit(NULL);
}

int main() {

	pthread_t ptid;
	
	pthread_create(&ptid, NULL, &func, NULL);
	
	pthread_join(ptid, NULL);
	
	pthread_exit(NULL);

	MyReadFile.close();

}
