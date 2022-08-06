#ifndef TEMPLATE_ENGINE_READTEMPLATE_H
#define TEMPLATE_ENGINE_READTEMPLATE_H
#include <iostream>
#include <vector>
#include <fstream>
#define formatVector std::vector<std::pair<std::string, std::string>>

bool readTemplate(std::vector<std::string>& templateVector, formatVector& formatData,
                  std::ifstream& inFile);
bool readLine(std::vector<std::string>& templateVector, const formatVector& formatData,
                  const std::string& line);
bool readCycle(std::vector<std::string>& templateVector, std::vector<std::string> splitInput,
               formatVector& formatData, std::ifstream& inFile);

bool calcRangeToReplace(const std::string& inputStr, size_t& startIndex,
                        size_t& endIndex, size_t& i);
long long findKey(const formatVector& formatData, const std::string& var);

#endif //TEMPLATE_ENGINE_READTEMPLATE_H
