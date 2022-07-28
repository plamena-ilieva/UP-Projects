#ifndef TEMPLATE_ENGINE_READDATA_H
#define TEMPLATE_ENGINE_READDATA_H

#include <iostream>
#include <vector>
#include <fstream>

#define formatVector std::vector<std::pair<std::string, std::string>>
#define dataVector std::vector<std::string*>

void readFormat(formatVector& formatData, std::ifstream& inFile);
void readMember(dataVector& memberData, const formatVector& formatData, std::ifstream& inFile);

#endif //TEMPLATE_ENGINE_READDATA_H
