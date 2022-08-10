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
* <cpp file with helper string functions>
*
*/

#include "stringOperations.h"

/** a functions that turns a string into a vector that contains all ste substrings
 * separated by a given symbol */
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

/** a function that finds 3 subsequent symbols */
long long findThreeSymbols(const std::string &str, char first, char second, char third, size_t &i) {
    for (; i < str.size() - 2; ++i) {
        if (str[i] == first && str[i + 1] == second && str[i + 2] == third) {
            i += 3;
            return i - 3;
        }
    }
    return -1;
}

/** a function that turns a string into a number */
long long strToNum(const std::string &str) {
    size_t num = 0;
    size_t counter = 1;
    size_t size = str.size();
    size_t i = (str[0] == '-') ? 1 : 0;

    for (; i < size; ++i) {
        num += (str[i] - '0') * counter;
        counter *= 10;
    }
    if (str[0] == '-')
        num *= -1;
    return num;
}

/** a function that turns a number into a string */
std::string numToStr(long long num) {
    size_t size = calcNumSize(num);
    if (num >= 0) {
        char *str = new char[size + 1];
        for (int i = size - 1; i >= 0; --i) {
            str[i] = (num % 10) + '0';
            num /= 10;
        }
        str[size] = '\0';
        std::string string(str);
        delete[] str;
        return string;
    } else {
        char *str = new char[size + 2];
        num *= -1;
        for (int i = size; i >= 1; --i) {
            str[i] = (num % 10) + '0';
            num /= 10;
        }
        str[size + 1] = '\0';
        str[0] = '-';
        std::string string(str);
        delete[] str;
        return string;
    }
}

/** a function that finds the length of a number */
size_t calcNumSize(long long num) {
    size_t size = 1;
    while (num > 9) {
        num /= 10;
        ++size;
    }
    return size;
}