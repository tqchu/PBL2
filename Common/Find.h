#ifndef FIND_H
#define FIND_H
#include "D:/PBL2/src/Entity/Material.h"
#include "utils.h"

template <typename T>
bool findByName(const T &t, const string &name)
{
    return isEqual(t.getName(), name);
}

template <typename T>
bool findByManufacturerId(const T &t, const int &id)
{
    return t.getManufacturer().getId()== id;
}

template <typename T>
bool findByCategoryId(const T &t, const int &id)
{
    return t.getCategory().getId()==id;
}

template <typename T>
bool findById(const T &t, const int &id)
{
    return t.getId() == id;
}

template <typename T>
bool findByOrderId(const T &t, const int &orderId)
{
    return t.getOrderId() == orderId;
}

template <typename T>
bool outOfQuantity(const T& t){
    return t.getQuantity() == 0;
}
#endif
