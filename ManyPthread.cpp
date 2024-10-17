#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <iomanip>
#include <pthread.h> 


using namespace std;

//opening .txt file
ifstream MyReadFile("filename.txt");

//struct for students
struct Student {

	int id;
	int result; 

};

//Global variables
int i = 0;

int const size = 6;

Student arr[size];

double passed = 0;



//counts the amount of people passed
void Passed(Student array[]) {

	if (array[i].result == 1) {
		passed++;
	}

}



void *func(void * arg){
    


    
    string myText;
    
    while(!MyReadFile.eof()){
    	getline(MyReadFile, myText, ' ');
    	//cout << myText << endl; 
    
    	stringstream(myText) >> arr[i].id; 
    
    	getline(MyReadFile, myText, '\n');
    	//cout << myText << endl;
    
    	stringstream(myText) >> arr[i].result; 
    
        Passed(arr);
        
    	i++;
    }

	pthread_exit(NULL);
}

void *perc(void * arg){
    
    double percent = ((passed / size) * 100);
    cout << "Percentage of students who passed: " << setprecision(3) << percent << "%" << endl;
    
    pthread_exit(NULL);
}

void *read(void * arg){
    
	for (int i = 0; i < size; i++) {
	    cout << arr[i].id << " " << arr[i].result << endl;
	}    
    
    pthread_exit(NULL);
}

int main() {

	pthread_t ptid;
	pthread_t percentage;
	pthread_t list;
	
	pthread_create(&ptid, NULL, &func, NULL);
	pthread_join(ptid, NULL);
	
	pthread_create(&percentage, NULL, &perc, NULL);
	pthread_join(percentage, NULL);
	
    pthread_create(&list, NULL, &read, NULL);
    pthread_join(list, NULL);
	

	
	
	
	pthread_exit(NULL);

	MyReadFile.close();

}
