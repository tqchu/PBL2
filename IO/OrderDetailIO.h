#ifndef ORDERDETAILIO_H
#define ORDERDETAILIO_H
#include "BaseIO.h"
#include "D:/PBL2/src/OrderDetail.h"
#include "D:/PBL2/src/utils.h"
#include "D:/PBL2/src/List.h"
class OrderDetailIO : public BaseIO<OrderDetail>
{
    /** inherited from BaseIO
     *  getList(), update()
     *  path,title
     * */
public:
    OrderDetailIO();
    virtual void insertRow(const OrderDetail &orderDetail, ofstream &out) const;
    virtual OrderDetail getRow(string &dataText) const;
};

#endif