/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Plamena Ilieva
* @idnumber 6MI0600020
* @compiler GCC
*
* <cpp file with functions that write the data into a document>
*
*/

#include "createDocument.h"
#include "stringOperations.h"

/** a function hat writes the whole document */
void writeDocument(const strMatrix &memberData, const strMatrix &templateData,
                   const formatVector &formatData, std::ofstream &outFile) {
    size_t templateSize = templateData.size();
    size_t formatSize = formatData.size();
    for (size_t i = 0; i < templateSize; ++i) {
        /** if there is only one element in a row, it means nothing should be replaced */
        if (templateData[i].size() == 1) {
            outFile << templateData[i][0];
            continue;
        }
        /** the first index could either be a single string that should be replaced once,
         * or indicate that a cycle follows */
        long long index = strToNum(templateData[i][1]);
        if (formatData[index].second == "string*")
            writeCycle(memberData, templateData, formatSize, index, i, outFile);
        else
            writeLine(memberData, templateData[i], formatSize, outFile);

    }
}

/** a function that writes a single line **/
void writeLine(const strMatrix &memberData, const std::vector<std::string> &templateLine,
               size_t formatSize, std::ofstream &outFile,
               size_t indexOfData, size_t indexOfArr) {
    size_t lineSize = templateLine.size();
    for (size_t i = 0; i < lineSize; ++i) {
        /** all indexes indicating the variable that should be put are on an odd  position */
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

/** a function hat writes a cycle */
void writeCycle(const strMatrix &memberData, const strMatrix &templateData,
                size_t formatSize, size_t indexOfVar, size_t &i, std::ofstream &outFile) {
    size_t memberDataSize = memberData[indexOfVar].size();
    ++i;

    size_t currentI = 0;
    /** for each member in the list, the data is put in the same way */
    for (size_t j = 0; j < memberDataSize; ++j) {
        /** index indicate the index read from the template, i - the row where
         * we start putting variables from an array, currentI - the row we are at
         */

        long long index = 0;
        currentI = i;

        while (true) {

            if (templateData[currentI].size() == 1) {
                outFile << templateData[currentI][0];
                continue;
            }
            index = strToNum(templateData[currentI][1]);
            /** if index is -1, the end of the cycle is reached */
            if (index == -1)
                break;
            writeLine(memberData, templateData[currentI],
                      formatSize, outFile, indexOfVar, j);
            ++currentI;

        }
    }
    i = currentI;
}