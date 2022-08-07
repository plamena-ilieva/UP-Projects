#ifndef TEMPLATE_ENGINE_CREATEDOCUMENT_H
#define TEMPLATE_ENGINE_CREATEDOCUMENT_H

#include <iostream>
#include <vector>
#include <fstream>
#define dataVector std::vector<std::string*>
#define formatVector std::vector<std::pair<std::string, std::string>>

void writeDocument(const dataVector& memberData, const std::vector<std::string>& templateData,
                   std::ofstream& outFile);

#endif //TEMPLATE_ENGINE_CREATEDOCUMENT_H
