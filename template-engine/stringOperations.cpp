#include "stringOperations.h"

std::vector<std::string> split(const std::string &str, char symbol) {
    std::vector<std::string> result;
    size_t startIndex = 0;
    size_t endIndex = 0;
    size_t i = 0;
    while (str[i] != '\0') {
        while (str[i] != '\0' && str[i] != symbol) {
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

std::vector<std::string> split(const std::string& str, const std::string& splitStr) {
    std::vector<std::string> result;
    size_t startIndex = 0;
    size_t endIndex = 0;
    size_t i = 0;
    bool split = true;
    while (str[i] != '\0') {
        while (str[i] != '\0' && str[i] != splitStr[0]) {
            ++i;
        }
        if (str[i] == splitStr[0]) {
            size_t j = 1;
            ++i;
            while (splitStr[j] != '\0') {

            }
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

void replace(std::string &toBeReplaced, const std::string &newStr, size_t startIndex, size_t endIndex) {
    if (startIndex == -1)
        return;
    std::string result = toBeReplaced.substr(0, startIndex);
    result += newStr;
    result += toBeReplaced.substr(startIndex, endIndex - startIndex);
    toBeReplaced = result;
}

long long findThreeSymbols(const std::string &str, char first, char second, char third, size_t &i) {
    for (; i < str.size() - 2; ++i) {
        if (str[i] == first && str[i + 1] == second && str[i + 2] == third) {
            i += 3;
            return i - 3;
        }
    }
    return -1;
}

size_t strToNum(const std::string& str) {
    size_t num = 0;
    size_t counter = 1;
    size_t size = str.size();

    for (size_t i = 0; i < size; ++i) {
        num += (str[i] - '0')*counter;
        counter *= 10;
    }
    return num;
}
std::string numToStr(size_t num) {
    size_t size = calcNumSize(num);
    char* str = new char[size+1];
    for (int i = size-1; i >= 0; --i) {
        str[i] = (num % 10) + '0';
        num /= 10;
    }
    str[size] = '\0';
    std::string string(str);
    return string;
}

size_t calcNumSize(size_t num) {
    size_t size = 1;
    while(num>9){
        num /= 10;
        ++size;
    }
    return size;
}