#include <iostream>
#include <vector>
#include "readData.h"
#include "createDocument.h"
#include "readTemplate.h"

#define formatVector std::vector<std::pair<std::string, std::string>>
#define dataVector std::vector<std::string*>
#define strMatrix std::vector<std::vector<std::string>>


int main() {
    //to do: destructor
    std::ifstream inFileData("database.txt");
    if (!inFileData.is_open()) {
        std::cout << "Error while opening file!" << std::endl;
        return -1;
    }

    std::ifstream inFileTemplate("template.txt");
    if (!inFileTemplate.is_open()) {
        std::cout << "Error while opening file!" << std::endl;
        return -1;
    }

    formatVector formatData;
    readFormat(formatData, inFileData);
    strMatrix templateData;

    if (!readTemplate(templateData, formatData, inFileTemplate))
        return 1;

    /*dataVector memberData;
    while(true) {
        readMember(memberData, formatData, inFileData);

        if (inFileData.eof())
            break;
    }*/

    return 0;
}
