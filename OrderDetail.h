#pragma once
#include "func.h"
#ifndef ORDERDETAIL_H
// đường dẫn tói file chi tiết đơn hàng
string CTDH="D:\\PBL2\\CTDH.txt";
string titleCTDH="	Ma don hang	Ma VT		So luong";
int maxOrderDetailRecords = 50;
class OrderDetail
{
    int id;
    int materialId;
    string materialName;
    string calculationUnit;
    int quantity;
    unsigned long unitPrice;
    unsigned long totalPrice;
public:
    OrderDetail() { id = 0; }
    OrderDetail(int id, int materialId, int quantity);
    int getId();
    int getMaterialId();
    string getMaterialName();
    string getCalculationUnit();
    int getQuantity();
    unsigned long getUnitPrice();
    unsigned long getTotalPrice();
    void setId(int);
    void setMaterialId(int);
    void setMaterialName(string);
    void setQuantity(int);
    void setUnitPrice(unsigned long);
    void setTotalPrice(unsigned long);
    void setCalculationUnit(string cUnit);
};
OrderDetail::OrderDetail(int id,int materialId,int quantity){
    setId(id);
    setMaterialId(materialId);
    setQuantity(quantity);
}
int OrderDetail::getId(){
    return this->id;
}
int OrderDetail::getMaterialId(){
    return this->materialId;
}
string OrderDetail::getMaterialName(){
    return this->materialName;
}
int OrderDetail::getQuantity(){
    return this->quantity;
}

unsigned long OrderDetail::getUnitPrice(){
    return this->unitPrice;
}
unsigned long OrderDetail::getTotalPrice(){
    return this->totalPrice;
}
string OrderDetail::getCalculationUnit(){
    return this->calculationUnit;
}

void OrderDetail::setId(int id)
{
    this->id = id;
}
void OrderDetail::setMaterialId(int materialId){
    this->materialId = materialId;
}
void OrderDetail::setMaterialName(string materialName){
    this->materialName = materialName; 
}
void OrderDetail::setQuantity(int quantity){
    this->quantity = quantity;
}
void OrderDetail::setUnitPrice(unsigned long unitPrice){
    this->unitPrice = unitPrice;
}
void OrderDetail::setTotalPrice(unsigned long totalPrice){
    this->totalPrice = totalPrice;
}
void OrderDetail::setCalculationUnit(string cUnit){
    this->calculationUnit = cUnit;
}
// ham phu
OrderDetail getOrderDetail(string &oderdetailText)
{
    // tạo orderDetail mới
    OrderDetail oderdetail;
    // gán dữ liệu từ file vào
    oderdetail.setId(stoi(getData(oderdetailText)));
    oderdetail.setMaterialId(stoi(getData(oderdetailText)));
    oderdetail.setQuantity(stoi(getData(oderdetailText)));
    // return 
    return oderdetail;
}
OrderDetail* getOrderDetailList(){
    OrderDetail* orderDetailList= new OrderDetail[maxOrderDetailRecords];
    // count để đếm số phần tử của list
    int count=0;

    // dùng để lưu từng line trong file
    string orderDetailText;
    
    ifstream src(CTDH);
    // đọc 1 dòng thừa
    getline(src,orderDetailText);
    // bắt đầu đọc dữ liệu
    while (getline(src,orderDetailText)){
        // thêm vào List
        orderDetailList[count++]=getOrderDetail(orderDetailText);
    }
    src.close();
    return orderDetailList;
}
void insertOrderDetail(OrderDetail &orderDetail,ofstream& out){
   
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
    int id=orderDetail.getId();
    
    len=getLength(id);
    out<<"\t"<<id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,2,len);

    // cột mã VT : 2 tab
    int materialId=orderDetail.getMaterialId();
    
    len=getLength(materialId);
    out<<materialId;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,2,len);

    // cột số lượng
    out<<orderDetail.getQuantity();
    
}
void deleteOrderDetailByOrderId(int orderId){
    OrderDetail *orderDetailList = getOrderDetailList();
    int numberOfRecords = getNumberOfRecords(orderDetailList, maxOrderDetailRecords);
    // mở file ghi đè
    ofstream out(CTDH);
    // in lại title ( tiêu đề)
    out << titleCTDH;

    for (int i = 0; i < numberOfRecords;i++){
        if (orderDetailList[i].getId()!=orderId){
            insertOrderDetail(orderDetailList[i],out);
        }
    }
    out.close();
}
void updateCTDH(int numberOfRecords, OrderDetail *orderDetailList)
{
    // mở file ghi đè
    ofstream out(CTDH);
    // in lại title ( tiêu đề)
    out << titleCTDH;
    // in lại toàn bộ ds mới
    for (int i = 0; i < numberOfRecords; i++)
        insertOrderDetail(orderDetailList[i], out);
    // đóng file
    out.close();
}
#endif