#include <iostream>
using namespace std;

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
cout << "Welcome to TAMIU OS" << endl; 

  
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

  //For the system login is it simply asking for a username and password from the user.
  //It does not check if there is an account in the system/ Doesnt save accounts.
    int loginChoice;
    string userName;
    string passWord;
    
    cout << "Press '1' to login to an existing account" << endl;
    cout << "Press '2' to create a new account" << endl;
    cout << "Press '0' to turn shut down" << endl;
    cin >> loginChoice;


    switch(loginChoice){
    case 0:
        cout << "Shutting down..." << endl;
        return 0;
    case 1:
        cout << "Username: " << endl;
        cin >> userName;
        cout << "Password: " << endl;
        cin >> passWord;
        cout << "Welcome back " << userName << endl;
        break;
    case 2:
        cout << "New Username: " << endl;
        cin >> userName;
        cout << "New Password: " << endl;
        cin >> passWord;
        cout << "Welcome " << userName << endl;
        break;
    }
    
  //PROCESS CREATION AND TERMINATION
  //
  //For the process creation I made a menu where the user can choose what program they want to execute.
  //The menu will keep on looping until the user decides to end the program by signing out.
  //Work is needed so the user can run a program and decide to end that program and go back to the menu.
  //

    int menuChoice;
    do{
        cout << "Please choose a program to execute on your OS: " << endl;
        cout << " Press '1' to run Google Chrome" << endl;
        cout << " Press '2' to run Microsoft Word" << endl;
        cout << " Press '3' to run File Explorer" << endl;
        cout << " Press '4' to run Microsoft PowerPoint" << endl;
        cout << " Press '0' to sign out " << endl;
        cin >> menuChoice;
        
        switch(menuChoice){
            case 0:
                cout << "Signing out...\n" << endl;
                return main();
            case 1:
                cout << "Running Google Chrome..." << endl;
                break;
            case 2:
                cout << "Running Microsoft Word" << endl;
                break;
            case 3:
                cout << "Running File Explorer" << endl;
                break;
            case 4:
                cout << "Running Microsoft PowerPoint" << endl;
                break;
        }
    }while (menuChoice != 0);
    return 0;
}
