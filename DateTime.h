#ifndef DATETIME_H
#define DATETIME_H
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
        this->day = stoi(dateString.substr(0, 2));
        this->month = stoi(dateString.substr(3, 5));
        this->year = stoi(dateString.substr(6, 10));
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
    // "dmy" || "ymd"
    string toString(string format) const{
        string day = getTimeFormatted(this->day, 2);
        string month = getTimeFormatted(this->month, 2);
        string year = getTimeFormatted(this->year, 4);
        if (format=="dmy")
            return day + "/" + month + "/" + year;
        return year + "/" + month + "/" + day;
    }
    bool operator>(const Date &date) const
    {
        
        return (this->toString("ymd").compare(date.toString("ymd"))==1);
    }

    bool operator<(const Date &date) const
    {
        return (this->toString("ymd").compare(date.toString("ymd")) == -1);
    }
    bool operator>=(Date &date)
    {
        
        return (this->toString("ymd").compare(date.toString("ymd"))>=0);
    }

    bool operator<=(Date &date)
    {
        return (this->toString("ymd").compare(date.toString("ymd")) <= 0);
    }
    bool operator==(const Date &date)
    {
        return ((this->year == date.year) && (this->month == date.month) && (this->day == date.day));
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
        Time(){};
        Time(int minute, int hour, int day, int month, int year) : Date(day, month, year), hour(hour), minute(minute){};
        Time(string timeString){
            this->hour = stoi(timeString.substr(0, 2));
            this->minute = stoi(timeString.substr(3, 5));
            this->day = stoi(timeString.substr(6, 8));
            this->month = stoi(timeString.substr(9, 11));
            this->year = stoi(timeString.substr(12, 16));
        }
        static Time now(){
            time_t t = time(0); // get time now
            tm *now = localtime(&t);
            return Time(now->tm_min,now->tm_hour,now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
        }

        static Time toTime(string timeString)
        {
            string timeRegex = "[0-9]{2}:[0-9]{2} [0-9]{2}/[0-9]{2}/[0-9]{4}";
            if (!regex_match(timeString, regex(timeRegex)))
                throw invalid_input("thoi gian");
            int hour = stoi(timeString.substr(0, 2));
            int minute = stoi(timeString.substr(3, 5));
            int day = stoi(timeString.substr(6, 8));
            int month = stoi(timeString.substr(9, 11));
            int year = stoi(timeString.substr(12, 16));
            return Time(minute,hour,day, month, year);
        }
        Date getDate(){
            return Date(this->day, this->month, this ->year);
        }
        // "hmdmy" || "ymdhm"
        string toString(string format)
        {
            string day = getTimeFormatted(this->day, 2);
            string month = getTimeFormatted(this->month, 2);
            string year = getTimeFormatted(this->year, 4);
            string hour = getTimeFormatted(this->hour, 2);
            string minute = getTimeFormatted(this->minute, 2);
            if (format == "hmdmy")
                return hour+":"+minute+" "+day + "/" + month + "/" + year;
            return year + "/" + month + "/" + day +" "+ hour + ":" + minute;
        }
        bool operator>(Time &time)
        {
            return this->toString("ymdhm").compare(time.toString("ymdhm"))==1;
        }

        bool operator<(Time &time)
        {
            return this->toString("ymdhm").compare(time.toString("ymdhm")) == -1;
        }
        bool operator>=(Time &time)
        {
            return this->toString("ymdhm").compare(time.toString("ymdhm"))>=0;
        }

        bool operator<=(Time &time)
        {
            return this->toString("ymdhm").compare(time.toString("ymdhm")) <= 0;
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
#endif
