#pragma once
#include "CustomException.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <regex>
using namespace std;
#ifndef FUNC_H

unsigned long toNumber(string str, string field)
{
    string numberRegex = "[0-9]+";
    if (!regex_match(str, regex(numberRegex)))
    {
        string subString = str.substr(1, str.length());
        if ((str[0] = '-') && (regex_match(subString, regex(numberRegex))))
        {
            throw negative_number(field);
        }
        else
            throw invalid_input("so");
    }
    else
        return stoul(str);
}
template <typename T>
void SWAP(T &t1, T &t2)
{
    T temp = t1;
    t1 = t2;
    t2 = temp;
}

void sortCategoryByPercentage(int *arr, double *percentage, int n, bool (*func_ptr)(double, double))
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if ((*func_ptr)(percentage[arr[j]], percentage[arr[j + 1]]))
                SWAP(arr[j], arr[j + 1]);
        }
    }
}
void sortByPercentage(int *arr, double *percentage, int n, bool (*func_ptr)(double, double))
{
    int i, j;
    for (i = 1; i < n - 1; i++)
    {
        for (j = 1; j < n - i - 1; j++)
        {
            if ((*func_ptr)(percentage[arr[j]], percentage[arr[j + 1]]))
                SWAP(arr[j], arr[j + 1]);
        }
    }
}
template <typename T>
void sortByName(T *tList, int numberOfRecords, bool (*func_ptr)(string, string))
{
    int i, j;
    for (i = 0; i < numberOfRecords - 1; i++)
    {
        for (j = 0; j < numberOfRecords - i - 1; j++)
        {
            if ((*func_ptr)(tList[j].getName(), tList[j + 1].getName()))
                SWAP(tList[j], tList[j + 1]);
        }
    }
}
template <typename T>
bool ascending(T l, T r)
{
    return l >= r;
}
template <typename T>
bool descending(T l, T r)
{
    return l < r;
}
template <typename T>
int getNextId(T *tList, int numberOfRecords)
{
    int max = 0;
    for (int i = 0; i < numberOfRecords; i++)
    {
        int id = tList[i].getId();
        if (id > max)
            max = id;
    }
    return max + 1;
}
template <typename T>
int getNumberOfRecords(T *list, int maxRecords)
{
    int numberOfRecords;
    for (numberOfRecords = 0; numberOfRecords < maxRecords; numberOfRecords++)
    {
        if (list[numberOfRecords].getId() == 0)
            break;
    }
    return numberOfRecords;
}
inline string getData(string &dataText)
{
    // loại bỏ các phím Tab
    int tabCount;
    for (tabCount = 0; tabCount < 50; tabCount++)
    {
        if (dataText[tabCount] == '\t')
        {
            while (dataText[tabCount] == '\t')
            {
                tabCount++;
            }
            break;
        };
    }
    // chuyển tab của materialText
    dataText = dataText.substr(tabCount, dataText.length() - tabCount + 1);
    // đếm số kí tự của dữ liệu
    int dataCount;
    for (dataCount = 0; dataCount < 50; dataCount++)
    {
        if (dataText[dataCount] == '\t')
            break;
    }
    // return dữ liệu
    return dataText.substr(0, dataCount);
}
// lấy số kí tự của một số unsigned long
inline int getLength(unsigned long data)
{
    return to_string(data).length();
}
// chèn những tab còn lại cho đủ size của cột ( len là số kí tự của chuỗi dữ liệu)
inline void insertTab(ofstream &out, int columnSize, int len)
{
    for (int i = 0; i < columnSize - len / 8; i++)
        out << "\t";
}
inline string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}
inline bool isEqual(string first_string, string second_string)
{
    string first = toLower(first_string);
    string second = toLower(second_string);
    return (first == second);
}
#endif