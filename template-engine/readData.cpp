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
* <cpp file with functions that read the data from the database>
*
*/

#include "readData.h"
#include "stringOperations.h"

const int SIZE = 1024;

/** a function that reads the format of the data presented - the first line of the data file*/
void readFormat(formatVector &formatData, std::ifstream &inFile) {
    char input[SIZE];
    inFile.getline(input, SIZE);
    std::string formatInput(input);
    std::vector<std::string> format = split(formatInput, ',');
    for (std::string &variable: format) {
        std::pair<std::string, std::string> current;
        std::vector<std::string> splitVars = split(variable, ':');
        current.first = splitVars[0];
        current.second = splitVars[1];
        formatData.push_back(current);
    }
}

/** a function that reads a single member from the data file */
void readMember(strMatrix &memberData, const formatVector &formatData, std::ifstream &inFile) {
    size_t count = 0;
    for (auto &variable: formatData) {
        memberData.push_back(std::vector<std::string>());
        if (variable.second == "string") {
            char input[SIZE];
            inFile.getline(input, SIZE, ',');

            /** if the input is an empty string, the file has ended */
            if (input[0] == '\0')
                return;
            std::string str(input);
            memberData[count++].push_back(str);
        } else if (variable.second == "string*") {
            char input[SIZE];
            inFile.getline(input, SIZE, '}');
            if (input[0] == '\0')
                return;
            /** inputStr contains all the members of an array */
            std::string inputStr = std::string(input).substr(1);
            std::vector<std::string> splitInput = split(inputStr, ',');
            for (auto &i: splitInput) {
                memberData[count].push_back(i);
            }
            ++count;
        }
    }
    /** we want to go to the next line */
    inFile.ignore();
}
