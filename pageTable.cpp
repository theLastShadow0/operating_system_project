#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <sstream>

class logicalMemory {
public:
    std::string name; // Program name
    double virtualAddress; // Virtual address in decimal
    
    //initializes name as empty string, and virtualAddress as 0
    logicalMemory(): name(""), virtualAddress(0) {}

    logicalMemory(const std::string& name, double virtualAddress)
        : name(name), virtualAddress(virtualAddress) {}

    //virtual address in hexadecimal
    std::string getHexAddress() const {
        std::stringstream ss;
        ss << std::hex << std::uppercase << static_cast<int>(virtualAddress);
        return ss.str();
    }
};


class PageTable{
private:
    std::unordered_map<std::string, logicalMemory> pageTable;

public: //constructor
    PageTable(){}
    
    void addProgram(const std:: string& name, double virtualAddress){
        pageTable[name] = logicalMemory(name, virtualAddress);
    }
    
    void displayPageTable() const {
        for (const auto& entry : pageTable){
            std:: cout << "Program: " << entry.second.name << ", Virtual Address: 0x" << entry.second.getHexAddress()<< std::endl;
        }
    }
};


int main(){
    
    PageTable pt;
    
    pt.addProgram("Google Chrome", 1193200); //virtual address will be translated to hex at the end
    pt.addProgram("Microsoft Word", 1193201);
    pt.addProgram("File Explorer", 1193202);
    pt.addProgram("Microsoft PowerPoint", 1193203);
    
    pt.displayPageTable();
    
    return 0;
}