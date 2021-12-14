#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "DateTime.h"

template <typename T>
bool sortByName(const T &t1, const T &t2, bool (*order)(const string &t1, const string &t2))
{
    return (*order)(t1.getName(), t2.getName());
}
template <typename T>

bool sortByCategoryName(const T &t1, const T &t2, bool (*order)(const string &t1, const string &t2))
{
    return (*order)(t1.getCategory().getName(), t2.getCategory().getName());
}
template <typename T>

bool sortByManufacturerName(const T &t1, const T &t2, bool (*order)(const string &t1, const string &t2))
{
    return (*order)(t1.getManufacturer().getName(), t2.getManufacturer().getName());
}
template <typename T>
bool sortByUnitPrice(const T &t1, const T &t2, bool (*order)(const unsigned long &t1, const unsigned long &t2))
{
    return (*order)(t1.getUnitPrice(), t2.getUnitPrice());
}

template <typename T>
bool sortByQuantity(const T &t1, const T &t2, bool (*order)(const unsigned long &t1, const unsigned long &t2))
{
    return (*order)(t1.getQuantity(), t2.getQuantity());
}
template <typename T>
bool sortByDate(const T &t1, const T &t2, bool (*order)(const Date &t1, const Date &t2))
{
    return (*order)(t1.getDate(), t2.getDate());
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
bool ascendingNumber(const unsigned long &l, const unsigned long &r)
{
    return l < r;
}
bool descendingNumber(const unsigned long &l, const unsigned long &r)
{
    return l > r;
}
#endif