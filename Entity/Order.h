#ifndef ORDER_H
#define ORDER_H
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/Common/DateTime.h"
#include "D:/PBL2/src/Entity/OrderDetail.h"
#include "D:/PBL2/src/Entity/Material.h"
#include "D:/PBL2/src/Common/List.h"
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
    
    // STATIC METHOD
    static void printTitle();

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

    bool operator==(const Order &order);
    // FRIEND
    friend ostream &operator<<(ostream &out, const Order &order);
};

#endif