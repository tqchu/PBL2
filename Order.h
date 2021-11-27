#include "func.h"
#ifndef ORDER_H
// đường dẫn tới file đơn hàng
string DH="D:\\PBL2\\DH.txt";
string titleDH="	Ma don hang	Thanh tien		Thoi gian dat		Dia chi giao hang			Trang thai giao";
int maxOrderRecords = 70;
class Order
{
    int id;
    unsigned long totalPrice;
    string time;
    string shippingAddress;
    string shippingStatus;

public:
    Order() { id = 0; }
    Order(int id, unsigned long totalPrice, string time, string shippingAddress, string shippingStatus);
    int getId();
    unsigned long getTotalPrice();
    string getTime();
    string getShippingAddress();
    string getShippingStatus();
    void setId(int id);
    void setTotalPrice(unsigned long totalPrice);
    void setTime(string time);
    void setShippingAddress(string shippingAddress);
    void setShippingStatus(string shippingStatus);
};
Order::Order(int id,unsigned long totalPrice,string time,string shippingAddress,string shippingStatus){
    setId(id);
    setTotalPrice(totalPrice);
    setTime(time);
    setShippingAddress(shippingAddress);
    setShippingStatus(shippingStatus);
}
int Order::getId(){
    return this->id;
}
unsigned long Order::getTotalPrice(){
    return this->totalPrice;
}
string Order::getTime(){
    return this->time;
}
string Order::getShippingAddress(){
    return this->shippingAddress;
}
string Order::getShippingStatus(){
    return this->shippingStatus;
}
void Order::setId(int id){
    this->id = id;
}
void Order::setTotalPrice(unsigned long totalPrice){
    this->totalPrice = totalPrice;
}
void Order::setTime(string time){
    this->time = time;
}
void Order::setShippingAddress(string shippingaddress){
    this->shippingAddress = shippingaddress;
}
void Order::setShippingStatus(string shippingStatus){
    this->shippingStatus = shippingStatus;
}
Order getOrder(string& orderText){
    // tạo order mới
    Order order;
    // gán dữ liệu từ file vào
    order.setId(stoi(getData(orderText)));
    order.setTotalPrice(stoi(getData(orderText)));
    order.setTime(getData(orderText));
    order.setShippingAddress(getData(orderText));
    order.setShippingStatus(getData(orderText));
    // return 
    return order;
}
Order* getOrderList(){
    Order *orderDetailList = new Order[maxOrderRecords];
    // count để đếm số phần tử của list
    int count=0;

    // dùng để lưu từng line trong file
    string orderText;
    
    ifstream src(DH);
    // đọc 1 dòng thừa
    getline(src,orderText);
    // bắt đầu đọc dữ liệu
    while (getline(src,orderText)){
        // thêm vào List
        orderDetailList[count++]=getOrder(orderText);
    }
    src.close();
    return orderDetailList;
}

void insertOrder(Order &order,ofstream& out){
    
    // xuống dòng mới
    out<<endl;
    // nhập file vào theo độ rộng, độ rộng 1 cột được tính từ đầu cột đó đến hết các dấu tab kề sau nó

    /*  cách tính số tab :
        gọi n là số kí tự trong chuỗi dữ liệu nhập vào.
        số tab của cột = n/8 + số tab phía sau 
    */
    // dùng để tính chiều dài chuỗi dữ liệu
    int len;
    // cột id :  2 tab 
    int id=order.getId();
    
    len=getLength(id);
    out<<"\t"<<id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,2,len);

    // cột thành tiền : 3 tab
    int totalPrice=order.getTotalPrice();
    
    len=getLength(totalPrice);
    out<<totalPrice;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,3,len);
    
    // cột thời gian đặt : 3 tab
    string time=order.getTime();
    len=time.length();
    out<<time;
    insertTab(out,3,len);

    // cột địa chỉ giao : 5 tab
    string shippingAddress=order.getShippingAddress();
    len=shippingAddress.length();
    out<<shippingAddress;
    insertTab(out,5,len);

    // cột trạng thái giao : 3 tab
    string shippingStatus= order.getShippingStatus();
    out<<shippingStatus;

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
unsigned long getOriginalPrice(unsigned long price){
    int TR = 1000000;
    unsigned long originalPrice;
    if ((price>=0.99*TR) && (price<1.98*TR)){
        originalPrice = price * (double)100 / 99;
    }
    else if ((price>=1.96*TR)&&(price<4.9*TR)){
        originalPrice = price * (double)100 / 98;
    }
    else if ((price>=4.85*TR)&&(price<9.7*TR)){
        originalPrice = price * (double)100 / 97;
    }else if (price>=9.5*TR){
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
#endif