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
    OrderDetail(int orderId, const Material& material, int quantity);
    int getOrderId() const; 
    Material getMaterial() const; 
    int getQuantity() const; 
    void setOrderId(int);
    void setMaterial(const Material&);
    void setQuantity(int);
    friend ostream &operator<<(ostream &out, const OrderDetail &orderDetail);
};

OrderDetail::OrderDetail(int orderId, const Material &material, int quantity)
{
    setOrderId(orderId);
    setMaterial(material);
    setQuantity(quantity);
}
int OrderDetail::getOrderId() const
{
    return this->orderId;
}
Material OrderDetail::getMaterial() const
{
    return this->material;
}
int OrderDetail::getQuantity() const
{
    return this->quantity;
}
void OrderDetail::setOrderId(int orderId)
{
    this->orderId = orderId;
}
void OrderDetail::setMaterial(const Material &material)
{
    this->material = material;
}
void OrderDetail::setQuantity(int quantity)
{
    this->quantity = quantity;
}
ostream &operator<<(ostream &out, const OrderDetail &orderDetail){
    Material material = orderDetail.getMaterial();
   out << setw(25) << material.getName();

   out << setw(10) << material.getCategory().getName();
   out << setw(25) << material.getManufacturer().getName();
   out << setw(20) << material.getCalculationUnit();
   out << setw(10) << orderDetail.getQuantity();
   out << setw(10) << material.getUnitPrice();

    unsigned long price = orderDetail.getQuantity() * material.getUnitPrice();
   out << price << endl;
   return out;
}

#endif