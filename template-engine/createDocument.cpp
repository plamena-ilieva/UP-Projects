#include "createDocument.h"
#include "stringOperations.h"

void writeDocument(const strMatrix &memberData, const strMatrix &templateData,
                   const formatVector& formatData, std::ofstream &outFile) {
    size_t templateSize = templateData.size();
    size_t formatSize = formatData.size();
    for (size_t i = 0; i < templateSize; ++i) {
        if (templateData[i].size() == 1) {
            outFile << templateData[i][0];
            continue;
        }
        long long index = strToNum(templateData[i][1]);
        if (formatData[index].second == "string*")
            writeCycle(memberData, templateData, formatSize, index, i, outFile);
        else
            writeLine(memberData, templateData[i], formatSize, outFile);

    }
}

void writeLine(const strMatrix& memberData, const std::vector<std::string>& templateLine,
               size_t formatSize, std::ofstream& outFile,
               size_t indexOfData, size_t indexOfArr) {
    size_t lineSize = templateLine.size();
    for (size_t i = 0; i < lineSize; ++i) {
        if (i & 1) /* j is odd */ {
            long long index = strToNum(templateLine[i]);
            if (index >= formatSize)
                outFile << memberData[indexOfData][indexOfArr];
            else
                outFile << memberData[index][0];

        } else
            outFile << templateLine[i];
    }
    outFile << std::endl;
}
void writeCycle(const strMatrix& memberData, const strMatrix& templateData,
                size_t formatSize, size_t indexOfVar, size_t& i, std::ofstream& outFile) {
    size_t memberDataSize = memberData[indexOfVar].size();
    ++i;

    size_t currentI = 0;
    for (size_t j = 0; j < memberDataSize; ++j) {
        long long index = 0;
        currentI = i;
        while (index != -1) {

            if (templateData[currentI].size() == 1) {
                outFile << templateData[currentI][0];
                continue;
            }
            index = strToNum(templateData[currentI][1]);
            if (index == -1)
                break;
            writeLine(memberData, templateData[currentI],
                      formatSize, outFile, indexOfVar, j);
            ++currentI;

        }
    }
    i = currentI;
}