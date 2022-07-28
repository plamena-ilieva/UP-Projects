#include <iostream>
#include <vector>
#include <fstream>
#include "readData.h"

#define formatVector std::vector<std::pair<std::string, std::string>>
#define dataVector std::vector<std::string*>


int main() {
    //to do: destructor
    std::ifstream inFile("database.txt");
    if (!inFile.is_open()) {
        std::cout << "Error while opening file!" << std::endl;
        return -1;
    }
    formatVector format;
    readFormat(format, inFile);
    dataVector data;
    while(true) {
        readMember(data, format, inFile);
        if (inFile.eof())
            break;
    }

    return 0;
}
