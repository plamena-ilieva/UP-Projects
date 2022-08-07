#ifndef TEMPLATE_ENGINE_READTEMPLATE_H
#define TEMPLATE_ENGINE_READTEMPLATE_H
#include <iostream>
#include <vector>
#include <fstream>
#define formatVector std::vector<std::pair<std::string, std::string>>
#define strMatrix std::vector<std::vector<std::string>>

bool readTemplate(strMatrix& templateVector, formatVector& formatData,
                  std::ifstream& inFile);
bool readLine(strMatrix& templateVector, const formatVector& formatData,
                  const std::string& line);
bool readCycle(strMatrix& templateVector, std::vector<std::string> splitInput,
               formatVector& formatData, std::ifstream& inFile);

bool calcRangeToReplace(const std::string& inputStr, size_t& startIndex,
                        size_t& endIndex, size_t& i);
long long findKey(const formatVector& formatData, const std::string& var);

#endif //TEMPLATE_ENGINE_READTEMPLATE_H
