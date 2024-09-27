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
  
  return 0;
}
