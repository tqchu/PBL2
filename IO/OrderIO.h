#ifndef ORDERIO_H
#define ORDERIO_H
#include "BaseIO.h"
#include "D:/PBL2/src/Order.h"
#include "D:/PBL2/src/utils.h"
#include "D:/PBL2/src/List.h"
class OrderIO : public BaseIO<Order>
{
    /** inherited from BaseIO
     *  getList(), update()
     *  path,title
     */
public:
    OrderIO();
    virtual void insertRow(const Order &order, ofstream &out);
    virtual Order getRow(string &dataText) const;
};
#endif