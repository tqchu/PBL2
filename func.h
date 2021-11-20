#pragma once
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
#ifndef FUNC_H
template <typename T>
void SWAP(T &t1, T &t2)
{
    T temp = t1;
    t1 = t2;
    t2 = temp;
}
template <typename T>
void sortById(T *tList, int numberOfRecords, bool (*func_ptr)(int, int))
{
    int i, j;
    for (i = 0; i < numberOfRecords - 1; i++)
    {
        for (j = 0; j < numberOfRecords - i - 1; j++)
        {
            if ((*func_ptr)(tList[j].getId(), tList[j + 1].getId()))
                SWAP(tList[j], tList[j + 1]);
            // ... to be continued
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
    return l > r;
}
template <typename T>
bool descending(T l, T r)
{
    return l < r;
}
bool ascendingDate(string l, string r)
{
    int dayL,dayR, monthL,monthR, yearL,yearR;
    dayL = stoi(l.substr(0, 2));
    dayR = stoi(r.substr(0, 2));
    monthL = stoi(l.substr(3, 5));
    monthR = stoi(r.substr(3, 5));
    yearL = stoi(l.substr(6, 10));
    yearR = stoi(r.substr(6, 10));
    if (yearL!=yearR)
        return yearL > yearR;
    else{
        if (monthL!=monthR)
            return monthL > monthR;
        else
            return dayL > dayR;
    }
}
bool descendingDate(string l, string r)
{
    int dayL, dayR, monthL, monthR, yearL, yearR;
    dayL = stoi(l.substr(0, 2));
    dayR = stoi(r.substr(0, 2));
    monthL = stoi(l.substr(3, 5));
    monthR = stoi(r.substr(3, 5));
    yearL = stoi(l.substr(6, 10));
    yearR = stoi(r.substr(6, 10));
    if (yearL != yearR)
        return yearL < yearR;
    else
    {
        if (monthL != monthR)
            return monthL < monthR;
        else
            return dayL < dayR;
    }
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

inline string getTimeFormatted(int time)
{
    if (time < 10)
        return "0" + to_string(time);
    else
        return to_string(time);
}
inline string getCurrentTime(string type)
{
    time_t t = time(0); // get time now
    tm *now = localtime(&t);
    string hour = getTimeFormatted(now->tm_hour), min = getTimeFormatted(now->tm_min), day = getTimeFormatted(now->tm_mday), month = getTimeFormatted(now->tm_mon + 1), year = to_string(now->tm_year + 1900);
    if (type == "time")
        return hour + ":" + min + " " + day + "-" + month + "-" + year;
    else
        return day + "/" + month + "/" + year;
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
