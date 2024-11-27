#include <iostream>
#include <unordered_map>
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

random_device rd;

int pageSize = 4096;

//implement with making process (loop) to make sure all random numbers do not repeat.
mt19937 gen(rd());

uniform_int_distribution<> distr1(1000,9999); //For the random pid

uniform_int_distribution<> distr2(1,10);//For CPU bursts

uniform_int_distribution<> distr3(1000000,9999999);//For virtualAddress

class logicalMemory {
public:
    string name; // Program name
    int virtualAddress; // Virtual address in decimal
    int cpu;
    int pid;
    string state;
    
    logicalMemory(): name(""), virtualAddress(0), cpu(0), pid(0), state("") {} //initializes name as empty string, and virtualAddress as 0

    logicalMemory(const string& name, int virtualAddress, int cpu, const int& pid, string& state)
        : name(name), virtualAddress(virtualAddress), cpu(cpu), pid(pid), state(state) {}
};

class LogicalTable{
private:
    unordered_map<string, logicalMemory> logicalTable; //program name as the key, and virtual address as value
    unordered_map<int,int>pageTable; //page number is set as the key, and frame number as the value

public: //constructor

    void addProgram(const string& name, int virtualAddress, int cpu, int pid, string& state, int frameNumber){
        int pageNumber = virtualAddress / pageSize; 
        
        pageTable[pageNumber] = frameNumber;
        logicalTable[name] = logicalMemory(name, virtualAddress, cpu, pid, state);
    }

    int translate(int virtualAddress, int pageSize)const{
        int pageNumber = virtualAddress / pageSize;
        int offset = virtualAddress % pageSize;

        if(pageTable.find(pageNumber)== pageTable.end()){
            cout << "Error: Page number not found in page table." << endl;
            return -1;
        }

        int frameNumber = pageTable.at(pageNumber);
        int physicalAddress = frameNumber * pageSize + offset;
        return physicalAddress;
    }

    void displayLogicalTable() const {
        for (const auto& entry: logicalTable){

            int physicalAddress = translate(entry.second.virtualAddress, pageSize);
            cout<< entry.second.name << " has a virtual address of 0x" << hex << entry.second.virtualAddress
            << " and got translated to physical address " << "0x" << hex << physicalAddress << endl << endl;
        }
    }
    
    //NEW PUBLIC FUNCTIONS 
    //Looks for a specific process with parameter name
    bool LookFor(string name){
        
        bool found = false;
        
        for (const auto& entry: logicalTable){

            if(entry.second.name == name){
                found = true;
            }
            
        }
        
        return found;
        
    }
    
    //removes process from hashtable
    void Remove(string name){
        
        logicalTable.erase(name);
        
    }
    
    //displays the PCB 
    void displayProcessCB() const {
        
        cout << "Process Name:\t\tProcess ID:\t\tState:\t\tCPU Burst:" << endl;

        
        for (const auto& entry: logicalTable){

            cout << entry.second.name << "\t\t\t" << entry.second.pid << "\t\t\t" << entry.second.state << "\t\t\t" << entry.second.cpu << endl << endl;
            
        }
    }
    
    //decrements cpu burst does not run without the next function
    void Bursts() {
        
        for (auto& entry: logicalTable){
            if(entry.second.state == "running"){
                if(entry.second.cpu > 0){
                    entry.second.cpu = entry.second.cpu - 1;
                }
            }
            if(entry.second.cpu == 0){
                entry.second.state = "waiting";
            }
        }
        
    }
    
    //checks for a state that is running
    void QueueUp() {
        
        bool runningfound = 0;
        
        for (const auto& entry: logicalTable){

            if(entry.second.state == "running"){
                runningfound = true;
            }
            
        }
        //if running state is found, Bursts() executes
        if(runningfound){
            Bursts();
        }
        //If not found, makes the next ready found to running
        else{
            for (auto& entry: logicalTable){

                if(entry.second.state == "ready"){
                    entry.second.state = "running";
                    break;
                }
            
            }
        }
    }
    
};

