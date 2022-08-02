#ifndef TEMPLATE_ENGINE_STRINGOPERATIONS_H
#define TEMPLATE_ENGINE_STRINGOPERATIONS_H
#include <iostream>
#include <vector>

std::vector<std::string> split(const std::string&, char);
void replace(std::string&, const std::string&, size_t, size_t);
long long findThreeSymbols(const std::string&, char first, char second, char third, size_t& i);

#endif //TEMPLATE_ENGINE_STRINGOPERATIONS_H
