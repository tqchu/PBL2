#pragma once
#include <iostream>
#include <regex>
#include "CustomException.h"
using namespace std;

int getNumberOfDays(int month, int year)
{
    int numberOfDays[] = {
        0,
        31,
        28,
        31,
        30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
        numberOfDays[2] = 29;
    return numberOfDays[month];
}
string getTimeFormatted(int time, int expectedLength)
{
    string timeString = to_string(time);
    int timeStringLength = timeString.length();
    if (timeStringLength != expectedLength)
    {

        int difference = expectedLength - timeStringLength;
        for (int i = 0; i < difference; i++)
        {
            timeString = "0" + timeString;
        }
    }
    return timeString;
}

class Date
{   protected:
    int day, month, year;

public:
    // khởi tạo mặc định, khởi tạo với số ,với chuỗi, chuyển chuỗi thành ngày
    Date()
    {
        day = 1;
        month = 1;
        year = 1111;
    }
    Date(int day, int month, int year) : day(day), month(month), year(year){};
    Date(string dateString)
    {
    }
    static Date toDate(string dateString)
    {
        string dateRegex = "[0-9]{2}/[0-9]{2}/[0-9]{4}";
        if (!regex_match(dateString, regex(dateRegex)))
            throw invalid_input("ngay");
        int day = stoi(dateString.substr(0, 2));
        int month = stoi(dateString.substr(3, 5));
        int year = stoi(dateString.substr(6, 10));
        return Date(day, month, year);
    }
    static Date now()
    {
        time_t t = time(0); // get time now
        tm *now = localtime(&t);
        return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    }
    bool operator>(Date &date)
    {
        
        return (this->getDateInYMD().compare(date.getDateInYMD())==1);
    }

    bool operator<(Date &date)
    {
        return (this->getDateInYMD().compare(date.getDateInYMD()) == -1);
    }
    bool operator==(const Date &date)
    {
        return ((this->year == date.year) && (this->month == date.month) && (this->day == date.day));
    }
    string getDateInYMD(){
        string day = getTimeFormatted(this->day, 2);
        string month = getTimeFormatted(this->month, 2);
        string year = getTimeFormatted(this->year, 4);
        return year + "/" + month + "/" + day;
    }
    void toDateOfLast(int numberOfDay, int numberOfMonth, int numberOfYear)
    {
        // year
        this->year -= numberOfYear;

        // month
        if (numberOfMonth >= this->month)
        {
            this->month = this->month + 12 - numberOfMonth;
            this->year--;
        }
        else
            this->month -= numberOfMonth;

        // day
        if (numberOfDay >= this->day)
        {
            // month= 1
            if (this->month == 1)
            {
                this->month = 12;
                this->year--;
                this->day = this->day + getNumberOfDays(12, this->year) - numberOfDay;
            }
            else
            {
                this->day = this->day + getNumberOfDays(--this->month, this->year) - numberOfDay;
            }
        }
        else
            this->day -= numberOfDay;
    }
    friend ostream &operator<<(ostream &out, Date &date)
    {
        string d, m, y;
        d = getTimeFormatted(date.day, 2);
        m = getTimeFormatted(date.month, 2);
        y = getTimeFormatted(date.year, 4);
        out << d << "/" << m << "/" << y;
        return out;
    }
};
class Time:public Date{
    int hour;
    int minute;
    public:
        Time(int minute, int hour, int day, int month, int year) : Date(day, month, year), hour(hour), minute(minute){};
        static Time now(){
            time_t t = time(0); // get time now
            tm *now = localtime(&t);
            return Time(now->tm_min,now->tm_hour,now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
        }
        Date getDate(){
            return Date(this->day, this->month, this ->year);
        }
        string getDateInYMDHM()
        {
            string day = getTimeFormatted(this->day, 2);
            string month = getTimeFormatted(this->month, 2);
            string year = getTimeFormatted(this->year, 4);
            string hour = getTimeFormatted(this->hour, 2);
            string minute = getTimeFormatted(this->minute, 2);
            return year + "/" + month + "/" + day+" "+hour+":"+minute;
        }
        bool operator>(Time &time)
        {
            return this->getDateInYMDHM().compare(time.getDateInYMDHM())==1;
        }

        bool operator<(Time &time)
        {
            return this->getDateInYMDHM().compare(time.getDateInYMDHM()) == 1;
        }
        bool operator==(const Time &time)
        {
            return ((this->year == time.year) && (this->month == time.month) && (this->day == time.day))&&(this->hour==time.hour)&&(this->minute==time.minute);
        }
        friend ostream &operator<<(ostream &out, Time &time)
        {
            string d, m, y,h,min;
            d = getTimeFormatted(time.day, 2);
            m = getTimeFormatted(time.month, 2);
            y = getTimeFormatted(time.year, 4);
            h = getTimeFormatted(time.hour, 2);
            min = getTimeFormatted(time.minute, 2);
            out <<h<< ":"<<min<<" "<<d << "/" << m << "/" << y;
            return out;
        }
};
