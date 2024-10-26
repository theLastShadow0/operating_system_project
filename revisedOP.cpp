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
#include <random>


using namespace std;

//ifstream MyReadFile("filename.txt");

ifstream inProfile("users.txt");
ofstream outProfile("users.txt", ios::app);

random_device rd;


//implement with making process (loop) to make sure all random numbers do not repeat.
mt19937 gen(rd());

uniform_int_distribution<> distr1(1000,9999);

uniform_int_distribution<> distr2(1,10);

//int random_number = distr1(gen);



struct Process {

	string name;
	int id;
	string state;
	int cpuBurst;

};

/*
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
void Login();
void menu();

bool logged;
string userUsername;
string userPassword;
string usr;
string psd;

void Welcome() {

	int choice;

	cout << "-------------------------------------------" << endl;
	cout << "-***********Welcome to TAMIU OS***********-" << endl;
	cout << "-------------------------------------------" << endl << endl;

	cout << "Press '1' to login to an existing account" << endl;
	cout << "Press '2' to create a new account" << endl;
	cout << "Press '0' to turn shut down" << endl;

	cin >> choice;


	switch(choice) {

	case 0:
		cout << "Shutting down..." << endl;
		exit(0);

	case 1:
		Login();
		break;

	case 2:
		createUser();
		break;

	}


}

void Login() {

	bool found;
	int choice;

	cout << "Enter username: ";
	cin >> userUsername;

	//The username should not be case-sensitive and this prevents that
	transform(userUsername.begin(), userUsername.end(), userUsername.begin(), [](unsigned char c) {
		return tolower(c);
	});

	//The password should be case-sensitive and will remain as-is.
	cout << "Enter password: ";
	cin >> userPassword;

	while(!inProfile.eof()) {

		getline(inProfile, usr, ' ');

		//The username should not be case-sensitive and this prevents that
		transform(usr.begin(), usr.end(), usr.begin(), [](unsigned char c) {
			return tolower(c);
		});

		getline(inProfile, psd, '\n');

		if((userUsername == usr) && (userPassword == psd)) {

			found = true;

		}

	}

	//resets eof command
	inProfile.clear();
	inProfile.seekg(0, ios::beg);

	if(!found) {
		//system("cls");
		cout << "Username or Password incorrect, please try again (0) or create new user (1)." << endl;
		cin >> choice;

		if(!choice) {

			Login();

		}
		else {
			createUser();
		}
	}
	else {

		logged = found;
		menu();

	}

}


void createUser() {


	bool found = false;
	int choice;

	cout << "Enter username (No spaces please): ";
	cin >> userUsername;

	//The username should not be case-sensitive and this prevents that
	transform(userUsername.begin(), userUsername.end(), userUsername.begin(), [](unsigned char c) {
		return tolower(c);
	});


	//The password should be case-sensitive and will remain as-is.
	cout << "Enter password: ";
	cin >> userPassword;

	//check if user exists
	while(!inProfile.eof()) {

		getline(inProfile, usr, ' ');

		//The username should not be case-sensitive and this prevents that
		transform(usr.begin(), usr.end(), usr.begin(), [](unsigned char c) {
			return tolower(c);
		});

		getline(inProfile, psd, '\n');

		if((userUsername == usr) && (userPassword == psd)) {

			found = true;

		}

	}

	//resets eof command
	inProfile.clear();
	inProfile.seekg(0, ios::beg);

	if(!found) {

		if(outProfile.is_open()) {

			outProfile << endl;
			outProfile << userUsername << " ";
			outProfile << userPassword;

			cout << "User has been added." << endl;
			cout << "Shutting down to save user. Bye bye!" <<endl;
			exit(0);

		}
		else {
			cout << "ERROR: Some error has occured and could not add user." << endl;
		}
	}
	else if(found) {

		cout << "User already exists. Try another (0) or Login (1)?" << endl;
		cin >> choice;

		if(!choice) {
			createUser();
		}
		else {
			Login();
		}

	}



}

void menu() {

    //exist is set to 0 for if statements to check if they are "running",
    //but by doing so can't add more than one of the same process

	cout << "Welcome " << userUsername << endl;


    int counter = 0;

    int index = 0;
    
    //int randnumber;

    Process Google;
    //google.exists = 0;

    Process Word;
    //word.exists = 0;

    Process File;
    //file.exists = 0;

    Process PowerPoint;
    //powerpoint.exists = 0;

    //character used to prompt the user for if they want to terminate a process
    int choice;

    int menuChoice;
    vector<Process> vec; //vector to store the processes opened. Used because it is easier to remove elements

    do {
        
        bool found = false;

        
        cout << "Please choose a program to execute on your OS: " << endl;
        cout << " Press '1' to run Google Chrome" << endl;
        cout << " Press '2' to run Microsoft Word" << endl;
        cout << " Press '3' to run File Explorer" << endl;
        cout << " Press '4' to run Microsoft PowerPoint" << endl;
        cout << " Press '5' to see tasks running" << endl; // NEW
        cout << " Press '0' to sign out " << endl;
        cin >> menuChoice;

        //system("cls"); //clears terminal

        switch (menuChoice) {

        case 0:
            cout << "Signing out...\n" << endl;
            return Welcome();


        case 1:

            if (vec.size() == 0) {

                Google.name = "Google";

                Google.id = distr1(gen);
                
                cout <<"Google's Process ID is: "<< Google.id << endl;

                Google.state = "running";

                Google.cpuBurst = distr2(gen);
                
                cout <<"Process burst time: " << Google.cpuBurst <<" cycle/s"<< endl;

                vec.push_back(Google);

            }
            else{
                
                for (int j = 0; j < vec.size(); j++) {

                    if(vec[j].name == "Google"){
                        
                        found = true;
                
                    }

                }
                
                if(found){
                    cout << "Google already exists, \n";
                    cout << "would you like to replace (0) \n";
                    cout << "Do nothing (1) \n";
                    cout << "Or terminate Process (2) \n";
                    
                    cin >> choice;
                    
                    switch(choice){
                        
                        case 0:
                        
                        for (int i = 0; i < vec.size(); i++) {
                            if (vec[i].name == "Google") {
                                //used to iterate and set the index of the number wanted to be found
                                //then .erase() to erase the element
                                //without this and typing vec.erase(i) causes overloading problem/bug
                                vector<Process>::iterator it = vec.begin(); 
                                advance(it, i);
                                vec.erase(it);
                            }
                        }   
                        
                        Google.id = distr1(gen);
                        
                        Google.state = "ready";
        
                        Google.cpuBurst = distr2(gen);
                        
                        vec.push_back(Google);
                        
                        break;
                            
                        case 1:
                        break;
                        
                        case 2:
                        
                        for (int i = 0; i < vec.size(); i++) {
                                if (vec[i].name == "Google") {
                                    //used to iterate and set the index of the number wanted to be found
                                    //then .erase() to erase the element
                                    //without this and typing vec.erase(i) causes overloading problem/bug
                                    vector<Process>::iterator it = vec.begin(); 
                                    advance(it, i);
                                    vec.erase(it);
                                }
                            }   
                        break;
                        
                    }
                }
                else{
                    
                    Google.name = "Google";

                    Google.id = distr1(gen);

                    cout <<"Google's Process ID is: "<< Google.id << endl;
                    
                    Google.state = "ready";
    
                    Google.cpuBurst = distr2(gen);

                    cout <<"Process burst time: " << Google.cpuBurst <<" cycle/s"<< endl;
                    
                    vec.push_back(Google);
                    
                }
                
            }
            
            

            break;
        case 2:
        
        
            if (vec.size() == 0) {

                Word.name = "Microsoft Word";

                Word.id = distr1(gen);

                cout <<"Word's Process ID is: "<< Word.id << endl;

                Word.state = "running";

                Word.cpuBurst = distr2(gen);

                cout <<"Process burst time: " << Word.cpuBurst <<" cycle/s"<< endl;

                vec.push_back(Word);

            }
            else{
                
                for (int j = 0; j < vec.size(); j++) {

                    if(vec[j].name == "Microsoft Word"){
                        
                        found = true;
                        
                    }
                    
                }
                
                if(found){
                    
                        cout << "Microsoft Word already exists, \n";
                        cout << "would you like to replace (0) \n";
                        cout << "Do nothing (1) \n";
                        cout << "Or terminate Process (2) \n";
                        
                        cin >> choice;
                        
                        switch(choice){
                            
                            case 0:
                            
                            for (int i = 0; i < vec.size(); i++) {
                                if (vec[i].name == "Microsoft Word") {
                                    //used to iterate and set the index of the number wanted to be found
                                    //then .erase() to erase the element
                                    //without this and typing vec.erase(i) causes overloading problem/bug
                                    vector<Process>::iterator it = vec.begin(); 
                                    advance(it, i);
                                    vec.erase(it);
                                }
                            }   
                            
                            Word.id = distr1(gen);
                
                            Word.state = "ready";
            
                            Word.cpuBurst = distr2(gen);
                            
                            vec.push_back(Word);
                            
                            break;
                                
                            case 1:
                            break;
                            
                            case 2:
                            
                            for (int i = 0; i < vec.size(); i++) {
                                    if (vec[i].name == "Microsoft Word") {
                                        //used to iterate and set the index of the number wanted to be found
                                        //then .erase() to erase the element
                                        //without this and typing vec.erase(i) causes overloading problem/bug
                                        vector<Process>::iterator it = vec.begin(); 
                                        advance(it, i);
                                        vec.erase(it);
                                    }
                                }   
                            break;
                            
                        }
                    }
                    else{
                        
                        Word.name = "Microsoft Word";
                        
                        Word.id = distr1(gen);

                        cout <<"Word's Process ID is: "<< Word.id << endl;
                
                        Word.state = "ready";
        
                        Word.cpuBurst = distr2(gen);

                        cout <<"Process burst time: " << Word.cpuBurst <<" cycle/s"<< endl;
                        
                        vec.push_back(Word);
                    }
                
            }

            break;
        case 3:
        

            if (vec.size() == 0) {

                File.name = "File Explorer";

                File.id = distr1(gen);

                cout <<"File Explorer's Process ID is: "<< File.id << endl;

                File.state = "running";

                File.cpuBurst = distr2(gen);

                cout <<"Process burst time: " << File.cpuBurst <<" cycle/s"<< endl;

                vec.push_back(File);


            }
            else{
                
                for (int j = 0; j < vec.size(); j++) {

                    if(vec[j].name == "File Explorer"){
                        
                        found = true;
                        
                    }
                    

                }
                
                if(found){   
                        cout << "File Explorer already exists, \n";
                        cout << "would you like to replace (0) \n";
                        cout << "Do nothing (1) \n";
                        cout << "Or terminate Process (2) \n";
                        
                        cin >> choice;
                        
                        switch(choice){
                            
                            case 0:
                            
                            for (int i = 0; i < vec.size(); i++) {
                                if (vec[i].name == "File Explorer") {
                                    //used to iterate and set the index of the number wanted to be found
                                    //then .erase() to erase the element
                                    //without this and typing vec.erase(i) causes overloading problem/bug
                                    vector<Process>::iterator it = vec.begin(); 
                                    advance(it, i);
                                    vec.erase(it);
                                }
                            }   
                            
                            File.id = distr1(gen);
                
                            File.state = "ready";
            
                            File.cpuBurst = distr2(gen);
                            
                            vec.push_back(File);
                            
                            break;
                                
                            case 1:
                            break;
                            
                            case 2:
                            
                            for (int i = 0; i < vec.size(); i++) {
                                    if (vec[i].name == "File") {
                                        //used to iterate and set the index of the number wanted to be found
                                        //then .erase() to erase the element
                                        //without this and typing vec.erase(i) causes overloading problem/bug
                                        vector<Process>::iterator it = vec.begin(); 
                                        advance(it, i);
                                        vec.erase(it);
                                    }
                                }   
                            break;
                            
                        }
                    }
                    else{
                        
                        File.name = "File Explorer";
                        
                        File.id = distr1(gen);

                        cout <<"File Explorer's Process ID is: "<< File.id << endl;
                
                        File.state = "ready";
        
                        File.cpuBurst = distr2(gen);

                        cout <<"Process burst time: " << File.cpuBurst <<" cycle/s"<< endl;
                        
                        vec.push_back(File);
                        
                    }
                
            }

            break;
        case 4:
        
            if (vec.size() == 0) {

                PowerPoint.name = "Microsoft PowerPoint";

                PowerPoint.id = distr1(gen);

                cout <<"PowerPoint's Process ID is: "<< PowerPoint.id << endl;

                PowerPoint.state = "running";

                PowerPoint.cpuBurst = distr2(gen);

                cout <<"Process burst time: " << PowerPoint.cpuBurst <<" cycle/s"<< endl;

                vec.push_back(PowerPoint);


            }
            else{
                
                for (int j = 0; j < vec.size(); j++) {

                    if(vec[j].name == "Microsoft PowerPoint"){
                        
                        found = true;
                        
                    }
                    

                }
                
                if(found){
                        cout << "Microsoft PowerPoint already exists, \n";
                        cout << "would you like to replace (0) \n";
                        cout << "Do nothing (1) \n";
                        cout << "Or terminate Process (2) \n";
                        
                        cin >> choice;
                        
                        switch(choice){
                            
                            case 0:
                            
                            for (int i = 0; i < vec.size(); i++) {
                                if (vec[i].name == "Microsoft PowerPoint") {
                                    //used to iterate and set the index of the number wanted to be found
                                    //then .erase() to erase the element
                                    //without this and typing vec.erase(i) causes overloading problem/bug
                                    vector<Process>::iterator it = vec.begin(); 
                                    advance(it, i);
                                    vec.erase(it);
                                }
                            }   
                            
                            PowerPoint.id = distr1(gen);
                
                            PowerPoint.state = "ready";
            
                            PowerPoint.cpuBurst = distr2(gen);
                            
                            vec.push_back(PowerPoint);
                            
                            break;
                                
                            case 1:
                            break;
                            
                            case 2:
                            
                            for (int i = 0; i < vec.size(); i++) {
                                    if (vec[i].name == "Microsoft PowerPoint") {
                                        //used to iterate and set the index of the number wanted to be found
                                        //then .erase() to erase the element
                                        //without this and typing vec.erase(i) causes overloading problem/bug
                                        vector<Process>::iterator it = vec.begin(); 
                                        advance(it, i);
                                        vec.erase(it);
                                    }
                                }   
                            break;
                            
                        }
                    }
                    else{
                        
                        PowerPoint.name = "Microsoft PowerPoint";
                        
                        PowerPoint.id = distr1(gen);

                        cout <<"PowerPoint's Process ID is: "<< PowerPoint.id << endl;
                
                        PowerPoint.state = "ready";
        
                        PowerPoint.cpuBurst = distr2(gen);

                        cout <<"Process burst time: " << PowerPoint.cpuBurst <<" cycle/s"<< endl;
                        
                        vec.push_back(PowerPoint);
                        
                    }
                
            }
            break;




        case 5:

            //tasks are shown if vector vec is not empty

            if (vec.size() == 0) {
                cout << "No Processes are open at this moment." << endl;
            }
            else {
                cout << "Process Name:\t\tProcess ID:\t\tState:\t\tCPU Burst:" << endl;



                for (int j = 0; j < vec.size(); j++) {

                    cout << vec[j].name << "\t\t\t" << vec[j].id << "\t\t\t" << vec[j].state << "\t\t\t" << vec[j].cpuBurst << endl << endl;

                }

            }
            break;
        }



        bool running = false;
        
        counter++;

        for (int k = 0; k < vec.size(); k++) {

            if(vec[k].state == "running"){
                running = true;
            }
            

        }
        
        
            for(int l = 0; l < vec.size(); l++){
                
                if(vec[l].cpuBurst == 0){
                    if(vec[l].state == "running"){
                        vec[l].state = "waiting";
                        
                        if(!(l+1 >= vec.size())){
                            vec[l+1].state = "running";
                        }
                        
                    }
                    else if(vec[l].state == "waiting"){
                        
                        if(!(l+1 >= vec.size())){
                            if(vec[l+1].state == "ready"){
                                vec[l+1].state = "running";
                            }
                        }
                        
                    }
                }
                else{
                    if(vec[l].state == "running"){
                        vec[l].cpuBurst = vec[l].cpuBurst - 1;
                        if(vec[l].cpuBurst == 0){
                            vec[l].state = "waiting";
                            
                            if(!(l+1 >= vec.size())){
                                vec[l+1].state = "running";
                            }
                        }
                    }
                }
                
            }
            
        



    } while (menuChoice != 0);







}

int main() {

	//cout << "random number " << random_number << endl;


	Welcome();
/*
	if(logged) {

		menu();

	}
	*/


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

	return 0;
}
