#pragma once
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
#ifndef FUNC_H

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
inline string getData(string& dataText){
        // loại bỏ các phím Tab
        int tabCount;
        for(tabCount=0;tabCount<50;tabCount++){
            if (dataText[tabCount]=='\t') {
                while (dataText[tabCount]=='\t')
                {
                    tabCount++;
                }
                break;
            };
        }
        // chuyển tab của materialText
        dataText=dataText.substr(tabCount,dataText.length()-tabCount+1);
        // đếm số kí tự của dữ liệu
        int dataCount;
        for(dataCount=0;dataCount<50;dataCount++){
            if (dataText[dataCount]=='\t') break;
        }
         // return dữ liệu
        return dataText.substr(0,dataCount);
}
// lấy số kí tự của một số unsigned long
inline int getLength(unsigned long data){
    return to_string(data).length();
}
// chèn những tab còn lại cho đủ size của cột ( len là số kí tự của chuỗi dữ liệu)
inline void insertTab(ofstream& out,int columnSize,int len){
    for(int i=0;i<columnSize-len/8;i++) out<<"\t";
}

inline string getTimeFormatted(int time)
{
    if (time < 10)
        return "0" + to_string(time);
    else
        return to_string(time);
}
inline string getCurrentTime(string type){
    time_t t = time(0); // get time now
    tm *now = localtime(&t);
    string hour = getTimeFormatted(now->tm_hour), min = getTimeFormatted(now->tm_min), day = getTimeFormatted(now->tm_mday), month = getTimeFormatted(now->tm_mon + 1), year = to_string(now->tm_year + 1900);
    if (type=="time")
        return hour + ":" + min + " " + day + "-" + month + "-" + year;
    else
        return day + "/" + month + "/" + year;
}
#endif
