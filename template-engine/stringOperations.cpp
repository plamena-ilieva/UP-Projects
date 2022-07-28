#include "stringOperations.h"

std::vector<std::string> split(const std::string& str, char symbol) {
    std::vector<std::string> result;
    size_t startIndex = 0;
    size_t endIndex = 0;
    size_t i = 0;
    while(str[i] != '\0') {
        while(str[i] != '\0' && str[i] != symbol) {
            ++i;
        }
        endIndex = i;
        result.push_back(str.substr(startIndex, endIndex - startIndex));
        startIndex = endIndex + 1;
        if (str[i] == '\0')
            break;
        ++i;
    }
    return result;
}

void replace(std::string& toBeReplaced, const std::string& newStr, size_t startIndex, size_t endIndex) {
    std::string result = toBeReplaced.substr(0, startIndex);
    result += newStr;
    result += toBeReplaced.substr(startIndex, endIndex - startIndex);
    toBeReplaced = result;
}