#ifndef TEMPLATE_ENGINE_CREATEDOCUMENT_H
#define TEMPLATE_ENGINE_CREATEDOCUMENT_H

#include <iostream>
#include <vector>
#include <fstream>
#define dataVector std::vector<std::string*>
#define formatVector std::vector<std::pair<std::string, std::string>>

bool writeMember(const dataVector& memberData, const formatVector& formatData, std::ifstream& inFile,std::ofstream & outFile);
long long findKey(const formatVector& formatData, const std::string& var);
#endif //TEMPLATE_ENGINE_CREATEDOCUMENT_H