void menu();

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
		menu();
		break;

	case 2:
		menu();
		break;

	}


}


LogicalTable pt;

void menu() {

    //exist is set to 0 for if statements to check if they are "running",
    //but by doing so can't add more than one of the same process

	cout << "Welcome " << "insert_username" << endl;

    //character used to prompt the user for if they want to terminate a process
    int choice;
    
    string name;
	int id;
	string state;
	int cpuBurst;
	int vaddress;
	
    int menuChoice;
    vector<string> vec; //vector to store the process name 

    do {
        
        bool found = false;

        
        cout << "Please choose a program to execute on your OS: " << endl;
        cout << " Press '1' to run Google Chrome" << endl;
        cout << " Press '2' to run Microsoft Word" << endl;
        cout << " Press '3' to run File Explorer" << endl;
        cout << " Press '4' to run Microsoft PowerPoint" << endl;
        cout << " Press '5' to see tasks running" << endl;
        cout << " Press '0' to sign out " << endl;
        cin >> menuChoice;

        //system("cls"); //clears terminal

        switch (menuChoice) {

        case 0:
            cout << "Signing out...\n" << endl;
            return Welcome();


        case 1:

            if (vec.size() == 0) {

                name = "Google Chrome";

                id = distr1(gen);
                
                state = "running";

                cpuBurst = distr2(gen);
                
                vaddress = distr3(gen);

                vec.push_back(name);
                
                pt.addProgram(name, vaddress, cpuBurst, id, state, 5);

            }
            else{
                
                found = pt.LookFor("Google Chrome"); // bool LookFor(string name);
                
                if(found){
                    cout << "Google Chrome already exists, \n";
                    cout << "would you like to replace (0) \n";
                    cout << "Do nothing (1) \n";
                    cout << "Or terminate Process (2) \n";
                    
                    cin >> choice;
                    
                    switch(choice){
                        
                        case 0:
                        
                        pt.Remove("Google Chrome"); // void Remove(string name);   
                        
                        id = distr1(gen);
                        
                        state = "ready";
        
                        cpuBurst = distr2(gen);
                        
                        vaddress = distr3(gen);
                        
                        vec.push_back(name);
                        
                        pt.addProgram(name, vaddress, cpuBurst, id, state, 5);
                        
                        break;
                            
                        case 1:
                        break;
                        
                        case 2:
                        
                        pt.Remove("Google Chrome");
                        break;
                        
                    }
                }
                else{
                    
                    name = "Google Chrome";

                    id = distr1(gen);

                    state = "ready";
    
                    cpuBurst = distr2(gen);
                    
                    vaddress = distr3(gen);

                    vec.push_back(name);
                    
                    pt.addProgram(name, vaddress, cpuBurst, id, state, 5);

                    
                }
                
            }
            
            

            break;
        
        case 2:
            if (vec.size() == 0) {

                name = "Microsoft Word";

                id = distr1(gen);
                
                state = "running";

                cpuBurst = distr2(gen);
                
                vaddress = distr3(gen);

                vec.push_back(name);
                
                pt.addProgram(name, vaddress, cpuBurst, id, state, 6);

            }
            else{
                
                found = pt.LookFor("Microsoft Word"); // bool LookFor(string name);
                
                if(found){
                    cout << "Microsoft Word already exists, \n";
                    cout << "would you like to replace (0) \n";
                    cout << "Do nothing (1) \n";
                    cout << "Or terminate Process (2) \n";
                    
                    cin >> choice;
                    
                    switch(choice){
                        
                        case 0:
                        
                        pt.Remove("Microsoft Word"); // void Remove(string name);   
                        
                        id = distr1(gen);
                        
                        state = "ready";
        
                        cpuBurst = distr2(gen);
                        
                        vaddress = distr3(gen);
                        
                        vec.push_back(name);
                        
                        pt.addProgram(name, vaddress, cpuBurst, id, state, 6);
                        
                        break;
                            
                        case 1:
                        break;
                        
                        case 2:
                        
                        pt.Remove("Microsoft Word");
                        break;
                        
                    }
                }
                else{
                    
                    name = "Microsoft Word";

                    id = distr1(gen);

                    state = "ready";
    
                    cpuBurst = distr2(gen);
                    
                    vaddress = distr3(gen);

                    vec.push_back(name);
                    
                    pt.addProgram(name, vaddress, cpuBurst, id, state, 6);

                    
                }
                
            }

            break;
            
        case 3:
            if (vec.size() == 0) {

                name = "File Explorer";

                id = distr1(gen);
                
                state = "running";

                cpuBurst = distr2(gen);
                
                vaddress = distr3(gen);

                vec.push_back(name);
                
                pt.addProgram(name, vaddress, cpuBurst, id, state, 7);

            }
            else{
                
                found = pt.LookFor("File Explorer"); // bool LookFor(string name);
                
                if(found){
                    cout << "File Explorer already exists, \n";
                    cout << "would you like to replace (0) \n";
                    cout << "Do nothing (1) \n";
                    cout << "Or terminate Process (2) \n";
                    
                    cin >> choice;
                    
                    switch(choice){
                        
                        case 0:
                        
                        pt.Remove("File Explorer"); // void Remove(string name);   
                        
                        id = distr1(gen);
                        
                        state = "ready";
        
                        cpuBurst = distr2(gen);
                        
                        vaddress = distr3(gen);
                        
                        vec.push_back(name);
                        
                        pt.addProgram(name, vaddress, cpuBurst, id, state, 7);
                        
                        break;
                            
                        case 1:
                        break;
                        
                        case 2:
                        
                        pt.Remove("File Explorer");
                        break;
                        
                    }
                }
                else{
                    
                    name = "File Explorer";

                    id = distr1(gen);

                    state = "ready";
    
                    cpuBurst = distr2(gen);
                    
                    vaddress = distr3(gen);

                    vec.push_back(name);
                    
                    pt.addProgram(name, vaddress, cpuBurst, id, state, 7);

                    
                }
                
            }

            break;
        case 4:
            if (vec.size() == 0) {

                name = "Microsoft PowerPoint";

                id = distr1(gen);
                
                state = "running";

                cpuBurst = distr2(gen);
                
                vaddress = distr3(gen);

                vec.push_back(name);
                
                pt.addProgram(name, vaddress, cpuBurst, id, state, 8);

            }
            else{
                
                found = pt.LookFor("Microsoft PowerPoint"); // bool LookFor(string name);
                
                if(found){
                    cout << "Microsoft PowerPoint already exists, \n";
                    cout << "would you like to replace (0) \n";
                    cout << "Do nothing (1) \n";
                    cout << "Or terminate Process (2) \n";
                    
                    cin >> choice;
                    
                    switch(choice){
                        
                        case 0:
                        
                        pt.Remove("Microsoft PowerPoint"); // void Remove(string name);   
                        
                        id = distr1(gen);
                        
                        state = "ready";
        
                        cpuBurst = distr2(gen);
                        
                        vaddress = distr3(gen);
                        
                        vec.push_back(name);
                        
                        pt.addProgram(name, vaddress, cpuBurst, id, state, 8);
                        
                        break;
                            
                        case 1:
                        break;
                        
                        case 2:
                        
                        pt.Remove("Microsoft PowerPoint");
                        break;
                        
                    }
                }
                else{
                    
                    name = "Microsoft PowerPoint";

                    id = distr1(gen);

                    state = "ready";
    
                    cpuBurst = distr2(gen);
                    
                    vaddress = distr3(gen);

                    vec.push_back(name);
                    
                    pt.addProgram(name, vaddress, cpuBurst, id, state, 8);

                    
                }
                
            }

            break;
        
        case 5:

            //tasks are shown if vector vec is not empty

            if (vec.size() == 0) {
                cout << "No Processes are open at this moment." << endl;
            }
            else {
                
                pt.displayProcessCB();
                
                pt.displayLogicalTable();

            }
            break;
        }
        
        pt.QueueUp();



    } while (menuChoice != 0);
}
    
int main(){
    
    Welcome();
    
}
