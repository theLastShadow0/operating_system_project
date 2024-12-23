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
//Returns a pointer of void type.
//It prevents retrictions for the function.
//Returns the results of the threads execution.
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
	//terminates the thread
}

int main() {

	pthread_t ptid;
	//stores the id of the thread
	
	pthread_create(&ptid, NULL, &func, NULL);
	//creates a new thread
	//&ptid points to the pthread_t variable where the new thread will be stored.
	
	pthread_join(ptid, NULL);
	//waits for the thread to finish executing
	
	pthread_exit(NULL);

	MyReadFile.close();

}
