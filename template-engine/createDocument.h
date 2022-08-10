#ifndef TEMPLATE_ENGINE_CREATEDOCUMENT_H
#define TEMPLATE_ENGINE_CREATEDOCUMENT_H

#include <iostream>
#include <vector>
#include <fstream>
#define dataVector std::vector<std::string*>
#define formatVector std::vector<std::pair<std::string, std::string>>
#define strMatrix std::vector<std::vector<std::string>>

void writeDocument(const strMatrix& memberData, const strMatrix& templateData,
                   const formatVector& formatData, std::ofstream& outFile);
void writeLine(const strMatrix& memberData, const std::vector<std::string>& templateLine,
               size_t formatSize, std::ofstream& outFile,
               size_t indexOfData = 0, size_t indexOfArr = 0);
void writeCycle(const strMatrix& memberData, const strMatrix& templateData,
                size_t formatSize, size_t indexOfVar, size_t& i, std::ofstream& outFile);

#endif //TEMPLATE_ENGINE_CREATEDOCUMENT_H
