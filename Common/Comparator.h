#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "DateTime.h"

/** 
 * sort theo Tên
*/
template <typename T>
bool sortByName(const T &t1, const T &t2, bool (*order)(const string &t1, const string &t2))
{
    return (*order)(t1.getName(), t2.getName());
}

/** 
 *  sort theo tên Loại Vật tư
*/
template <typename T>
bool sortByCategoryName(const T &t1, const T &t2, bool (*order)(const string &t1, const string &t2))
{
    return (*order)(t1.getCategory().getName(), t2.getCategory().getName());
}

/** 
 * sort theo tên NSX
*/
template <typename T>
bool sortByManufacturerName(const T &t1, const T &t2, bool (*order)(const string &t1, const string &t2))
{
    return (*order)(t1.getManufacturer().getName(), t2.getManufacturer().getName());
}

// sort theo Đơn giá
template <typename T>
bool sortByUnitPrice(const T &t1, const T &t2, bool (*order)(const unsigned long &t1, const unsigned long &t2))
{
    return (*order)(t1.getUnitPrice(), t2.getUnitPrice());
}

// sort theo số lượng
template <typename T>
bool sortByQuantity(const T &t1, const T &t2, bool (*order)(const unsigned long &t1, const unsigned long &t2))
{
    return (*order)(t1.getQuantity(), t2.getQuantity());
}

// sort theo Ngày
template <typename T>
bool sortByDate(const T &t1, const T &t2, bool (*order)(const Date &t1, const Date &t2))
{
    return (*order)(t1.getDate(), t2.getDate());
}

// 
template <typename T>
bool sortByTime(const T &t1, const T &t2, bool (*order)(const Time &t1, const Time &t2))
{
    return (*order)(t1.getTime(), t2.getTime());
}

// sort theo tổng giá
template <typename T>
bool sortByTotalPrice(const T &t1, const T &t2, bool (*order)(const unsigned long &t1, const unsigned long &t2))
{
    return (*order)(t1.getTotalPrice(), t2.getTotalPrice());
}

// sort theo tỷ lệ %
template <typename T>
bool sortByPercentage(const T &t1, const T &t2, bool (*order)(const double &t1, const double &t2))
{
    return (*order)(t1.getPercentage(), t2.getPercentage());
}


bool ascendingString(const string &l, const string &r)
{
    return l < r;
}
bool descendingString(const string &l, const string &r)
{
    return l > r;
}

bool ascendingDate(const Date &l, const Date &r)
{
    return l < r;
}
bool descendingDate(const Date &l, const Date &r)
{
    return l > r;
}

bool ascendingTime(const Time &l, const Time &r)
{
    return l < r;
}
bool descendingTime(const Time &l, const Time &r)
{
    return l > r;
}

bool ascendingNumber(const unsigned long &l, const unsigned long &r)
{
    return l < r;
}
bool descendingNumber(const unsigned long &l, const unsigned long &r)
{
    return l > r;
}

bool ascendingDouble(const double &l, const double &r)
{
    return l < r;
}
bool descendingDouble(const double &l, const double &r)
{
    return l > r;
}
#endif