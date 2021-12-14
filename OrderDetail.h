#ifndef ORDERDETAIL_H
#define ORDERDETAIL_H

#include "utils.h"
#include "Material.h"
class OrderDetail
{
    int orderId;
    Material material;
    int quantity;

public:
    OrderDetail() { orderId = 0; }
    OrderDetail(int orderId, const Material &material, int quantity);

    // GET
    int getOrderId() const;
    Material getMaterial() const;
    int getQuantity() const;

    // SET
    void setOrderId(int);
    void setMaterial(const Material &);
    void setQuantity(int);

    // FRIEND
    friend ostream &operator<<(ostream &out, const OrderDetail &orderDetail);
};

#endif