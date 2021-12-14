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
    Order(int id, unsigned long totalPrice, const Time &time, string shippingAddress, string shippingStatus, const ArrayList<OrderDetail> &orderDetailList);

    // GET
    int getId() const;
    unsigned long getTotalPrice() const;
    Time getTime() const;
    string getShippingAddress() const;
    string getShippingStatus() const;
    ArrayList<OrderDetail> getOrderDetailList() const;

    // SET
    void setOrderDetailList(const ArrayList<OrderDetail> &orderDetailList);
    void setId(int id);
    void setTotalPrice(unsigned long totalPrice);
    void setTime(const Time &time);
    void setShippingAddress(string shippingAddress);
    void setShippingStatus(string shippingStatus);

    // FRIEND
    friend ostream &operator<<(ostream &out, const Order &order);
};

#endif