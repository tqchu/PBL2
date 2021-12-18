#ifndef ORDERIO_H
#define ORDERIO_H
#include "BaseIO.h"
#include "D:/PBL2/src/Entity/Order.h"
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/Common/List.h"
class OrderIO : public BaseIO<Order>
{
public:
    OrderIO();
    virtual void insertRow(const Order &order, ofstream &out) const;
    virtual Order getRow(string &dataText) const;
};
#endif