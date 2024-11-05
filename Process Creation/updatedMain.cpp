#include <iostream>
#include <vector>
#include <stdlib.h> // this is to clear the terminal
using namespace std;


//LOGIN AUTHENTICATION
  //
  //Like any other computer, it would require a username and password
  //
  //If the user does not have a username or password, prompt them to make an account
  //
  //Save info, and prompt user to login and then confirm their inputs

  /*

  IMPLEMENTATION:
  I've had a couple of ideas, but the one that made most sense to me is to look for 2 .txt files
  one is for usernames and the other is for passwords.

  IF
  One or the other does not exist, then create one or both.

  In order to check for authenticity, or in other words, that they match, we would need to check the position
  of the username the user inputed in the username.txt file and search the password in the password.txt file in the same position
  and then check if the password matches.

  */



  //PROCESS CREATION AND TERMINATION
  //
  //Create a class for the Operating System which will have the login prompt and processes. 
  //
  //For the system login is it simply asking for a username and password from the user.
  //It does not check if there is an account in the system/doesn't save accounts.
  //
  //For the process creation I made a menu where the user can choose what program they want to execute.
  //The menu will keep on looping until the user decides to end the program by signing out.
  //Work is needed so the user can terminate the program and choose to execute another one.

class OperatingSystem {
public:
    string userName;
    string passWord;

    void login() {
        int loginChoice;
        cout << "Press '1' to login to an existing account" << endl;
        cout << "Press '2' to create a new account" << endl;
        cout << "Press '0' to turn shut down" << endl;
        cin >> loginChoice;

        system("cls"); //clears terminal

        switch (loginChoice) {
        case 0:
            cout << "Shutting down..." << endl;
            exit(0);
        case 1:
            cout << "Username: " << endl;
            cin >> userName;
            cout << "Password: " << endl;
            cin >> passWord;

            system("cls"); //clears terminal

            cout << "Welcome back " << userName << endl;
            return menu();
        case 2:
            cout << "New Username: " << endl;
            cin >> userName;
            cout << "New Password: " << endl;
            cin >> passWord;

            system("cls"); //clears terminal

            cout << "Welcome " << userName << endl;
            return menu();
        }
    }

    

    struct Task{
      
        string state = "running";
        bool exists;
     
    
    };

