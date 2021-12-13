#ifndef ORDER_H
#define ORDER_H
#include "utils.h"
#include "DateTime.h"
#include "OrderDetail.h"
#include "Material.h"
#include "List.h"
// đường dẫn tới file đơn hàng
unsigned long getDiscount(unsigned long totalWithoutDiscount);
class Order
{
    ArrayList<OrderDetail> orderDetailList;
    int id;
    Time time;
    unsigned long totalPrice;
    string shippingAddress;
    string shippingStatus;

public:
    Order() { id = 0; }
    Order(int id, unsigned long totalPrice,const Time& time, string shippingAddress, string shippingStatus, const ArrayList<OrderDetail> &orderDetailList);
    int getId() const;
    unsigned long getTotalPrice() const;
    Time getTime() const;
    string getShippingAddress() const;
    string getShippingStatus() const;
    ArrayList<OrderDetail> getOrderDetailList() const;
    void setOrderDetailList(const ArrayList<OrderDetail>& orderDetailList);
    void setId(int id);
    void setTotalPrice(unsigned long totalPrice);
    void setTime(const Time& time);
    void setShippingAddress(string shippingAddress);
    void setShippingStatus(string shippingStatus);
    friend ostream &operator<<(ostream &out, const Order &order);
};

Order::Order(int id, unsigned long totalPrice, const Time &time, string shippingAddress, string shippingStatus, const ArrayList<OrderDetail> &orderDetailList)
{
    setId(id);
    setTotalPrice(totalPrice);
    setTime(time);
    setShippingAddress(shippingAddress);
    setShippingStatus(shippingStatus);
}
int Order::getId() const
{
    return this->id;
}
unsigned long Order::getTotalPrice() const
{
    return this->totalPrice;
}
Time Order::getTime() const
{
    return this->time;
}
string Order::getShippingAddress() const
{
    return this->shippingAddress;
}
string Order::getShippingStatus() const
{
    return this->shippingStatus;
}
ArrayList<OrderDetail> Order::getOrderDetailList() const
{
    return this->orderDetailList;
}
void Order::setOrderDetailList(const ArrayList<OrderDetail> &orderDetailList)

{
    this->orderDetailList = orderDetailList;
}
void Order::setTotalPrice(unsigned long totalPrice)
{
    this->totalPrice = totalPrice;
}
void Order::setId(int id)
{
    this->id = id;
}
void Order::setTime(const Time &time)
{
    this->time = time;
}
void Order::setShippingAddress(string shippingaddress)
{
    this->shippingAddress = shippingaddress;
}
void Order::setShippingStatus(string shippingStatus)
{
    this->shippingStatus = shippingStatus;
}
ostream &operator<<(ostream &out, const Order &order)
{
    out << setw(5) << "";

    out << setw(15) << left << order.getId();
    out << setw(15) << left << order.getTotalPrice();

    out << setw(20) << left << order.getTime().toString("hmdmy");
    out << setw(30) << left << order.getShippingAddress();
    out << order.getShippingStatus() << endl;
    return out;
}
#endif