#include "readData.h"
#include "stringOperations.h"

void readFormat(formatVector &formatData, std::ifstream &inFile) {
    std::string formatInput;
    inFile >> formatInput;
    std::vector<std::string> format = split(formatInput, ',');
    for (std::string &variable: format) {
        std::pair<std::string, std::string> current;
        std::vector<std::string> splitVars = split(variable, ':');
        current.first = splitVars[0];
        current.second = splitVars[1];
        formatData.push_back(current);
    }

}

void readMember(dataVector &memberData, const formatVector &formatData, std::ifstream &inFile){
    for(auto &variable: formatData) {
        if (variable.second == "string") {
            char input[1024];
            inFile.getline(input, 1024, ',');
            std::string* ptr = new std::string(input);
            memberData.push_back(ptr);
        }
        else if (variable.second == "string*") {
            char input[1024];
            inFile.getline(input, 1024, '}');
            std::string inputStr = std::string(input).substr(1);
            std::vector<std::string> splitInput = split(inputStr, ',');
            std::string *ptr = new std::string[splitInput.size()];
            for (int i = 0; i < splitInput.size(); ++i) {
                ptr[i] = splitInput[i];
            }
            memberData.push_back(ptr);
        }
    }
}
