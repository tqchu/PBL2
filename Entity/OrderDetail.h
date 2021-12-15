#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include "D:/PBL2/src/Common/utils.h"
#include "Material.h"
class OrderDetail
{
    int orderId;
    Material material;
    int quantity;
    unsigned long unitPrice;

public:
    OrderDetail() { orderId = 0; }
    OrderDetail(int orderId, const Material &material, int quantity);

    // STATIC METHOD
    static void printTitle();

    // GET
    int getOrderId() const;
    Material getMaterial() const;
    int getQuantity() const;
    unsigned long getUnitPrice() const;

    // SET
    void setOrderId(int);
    void setMaterial(const Material &);
    void setQuantity(int);
    void setUnitPrice(unsigned long unitPrice);

    // FRIEND
    friend ostream &operator<<(ostream &out, const OrderDetail &orderDetail);
};

#endif