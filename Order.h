#pragma once
#include "func.h"
#include "DateTime.h"
#include "OrderDetail.h"
#include "Material.h"
#ifndef ORDER_H
// đường dẫn tới file đơn hàng
unsigned long getDiscount(unsigned long totalWithoutDiscount);
string DH = "D:\\PBL2\\DH.txt";
string titleDH = "	Ma don hang	Thoi gian dat		Dia chi giao hang			Trang thai giao";
int maxOrderRecords = 70;   
class Order
{
    OrderDetail *orderDetails;
    int id;
    Time time;
    unsigned long totalPrice;
    string shippingAddress;
    string shippingStatus;

public:
    Order() { id = 0; }
    Order(int id, unsigned long totalPrice, Time time, string shippingAddress, string shippingStatus);
    ~Order(){
        delete[] orderDetails;
    }
    int getId();
    unsigned long getTotalPrice();
    Time getTime();
    string getShippingAddress();
    string getShippingStatus();
    OrderDetail *getOrderDetailS();
    void setOrderDetails(OrderDetail *orderDetails);
    void setId(int id);
    void setTotalPrice(unsigned long totalPrice);
    void setTime(Time time);
    void setShippingAddress(string shippingAddress);
    void setShippingStatus(string shippingStatus);
};
Order::Order(int id, unsigned long totalPrice, Time time, string shippingAddress, string shippingStatus)
{
    setId(id);
    setTotalPrice(totalPrice);
    setTime(time);
    setShippingAddress(shippingAddress);
    setShippingStatus(shippingStatus);
}
int Order::getId()
{
    return this->id;
}
unsigned long Order::getTotalPrice()
{
    return this->totalPrice;
}
Time Order::getTime()
{
    return this->time;
}
string Order::getShippingAddress()
{
    return this->shippingAddress;
}
string Order::getShippingStatus()
{
    return this->shippingStatus;
}
OrderDetail *Order::getOrderDetailS()
{
    return this->orderDetails;
}
void Order::setOrderDetails(OrderDetail *orderDetails)
{
    this->orderDetails = orderDetails;
}
void Order::setTotalPrice(unsigned long totalPrice)
{
    this->totalPrice = totalPrice;
}
void Order::setId(int id)
{
    this->id = id;
}
void Order::setTime(Time time)
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
Order getOrder(string &orderText)
{
    // tạo order mới
    Order order;
    // gán dữ liệu từ file vào
    order.setId(stoi(getData(orderText)));
    order.setTime(Time(getData(orderText)));
    order.setShippingAddress(getData(orderText));
    order.setShippingStatus(getData(orderText));
    //! đoạn code siêu dỏm
    //! 1. Lấy ds orderDetails
    OrderDetail *fullODList = getOrderDetailList();
    int numberOfODRecords = getNumberOfRecords(fullODList, maxOrderDetailRecords);
    OrderDetail *orderDetails = new OrderDetail[50];
    int count = 0;
    for (int i = 0; i < numberOfODRecords; i++)
    {
        if (fullODList[i].getId() == order.getId())
        {
            orderDetails[count++] = fullODList[i];
        }
        else if (fullODList[i].getId() > order.getId())
            break;
    }
    order.setOrderDetails(orderDetails);
    delete[] fullODList;

    //! 2. Lấy total Price

    unsigned long totalWithoutDiscount = 0;
    Material *materialList = getMaterialList();
    for (int i = 0; i < count; i++)
    {
        Material materialById = getMaterialById(orderDetails[i].getMaterialId(), materialList);

        unsigned long price = orderDetails[i].getQuantity() * materialById.getUnitPrice();
        totalWithoutDiscount += price;
    }
    order.setTotalPrice(totalWithoutDiscount - getDiscount(totalWithoutDiscount));
    delete[] materialList;
    // return
    return order;
}
Order *getOrderList()
{
    Order *orderList = new Order[maxOrderRecords];
    // count để đếm số phần tử của list
    int count = 0;

    // dùng để lưu từng line trong file
    string orderText;

    ifstream src(DH);
    // đọc 1 dòng thừa
    getline(src, orderText);
    // bắt đầu đọc dữ liệu
    while (getline(src, orderText))
    {
        // thêm vào List
        orderList[count++] = getOrder(orderText);
    }
    src.close();
    return orderList;
}

