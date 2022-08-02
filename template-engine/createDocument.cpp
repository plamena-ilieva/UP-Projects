#include "createDocument.h"
#include "stringOperations.h"

bool writeMember(const dataVector& memberData, const formatVector& formatData,
                 std::ifstream& inFile, std::ofstream & outFile) {

    while (true) {
        char input[1024];
        inFile.getline(input, 1024);
        std::string inputStr = std::string(input);
        std::vector<std::string> splitInput = split(inputStr, ' ');
        size_t i = 0;
        if (splitInput[0] == "{%") {
            if (splitInput.size() != 6)
                return false;
            if (splitInput[1] != "for" || splitInput[3] != "in"|| splitInput[5] != "%}")
                return false;
            char body[1024];
            inFile.getline(body, 1024);
            std::string bodyStr = std::string(body);
            std::vector<std::string> bodyInput = split(bodyStr, ' ');
            char end[1024];
            inFile.getline(end, 1024);
            std::string endStr = std::string(end);
            if (endStr != "{% endfor %}")
                return false;
            if (!writeCycle(splitInput, inputStr, memberData, formatData, outFile))
                return false;
        }
        else {
            if (!writeVariable(inputStr, memberData, formatData, outFile))
                return false;
        }

        if (inFile.eof())
            break;
    }
    return true;
}

long long findKey(const formatVector& formatData, const std::string& var) {
    for (size_t i = 0; i < formatData.size(); ++i) {
        if (formatData[i].first == var)
            return i;
    }
    return -1;
}

bool calcRangeToReplace(const std::string& inputStr, size_t& startIndex,
                        size_t& endIndex, size_t& i) {
    startIndex = findThreeSymbols(inputStr, '}', '}', ' ', i);
    if (startIndex == -1) {
        return true;
    }

    endIndex = findThreeSymbols(inputStr, ' ', '}', '}', i);
    if (endIndex == -1)
        return false;
    return true;
}


bool writeVariable(std::string& inputStr, const dataVector& memberData,
                   const formatVector& formatData, std::ofstream & outFile) {
    /*for (size_t i = 0; i < splitInput.size() - 2; ++i) {
        if (splitInput[i] == "{{" && splitInput[i+2] == "}}") {
            long long formatIndex = findKey(formatData, splitInput[i+1]);
            if (formatIndex == -1)
                return false;
            splitInput[i+1] = *memberData[formatIndex];
            i+=2;
        }
        else if(splitInput[i] == "{{" && splitInput[i+2] != "}}")
            return false;
    }
    for (int i = 0; i < splitInput.size() - 1; ++i) {
       if (splitInput[i] != "{{" && splitInput[i+2] == "}}")
           outFile << splitInput[i] << ' ';
    }
    outFile << splitInput[splitInput.size() - 1] << std::endl;*/
    size_t i = 0;
    while (inputStr[i] != '\0') {

        size_t startIndex, endIndex;
        if (calcRangeToReplace(inputStr, startIndex, endIndex, i))
            return false;
        std::string variable = inputStr.substr(startIndex + 3, endIndex - startIndex - 1);
        long long formatIndex = findKey(formatData, variable);
        if (formatIndex == -1)
            return false;
        replace(inputStr, formatData[formatIndex].second, startIndex, endIndex);
    }
    outFile << inputStr;
    return true;
}

bool writeVariableInCycle(std::string& inputStr, const std::string& toBeReplaced,
                   const std::string& replacement, size_t startIndex,
                   size_t endIndex, std::ofstream & outFile) {
    size_t i = 0;
    while (inputStr[i] != '\0') {

        std::string variable = inputStr.substr(startIndex + 3, endIndex - startIndex - 1);
        if (variable != toBeReplaced)
            return false;
        replace(inputStr, replacement, startIndex, endIndex);
    }
    outFile << inputStr;
    return true;
}

bool writeCycle(std::vector<std::string>& splitBeg, std::string& inputStr,
                const dataVector& memberData, const formatVector& formatData,
                std::ofstream & outFile) {
    long long varIndex = findKey(formatData, splitBeg[4]);
    if (varIndex == -1)
        return false;
    size_t startIndex, endIndex;
    size_t i = 0;
    if (calcRangeToReplace(inputStr, startIndex, endIndex, i))
        return false;
    std::string variable = inputStr.substr(startIndex + 3, endIndex - startIndex - 1);
    if (variable != splitBeg[2])
        return false;
    for (int j = 0; j < memberData[varIndex]->size(); ++j) {
        replace(inputStr, memberData[varIndex][j], startIndex, endIndex);
        if (!writeVariable(inputStr, memberData, formatData, outFile))
            return false;
    }
    return true;
}