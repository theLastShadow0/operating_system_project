#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>

using namespace std;

int pageSize = 4096;

class logicalMemory {
public:
    string name; // Program name
    int virtualAddress; // Virtual address in decimal
    
    logicalMemory(): name(""), virtualAddress(0) {} //initializes name as empty string, and virtualAddress as 0

    logicalMemory(const string& name, int virtualAddress)
        : name(name), virtualAddress(virtualAddress) {}
};

class LogicalTable{
private:
    unordered_map<string, logicalMemory> logicalTable; //program name as the key, and virtual address as value
    unordered_map<int,int>pageTable; //page number is set as the key, and frame number as the value

public: //constructor

    void addProgram(const string& name, int virtualAddress, int frameNumber){
        int pageNumber = virtualAddress / pageSize; 
        
        pageTable[pageNumber] = frameNumber;
        logicalTable[name] = logicalMemory(name, virtualAddress);
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
            cout<< entry.second.name << " has a virtual address of 0x" << hex << entry.second.virtualAddress<< " and got translated to physical address " << "0x" << hex << physicalAddress << endl;
        }
    }
};


int main(){

    LogicalTable pt;
    
    //unordered map has the name of the program, virtual address in decimal, and the frame number
    pt.addProgram("Google Chrome", 1193200,5); 
    pt.addProgram("Microsoft Word", 1193201,6);
    pt.addProgram("File Explorer", 1193202,7);
    pt.addProgram("Microsoft PowerPoint", 1193203,8);

    pt.displayLogicalTable();
    
    return 0;
}
