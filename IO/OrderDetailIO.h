#ifndef ORDERDETAILIO_H
#define ORDERDETAILIO_H
#include "BaseIO.h"
#include "D:/PBL2/src/Entity/OrderDetail.h"
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/Common/List.h"
class OrderDetailIO : public BaseIO<OrderDetail>
{
public:
    OrderDetailIO();
    virtual void insertRow(const OrderDetail &orderDetail, ofstream &out) const;
    virtual OrderDetail getRow(string &dataText) const;
};

#endif