void insertOrder(Order &order, ofstream &out)
{

    // xuống dòng mới
    out << endl;
    // nhập file vào theo độ rộng, độ rộng 1 cột được tính từ đầu cột đó đến hết các dấu tab kề sau nó

    /*  cách tính số tab :
        gọi n là số kí tự trong chuỗi dữ liệu nhập vào.
        số tab của cột = n/8 + số tab phía sau
    */
    // dùng để tính chiều dài chuỗi dữ liệu
    int len;
    // cột id :  2 tab
    int id = order.getId();

    len = getLength(id);
    out << "\t" << id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột thời gian đặt : 3 tab
    Time time = order.getTime();
    len = 16;
    out << time;
    insertTab(out, 3, len);

    // cột địa chỉ giao : 5 tab
    string shippingAddress = order.getShippingAddress();
    len = shippingAddress.length();
    out << shippingAddress;
    insertTab(out, 5, len);

    // cột trạng thái giao : 3 tab
    string shippingStatus = order.getShippingStatus();
    out << shippingStatus;
}

void updateDH(int numberOfRecords, Order *orderList)
{
    // mở file ghi đè
    ofstream out(DH);
    // in lại title ( tiêu đề)
    out << titleDH;
    // in lại toàn bộ ds mới
    for (int i = 0; i < numberOfRecords; i++)
        insertOrder(orderList[i], out);
    // đóng file
    out.close();
}
unsigned long getOriginalPrice(unsigned long price)
{
    int TR = 1000000;
    unsigned long originalPrice;
    if ((price >= 0.99 * TR) && (price < 1.98 * TR))
    {
        originalPrice = price * (double)100 / 99;
    }
    else if ((price >= 1.96 * TR) && (price < 4.9 * TR))
    {
        originalPrice = price * (double)100 / 98;
    }
    else if ((price >= 4.85 * TR) && (price < 9.7 * TR))
    {
        originalPrice = price * (double)100 / 97;
    }
    else if (price >= 9.5 * TR)
    {
        originalPrice = price * (double)100 / 95;
    }
    return originalPrice;
}
unsigned long getDiscount(unsigned long totalWithoutDiscount)
{

    int TR = 1000000;
    unsigned long discount;
    if ((totalWithoutDiscount >= 1 * TR) && (totalWithoutDiscount < 2 * TR))
    {
        discount = totalWithoutDiscount * 1 / 100;
    }
    else if ((totalWithoutDiscount >= 2 * TR) && (totalWithoutDiscount < 5 * TR))
    {
        discount = totalWithoutDiscount * 2 / 100;
    }
    else if ((totalWithoutDiscount >= 5 * TR) && (totalWithoutDiscount <= 10 * TR))
    {
        discount = totalWithoutDiscount * 3 / 100;
    }
    else if (totalWithoutDiscount >= 10 * TR)
        discount = totalWithoutDiscount * 5 / 100;
    return discount;
}

void sortByTime(Order *orderList, int numberOfRecords, bool (*func_ptr)(Time, Time))
{
    int i, j;
    for (i = 0; i < numberOfRecords - 1; i++)
    {
        for (j = 0; j < numberOfRecords - i - 1; j++)
        {
            if ((*func_ptr)(orderList[j].getTime(), orderList[j + 1].getTime()))
                SWAP(orderList[j], orderList[j + 1]);
        }
    }
}

void sortByTotalPrice(Order *orderList, int numberOfRecords, bool (*func_ptr)(unsigned long, unsigned long))
{
    int i, j;
    for (i = 0; i < numberOfRecords - 1; i++)
    {
        for (j = 0; j < numberOfRecords - i - 1; j++)
        {
            if ((*func_ptr)(orderList[j].getTotalPrice(), orderList[j + 1].getTotalPrice()))
                SWAP(orderList[j], orderList[j + 1]);
        }
    }
}

#endif