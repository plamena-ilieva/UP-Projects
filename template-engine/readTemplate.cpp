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
* <cpp file with functions that read the data from the template>
*
*/

#include "readTemplate.h"
#include "stringOperations.h"

const short SIZE = 1024;

/** a function hat reads the whole template
 * returns false if the template is not in the expected format */
bool readTemplate(strMatrix &templateVector, formatVector &formatData,
                  std::ifstream &inFile) {
    char inputLine[SIZE];
    while (!inFile.eof()) {
        inFile.getline(inputLine, SIZE);
        if (inFile.eof())
            return true;

        std::string input(inputLine);
        std::vector<std::string> splitInput = split(input, ' ');
        size_t i = 0;
        /** if the line starts with "{%", a cycle will begin
         * otherwise a single line is read */
        if (splitInput[0] == "{%") {
            if (!readCycle(templateVector, splitInput, formatData, inFile))
                return false;
        } else {
            if (!readLine(templateVector, formatData, input))
                return false;
        }
    }
    return true;
}

/** a function hat reads a single line
 * returns false if the template is not in the expected format */
bool readLine(strMatrix &templateVector, const formatVector &formatData,
              const std::string &line) {
    size_t index = 0;
    size_t i = 0;
    size_t startIndex = 0;
    size_t endIndex = 0;
    size_t lineSize = line.size();
    size_t templateSize = templateVector.size();
    templateVector.push_back(std::vector<std::string>());

    while (i < lineSize) {
        /** we find the position of the variable name
         * if we have "{{", but no "}}", the template is incorrect */
        if (!calcRangeToReplace(line, startIndex, endIndex, i))
            return false;

        /** if startIndex is -1, there is noting to be replaced */
        if (startIndex == -1) {
            templateVector[templateSize].push_back(line.substr
                    (endIndex, templateVector.size() - endIndex - 1));
            break;
        }
        /** first we write the text that should not be replaced (they will always be on an
         * even index, then the index of the variable to be replaced (always on an odd index)
         */
        templateVector[templateSize].push_back(line.substr(index, startIndex - index));

        std::string variable = line.substr(startIndex + 3, endIndex - startIndex - 6);
        long long varIndex = findKey(formatData, variable);
        /** if the variable name does not exist, template is incorrect */
        if (varIndex == -1)
            return false;

        templateVector[templateSize].push_back(numToStr(varIndex));
        index = i;
    }
    return true;
}

/** a function hat reads a cycle
 * returns false if the template is not in the expected format */
bool readCycle(strMatrix &templateVector, std::vector<std::string> splitInput,
               formatVector &formatData, std::ifstream &inFile) {
    /** the right format is "{% for new_variable in variable_array %}" */
    if (splitInput.size() != 6)
        return false;
    if (splitInput[1] != "for" || splitInput[3] != "in" || splitInput[5] != "%}")
        return false;

    /** we check whether the array name exists */
    long long index = findKey(formatData, splitInput[4]);
    if (index == -1)
        return false;

    size_t templateSize = templateVector.size();
    templateVector.push_back(std::vector<std::string>());
    /** we add an empty string first so that the index is on an odd position */
    templateVector[templateSize].push_back("");
    templateVector[templateSize].push_back(numToStr(index));

    /** we add the name of the variable that is expected in the cycle, so that we can check
     * whether it is on the next lines, then we delete it after the enf of the cycle
     */
    std::pair<std::string, std::string> current;
    current.first = splitInput[2];
    formatData.push_back(current);

    char line[SIZE];
    while (true) {
        inFile.getline(line, SIZE);
        if (inFile.eof())
            break;
        templateSize++;

        std::string lineStr(line);
        /** if this line is reached, the cycle is complete
         * the index -1 is indicator for it, again on an odd position
         */
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
    /** if the line "{% endfor %}" is not reached, the template is incorrect */
    formatData.pop_back();
    return false;
}

/** a function that calculates the range where the name of the variable is */
bool calcRangeToReplace(const std::string &inputStr, size_t &startIndex,
                        size_t &endIndex, size_t &i) {
    startIndex = findThreeSymbols(inputStr, '{', '{', ' ', i);
    if (startIndex == -1) {
        return true;
    }

    endIndex = findThreeSymbols(inputStr, ' ', '}', '}', i) + 3;
    if (endIndex == -1)
        return false;
    return true;
}

/** a function that finds whether a string is a variable name in the format */
long long findKey(const formatVector &formatData, const std::string &var) {
    for (size_t i = 0; i < formatData.size(); ++i) {
        if (formatData[i].first == var)
            return i;
    }
    return -1;
}