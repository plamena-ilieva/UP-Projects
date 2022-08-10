#ifndef TEMPLATE_ENGINE_STRINGOPERATIONS_H
#define TEMPLATE_ENGINE_STRINGOPERATIONS_H
#include <iostream>
#include <vector>

std::vector<std::string> split(const std::string&, char);
std::vector<std::string> split(const std::string&, const std::string&);
void replace(std::string&, const std::string&, size_t, size_t);
long long findThreeSymbols(const std::string&, char first, char second, char third, size_t& i);
long long strToNum(const std::string& str);
std::string numToStr(long long num);
size_t calcNumSize(long long num);

#endif //TEMPLATE_ENGINE_STRINGOPERATIONS_H
