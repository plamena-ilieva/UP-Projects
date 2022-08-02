#include <iostream>
#include <vector>
#include <fstream>
#include "readData.h"
#include "createDocument.h"

#define formatVector std::vector<std::pair<std::string, std::string>>
#define dataVector std::vector<std::string*>


int main() {
    //to do: destructor
    std::ifstream inFile("database.txt");
    if (!inFile.is_open()) {
        std::cout << "Error while opening file!" << std::endl;
        return -1;
    }
    formatVector formatData;
    readFormat(formatData, inFile);
    dataVector memberData;
    while(true) {
        readMember(memberData, formatData, inFile);

        if (inFile.eof())
            break;
    }


    return 0;
}
