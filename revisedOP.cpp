#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <iomanip>
#include <pthread.h> 
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdlib.h>


using namespace std;

//ifstream MyReadFile("filename.txt");

ifstream inProfile("users.txt");
ofstream outProfile("users.txt", ios::app);

/*
struct Process {

    string name;
	int id;
	string state; 

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
*/
void createUser();
bool Login();

bool Welcome(){
    
    int choice;
    bool logged;

    
    cout << "-------------------------------------------" << endl;
    cout << "-***********Welcome to TAMIU OS***********-" << endl;
    cout << "-------------------------------------------" << endl << endl;
    
    cout << "Would you like to login (0) or add user(1)?" << endl;
    
    cin >> choice;
    
    if(!choice){
        
        logged = Login();
        
    }
    else{
        
        createUser();
        
    }
    
    return logged;
    
}

bool Login(){
    
    string userUsername;
    string userPassword;
    string usr;
    string psd;
    bool found;
    int choice;
    
    bool logged;
    
    cout << "Enter username: ";
    cin >> userUsername;

    //The username should not be case-sensitive and this prevents that
    transform(userUsername.begin(), userUsername.end(), userUsername.begin(), [](unsigned char c){
        return tolower(c);
    });
    
    //The password should be case-sensitive and will remain as-is.
    cout << "Enter password: ";
    cin >> userPassword;
    
    while(!inProfile.eof()){
        
        getline(inProfile, usr, ' ');
        
        //The username should not be case-sensitive and this prevents that
        transform(usr.begin(), usr.end(), usr.begin(), [](unsigned char c){
            return tolower(c);
        });
        
        getline(inProfile, psd, '\n');
        
        if((userUsername == usr) && (userPassword == psd)){
            
            found = true;
            
        }
        
    }
    
    //resets eof command
    inProfile.clear();
    inProfile.seekg(0, ios::beg);
    
    if(!found){
        //system("cls");
        cout << "Username or Password incorrect, please try again (0) or create new user (1)." << endl;
        cin >> choice;
        
        if(!choice){
            
            return Login();
            
        }
        else{
            createUser();
        }
    }
    else {
        
        logged = found;
        return logged;
        
    }
    
}


void createUser(){
    
    string userUsername;
    string userPassword;
    string usr;
    string psd;
    bool found = false;
    int choice;
    
    cout << "Enter username (No spaces please): ";
    cin >> userUsername;

    //The username should not be case-sensitive and this prevents that
    transform(userUsername.begin(), userUsername.end(), userUsername.begin(), [](unsigned char c){
        return tolower(c);
    });
    
    
    //The password should be case-sensitive and will remain as-is.
    cout << "Enter password: ";
    cin >> userPassword;
    
    //check if user exists
    while(!inProfile.eof()){
        
        getline(inProfile, usr, ' ');
        
        //The username should not be case-sensitive and this prevents that
        transform(usr.begin(), usr.end(), usr.begin(), [](unsigned char c){
            return tolower(c);
        });
        
        getline(inProfile, psd, '\n');
        
        if((userUsername == usr) && (userPassword == psd)){
            
            found = true;
            
        }
        
    }
    
    //resets eof command
    inProfile.clear();
    inProfile.seekg(0, ios::beg);
    
    if(!found){
        
        if(outProfile.is_open()){
        
        outProfile << endl;
        outProfile << userUsername << " ";
        outProfile << userPassword;
        
        cout << "User has been added." << endl;
        cout << "Shutting down to save user. Bye bye!" <<endl;
        exit(0);
        
        }
        else{
            cout << "ERROR: Some error has occured and could not add user." << endl;
        }
    }
    else if(found){
        
        cout << "User already exists. Try another (0) or login (1)?" << endl;
        cin >> choice;
        
        if(!choice) {
            createUser();
        }
        else{
            Login();
        }
        
    }
    
    
    
}

int main() {
    
    bool logged;
    
    logged = Welcome();
    
    /*if(logged){
        
        
        
    }*/
    
    
    /*
    
	pthread_t ptid;
	//stores the id of the thread
	
	pthread_create(&ptid, NULL, &func, NULL);
	//creates a new thread
	//&ptid points to the pthread_t variable where the new thread will be stored.
	
	pthread_join(ptid, NULL);
	//waits for the thread to finish executing
	
	pthread_exit(NULL);
	
    */
	//MyReadFile.close();
    inProfile.close();
    outProfile.close();
}

