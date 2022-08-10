/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Plamena Ilieva
* @idnumber 6MI0600020
* @compiler GCC
*
* <main file>
* reads the data and the template from resource files
* merges data and template in a new file for each member
*
*/

#include <iostream>
#include <vector>
#include "readData.h"
#include "createDocument.h"
#include "readTemplate.h"
#include "stringOperations.h"

/** formatVector - holds the format, contains all the variable names and their types */
#define formatVector std::vector<std::pair<std::string, std::string>>
#define strMatrix std::vector<std::vector<std::string>>

int main() {
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

    size_t counter = 1;
    while (true) {
        strMatrix memberData;
        readMember(memberData, formatData, inFileData);
        if (inFileData.eof())
            break;
        std::ofstream outFile(numToStr(counter));
        if (!outFile.is_open()) {
            std::cout << "Error while opening file!" << std::endl;
            return -1;
        }
        writeDocument(memberData, templateData, formatData, outFile);
        outFile.close();
        ++counter;
    }
    return 0;
}