    void menu() {

        //exist is set to 0 for if statements to check if they are "running", 
        //but by doing so can't add more than one of the same process 

        Task google;
        google.exists = 0;

        Task word;
        word.exists = 0;

        Task file;
        file.exists = 0;

        Task powerpoint;
        powerpoint.exists = 0;

        //character used to prompt the user for if they want to terminate a process
        char terminate;

        int menuChoice;
        vector<int> vec; //vector to store the processes opened. Used because it is easier to remove elements

        do {
            cout << "Please choose a program to execute on your OS: " << endl;
            cout << " Press '1' to run Google Chrome" << endl;
            cout << " Press '2' to run Microsoft Word" << endl;
            cout << " Press '3' to run File Explorer" << endl;
            cout << " Press '4' to run Microsoft PowerPoint" << endl;
            cout << " Press '5' to see tasks running" << endl; // NEW
            cout << " Press '0' to sign out " << endl;
            cin >> menuChoice;

            system("cls"); //clears terminal

            switch (menuChoice) {
            case 0:
                cout << "Signing out...\n" << endl;
                return login();
            case 1:
                if(!google.exists){
 
                    cout << "Running Google Chrome..." << endl << endl;
                    google.exists = 1;
                    vec.push_back(1);
                    
                }
                else {
                    cout << "Google Chrome is already open,\n would you like to terminate process? (y/n)" << endl;
                    cin >> terminate;
                    if (terminate != 'y' && terminate != 'Y') {
                        system("cls"); //clears terminal
                    }
                    else {

                        cout << "Terminating Google Chrome..." << endl << endl; 
                        google.exists = 0;

                        for (int i = 0; i < vec.size(); i++) {
                            if (vec[i] == 1) {
                                //used to iterate and set the index of the number wanted to be found
                                //then .erase() to erase the element
                                //without this and typing vec.erase(i) causes overloading problem/bug
                                vector<int>::iterator it = vec.begin(); 
                                advance(it, i);
                                vec.erase(it);
                            }
                        }
                    }
                }
                
                break;
            case 2:
                if (!word.exists) {

                    cout << "Running Microsoft Word" << endl << endl;
                    word.exists = 1;
                    vec.push_back(2);
                }
                else {
                    cout << "Microsoft Word is already open, \n would you like to terminate process? (y/n)" << endl;
                    cin >> terminate;
                    if (terminate != 'y' && terminate != 'Y') {
                        system("cls"); //clears terminal
                    }
                    else {

                        cout << "Terminating Microsoft Word..." << endl << endl;
                        word.exists = 0;

                        for (int i = 0; i < vec.size(); i++) {
                            if (vec[i] == 2) {
                                vector<int>::iterator it = vec.begin();
                                advance(it, i);
                                vec.erase(it);
                            }
                        }
                    }
                }
                
                break;
            case 3:
                if (!file.exists) {

                    cout << "Running File Explorer" << endl << endl;
                    file.exists = 1;
                    vec.push_back(3); 
                }
                else {
                    cout << "File Explorer is already open, \n would you like to terminate process? (y/n)" << endl;
                    cin >> terminate;
                    if (terminate != 'y' && terminate != 'Y') {
                        system("cls"); //clears terminal
                    }
                    else {

                        cout << "Terminating File Explorer..." << endl << endl;
                        file.exists = 0;

                        for (int i = 0; i < vec.size(); i++) {
                            if (vec[i] == 3) {
                                vector<int>::iterator it = vec.begin();
                                advance(it, i);
                                vec.erase(it);
                            }
                        }
                    }
                }
                
                break;
            case 4:
                if (!powerpoint.exists) {

                    cout << "Running Microsoft PowerPoint" << endl << endl;
                    powerpoint.exists = 1;
                    vec.push_back(4);
                }
                else {
                    
                    cout << "Microsoft PowerPoint is already open, \n would you like to terminate process? (y/n)" << endl;
                    cin >> terminate;
                    if (terminate != 'y' && terminate != 'Y') {
                        system("cls"); //clears terminal
                    }else{

                        cout << "Terminating Microsoft PowerPoint..." << endl << endl;
                        powerpoint.exists = 0;

                        for (int i = 0; i < vec.size(); i++) {
                            
                            if (vec[i] == 4) {
                                vector<int>::iterator it = vec.begin();
                                advance(it, i);
                                vec.erase(it);
                            }
                        }
                    }
                }
                break;




            case 5: 

                //tasks are shown if vector vec is not empty

                if (vec.size() == 0) { 
                    cout << "No Processes are open at this moment." << endl;
                }
                else {
                    cout << "Process:                     State:" << endl;



                    for (int i = 0; i < vec.size(); i++) {

                        switch (vec[i]) { //this way the processes appear in order from the first added to last (top to bottom)

                        case 1:

                            cout << "Google                     " << google.state << endl;

                            break;
                        case 2:
                            cout << "Microsoft Word             " << google.state << endl;

                            break;
                        case 3:
                            cout << "File Explorer              " << google.state << endl;

                            break;
                        case 4:
                            cout << "Microsoft PowerPoint       " << google.state << endl;

                            break;
                        }

                    }
                }


                break;
            }





        } while (menuChoice != 0);
    }

};



int main() {

    //BOOTING UP THE SYSTEM
    // 
    // When power initialized on system, execution starts at a fixed memory location
    // 
    //		Firmware ROM used to hold initial boot code (bootstrap loader)
    // 
    //Small piece of code - bootstrap loader, stored in ROM or EEPROM located the kernel, loads it into memory, and starts it
    //
    //kernel loads and system is then running

    /*

    IMPLEMENTATION:
      Make a class named ROM
      Get "bootstrap loader" from class
      Bootstrap loader will contain the address of the "kernel"
      Kernel "loads" (simulate that it loaded) and system is "running"

    */

    //Create object of OperatingSystem Class 
    OperatingSystem tamiuOS;

    cout << "Welcome to TAMIU OS" << endl;
    //Call of functions
    tamiuOS.login();

    tamiuOS.menu();

    return 0;
}
