#ifndef TEMPLATE_ENGINE_CREATEDOCUMENT_H
#define TEMPLATE_ENGINE_CREATEDOCUMENT_H

#include <iostream>
#include <vector>
#include <fstream>
#define dataVector std::vector<std::string*>
#define formatVector std::vector<std::pair<std::string, std::string>>

bool writeMember(const dataVector& memberData, const formatVector& formatData,
                 std::ifstream& inFile,std::ofstream & outFile);
long long findKey(const formatVector& formatData, const std::string& var);
bool writeVariable(std::string& inputStr, const dataVector& memberData,
                   const formatVector& formatData, std::ofstream & outFile);
bool writeVariableInCycle(std::string& inputStr, const std::string& toBeReplaced,
                   const std::string& replacement, std::ofstream & outFile);
bool writeCycle(std::vector<std::string>& splitBeg,std::string& inputStr,
                const dataVector& memberData, const formatVector& formatData,
                std::ofstream & outFile);
bool calcRangeToReplace(const std::string& inputStr, size_t& startIndex,
                        size_t& endIndex, size_t& i);
#endif //TEMPLATE_ENGINE_CREATEDOCUMENT_H
