#include "readTemplate.h"
#include "stringOperations.h"

bool readTemplate(std::vector<std::string>& templateVector, formatVector& formatData,
                  std::ifstream& inFile){
    std::string input;
    while (!inFile.eof()) {
        inFile >> input;
        if (inFile.eof())
            return true;

        std::vector<std::string> splitInput = split(input, ' ');
        size_t i = 0;
        if (splitInput[0] == "{%") {
            if (!readCycle(templateVector, splitInput, formatData, inFile))
                return false;
        }
        else {
            if (!readLine(templateVector, formatData, input))
                return false;
        }
    }
    return true;
}

bool readLine(std::vector<std::string>& templateVector, const formatVector& formatData,
              const std::string& line) {
    size_t index = 0;
    size_t i = 0;
    size_t startIndex = 0;
    size_t endIndex = 0;
    size_t size = line.size();
    while(i < size) {
        if (!calcRangeToReplace(line, startIndex, endIndex, i))
            return false;

        if(startIndex == -1){
            templateVector.push_back(line.substr(endIndex, templateVector.size() - endIndex - 1));
        }

        templateVector.push_back(line.substr(index, index - startIndex));

        std::string variable = line.substr(startIndex + 3, startIndex - endIndex - 1);
        long long varIndex = findKey(formatData, variable);
        if (varIndex == -1)
            return false;

        templateVector.push_back(numToStr(varIndex));
        index = i;
    }
    return true;
}

bool readCycle(std::vector<std::string>& templateVector, std::vector<std::string> splitInput,
               formatVector& formatData, std::ifstream& inFile) {
    if (splitInput.size() != 6)
        return false;
    if (splitInput[1] != "for" || splitInput[3] != "in"|| splitInput[5] != "%}")
        return false;

    std::pair<std::string, std::string> current;
    current.first = splitInput[2];
    formatData.push_back(current);

    std::string line;
    while(true) {
        inFile >> line;
        if (inFile.eof())
            break;
        if (line == "{% endfor %}") {
            formatData.pop_back();
            return true;
        }
        if (!readLine(templateVector, formatData, line))
            return false;

    }
    formatData.pop_back();
    return false;
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

long long findKey(const formatVector& formatData, const std::string& var) {
    for (size_t i = 0; i < formatData.size(); ++i) {
        if (formatData[i].first == var)
            return i;
    }
    return -1;
}