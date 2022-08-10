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
* <header file with functions that read the data from the database>
*
*/
#ifndef TEMPLATE_ENGINE_READDATA_H
#define TEMPLATE_ENGINE_READDATA_H

#include <iostream>
#include <vector>
#include <fstream>

#define formatVector std::vector<std::pair<std::string, std::string>>
#define strMatrix std::vector<std::vector<std::string>>

void readFormat(formatVector &formatData, std::ifstream &inFile);

void readMember(strMatrix &memberData, const formatVector &formatData, std::ifstream &inFile);

#endif //TEMPLATE_ENGINE_READDATA_H
