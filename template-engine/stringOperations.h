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
* <header file with helper string functions>
*
*/

#ifndef TEMPLATE_ENGINE_STRINGOPERATIONS_H
#define TEMPLATE_ENGINE_STRINGOPERATIONS_H
#include <iostream>
#include <vector>

std::vector<std::string> split(const std::string&, char);
long long findThreeSymbols(const std::string&, char first, char second, char third, size_t& i);
long long strToNum(const std::string& str);
std::string numToStr(long long num);
size_t calcNumSize(long long num);

#endif //TEMPLATE_ENGINE_STRINGOPERATIONS_H
