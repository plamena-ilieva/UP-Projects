#include "readTemplate.h"
#include "stringOperations.h"
const short SIZE = 1024;
bool readTemplate(strMatrix& templateVector, formatVector& formatData,
                  std::ifstream& inFile){
    char inputLine[SIZE];
    while (!inFile.eof()) {
        inFile.getline(inputLine, SIZE);
        if (inFile.eof())
            return true;

        std::string input(inputLine);
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

bool readLine(strMatrix& templateVector, const formatVector& formatData,
              const std::string& line) {
    size_t index = 0;
    size_t i = 0;
    size_t startIndex = 0;
    size_t endIndex = 0;
    size_t lineSize = line.size();
    size_t templateSize = templateVector.size();
    templateVector.push_back(std::vector<std::string>());

    while(i < lineSize) {
        if (!calcRangeToReplace(line, startIndex, endIndex, i))
            return false;

        if(startIndex == -1){
            templateVector[templateSize].push_back(line.substr
            (endIndex, templateVector.size() - endIndex - 1));
            break;
        }

        templateVector[templateSize].push_back(line.substr(index, startIndex - index));

        std::string variable = line.substr(startIndex + 3, endIndex - startIndex - 6);
        long long varIndex = findKey(formatData, variable);
        if (varIndex == -1)
            return false;

        templateVector[templateSize].push_back(numToStr(varIndex));
        index = i;
    }
    return true;
}

bool readCycle(strMatrix& templateVector, std::vector<std::string> splitInput,
               formatVector& formatData, std::ifstream& inFile) {
    if (splitInput.size() != 6)
        return false;
    if (splitInput[1] != "for" || splitInput[3] != "in"|| splitInput[5] != "%}")
        return false;

    long long index = findKey(formatData, splitInput[4]);
    if (index == -1)
        return false;

    size_t templateSize = templateVector.size();
    templateVector.push_back(std::vector<std::string>());
    templateVector[templateSize].push_back("");
    templateVector[templateSize].push_back(numToStr(index));

    std::pair<std::string, std::string> current;
    current.first = splitInput[2];
    formatData.push_back(current);

    char line[SIZE];
    while(true) {
        inFile.getline(line, SIZE);
        if (inFile.eof())
            break;
        templateSize++;

        std::string lineStr(line);
        if (lineStr == "{% endfor %}") {
            formatData.pop_back();
            templateVector.push_back(std::vector<std::string>());
            templateVector[templateSize].push_back("");
            templateVector[templateSize].push_back(numToStr(-1));
            return true;
        }
        if (!readLine(templateVector, formatData, lineStr))
            return false;

    }
    formatData.pop_back();
    return false;
}

bool calcRangeToReplace(const std::string& inputStr, size_t& startIndex,
                        size_t& endIndex, size_t& i) {
    startIndex = findThreeSymbols(inputStr, '{', '{', ' ',i);
    if (startIndex == -1) {
        return true;
    }

    endIndex = findThreeSymbols(inputStr, ' ', '}', '}', i) + 3;
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