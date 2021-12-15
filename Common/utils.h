#ifndef UTILS_H
#define UTILS_H
#include "iomanip"
#include "CustomException.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <regex>
using namespace std;
#define lineWidth 126

unsigned long getOriginalPrice(unsigned long price)
{
    int TR = 1000000;
    unsigned long originalPrice = price;
    if ((price >= 0.99 * TR) && (price < 1.98 * TR))
    {
        originalPrice = price * (double)100 / 99;
    }
    else if ((price >= 1.96 * TR) && (price < 4.9 * TR))
    {
        originalPrice = price * (double)100 / 98;
    }
    else if ((price >= 4.85 * TR) && (price < 9.7 * TR))
    {
        originalPrice = price * (double)100 / 97;
    }
    else if (price >= 9.5 * TR)
    {
        originalPrice = price * (double)100 / 95;
    }
    return originalPrice;
}

unsigned long getDiscount(unsigned long totalWithoutDiscount)
{

    int TR = 1000000;
    unsigned long discount = 0;
    if ((totalWithoutDiscount >= 1 * TR) && (totalWithoutDiscount < 2 * TR))
    {
        discount = totalWithoutDiscount * 1 / 100;
    }
    else if ((totalWithoutDiscount >= 2 * TR) && (totalWithoutDiscount < 5 * TR))
    {
        discount = totalWithoutDiscount * 2 / 100;
    }
    else if ((totalWithoutDiscount >= 5 * TR) && (totalWithoutDiscount <= 10 * TR))
    {
        discount = totalWithoutDiscount * 3 / 100;
    }
    else if (totalWithoutDiscount >= 10 * TR)
        discount = totalWithoutDiscount * 5 / 100;
    return discount;
}

/** 
 * loại bỏ khoảng trắng không cần thiết ở phía trước và phía sau chuỗi
 * @param str chuỗi cần trim
 * @return chuỗi sau khi trim
*/
string trim(string str)
{

    int length = str.length();
    int i = 0, j = length;
    if (str[0] == ' ')
    {
        for (i = 1; i < length; i++)
        {
            if (str[i] != ' ')
                break;
        }
    }
    if (str[length - 1] == ' ')
    {

        for (j = length - 2; j >= 0; j--)
        {
            if (str[j] != ' ')
                break;
        }
    }
    return str.substr(i, j - i + 1);
}

/* 
 * Chuyển chuỗi thành Number
 * @param str chuỗi cần chuyển
 * @param field field của chuỗi cần chuyển để tạo message của exception
 * @return số sau khi chuyển
 * @throw negative_number 
 * @throw invalid_input 
*/
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

/*
 * phân tích chuỗi từ file thành data
*/
string getData(string &dataText)
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

/** 
 * @return số kí tự của 1 số
*/
int getLength(unsigned long data)
{
    return to_string(data).length();
}

// chèn những tab còn lại cho đủ size của cột ( len là số kí tự của chuỗi dữ liệu)
void insertTab(ofstream &out, int columnSize, int len)
{
    for (int i = 0; i < columnSize - len / 8; i++)
        out << "\t";
}

string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}
/*
 * so sánh 2 chuỗi (non_case_sensitive)
*/
bool isEqual(string first_string, string second_string)
{
    string first = toLower(first_string);
    string second = toLower(second_string);
    return (first == second);
}

void printUnderscore(int n)
{
    int indent = (lineWidth - n) / 2;
    for (int i = 0; i < indent; i++)
        cout << " ";
    for (int i = 0; i < n; i++)
    {
        cout << "_";
    }
    cout << endl
         << endl;
}
void printHyphen(int n)
{
    int indent = (lineWidth - n) / 2;
    for (int i = 0; i < indent; i++)
        cout << " ";
    for (int i = 0; i < n; i++)
    {
        cout << "-";
    }
    cout << endl;
}
void printBox(string title)
{
    printUnderscore(lineWidth);
    cout << endl;
    int length = title.length();
    int indent = (lineWidth - length) / 2;
    for (int i = 0; i < indent; i++)
    {
        cout << " ";
    }
    cout << title << endl;
    printHyphen(40);
    cout << endl;
}
void printTitle(string title)
{
    int length = title.length();
    int indent = (lineWidth - length) / 2;
    for (int i = 0; i < indent; i++)
    {
        cout << " ";
    }
    cout << title << endl;
    cout << endl;
}

void introduce()
{
    printUnderscore(lineWidth);

    printTitle("DO AN CO SO LAP TRINH PBL2 ");
    printTitle("DE TAI : QUAN LY VAT TU ");
    printHyphen(lineWidth * 2 / 3);
    cout << endl;
    printTitle("GIAO VIEN HUONG DAN: ThS. DO THI TUYET HOA");
    printTitle("SINH VIEN THUC HIEN: TRUONG QUANG CHU     ");
    printTitle("                     NGUYEN VAN VUONG     ");
}

void printMenu()
{
    printBox("HE THONG QUAN LY VAT TU");
    printHyphen(lineWidth);
    cout << setw(2) << "";
    cout << setw(30) << left << "0. Thoat chuong trinh";
    cout << setw(20) << left << "1. Quan ly VT";
    cout << setw(30) << "2. Quan ly nha san xuat";
    cout << setw(25) << "3. Quan ly loai VT";
    cout << "4. Quan ly hoa don " << endl;
    printHyphen(lineWidth);
    cout << endl;
}
void sayBye()
{
    printUnderscore(lineWidth);
    cout << endl;
    printTitle("CHUONG TRINH KET THUC!");
    printTitle("CAM ON THAY CO VA CAC BAN DA THEO DOI");
    printUnderscore(lineWidth);
}
#endif