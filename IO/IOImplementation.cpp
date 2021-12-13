#include "BaseIO.h"
#include "MaterialIO.h"
#include "DeletedMaterialIO.h"
#include "DeletedCategoryIO.h"
#include "DeletedManufacturerIO.h"
#include "ManufacturerIO.h"
#include "CategoryIO.h"
#include "OrderIO.h"
#include "OrderDetailIO.h"
#include "D:/PBL2/src/Find.h"

/**
 * MaterialIO
 */

ManufacturerIO::ManufacturerIO()
{
    path = "D:\\PBL2\\Manufacturer.txt";
    title = "	Ma NSX		Ten NSX				SDT		Ngay hop tac	Dia chi";
}
void ManufacturerIO::insertRow(const Manufacturer &manufacturer, ofstream &out)
{
    out << endl;

    int len;
    // cột id :  2 tab
    int id = manufacturer.getId();

    len = getLength(id);
    out << "\t" << id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột tên : 4 tab
    string name = manufacturer.getName();
    len = name.length();
    out << name;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 4, len);
    // cột sdt : 2 tab
    string phoneNumber = manufacturer.getPhoneNumber();
    len = phoneNumber.length();
    out << phoneNumber;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột ngày hợp tác : 2 tab
    Date date = manufacturer.getDate();
    len = 10;
    out << date;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    string address = manufacturer.getAddress();
    out << address;
}
/**
 * Cần lấy DS VT
 * */ 
Manufacturer ManufacturerIO::getRow(string &dataText) const
{
    MaterialIO mIO;
    ArrayList<Material> fullMList = mIO.getList();
    // tạo Manufacturer mới
    Manufacturer manufacturer;
    // gán dữ liệu từ file vào
    int id = stoi(getData(dataText));
    manufacturer.setId(id);
    ArrayList<Material> mList = fullMList.getGroup(findByManufacturerId, id);
    manufacturer.setMaterialList(&mList);
    manufacturer.setName(getData(dataText));
    manufacturer.setPhoneNumber(getData(dataText));
    manufacturer.setDate(Date(getData(dataText)));
    manufacturer.setAddress(getData(dataText));
    // return
    return manufacturer;
}
/** DELETED_MANUFACTURER_IO
 * */
DeletedManufacturerIO::DeletedManufacturerIO()
{
    path = "D:\\PBL2\\DeletedManufacturer.txt";
    title = "	Ma NSX		Ten NSX";
}
void DeletedManufacturerIO::insertRow(const Manufacturer &manufacturer, ofstream &out)
{
    out << endl;
    int len;
    // cột id :  2 tab
    int id = manufacturer.getId();

    len = getLength(id);
    out << "\t" << id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột tên : 4 tab
    string name = manufacturer.getName();
    len = name.length();
    out << name;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 4, len);
}
/** 
 * Chỉ Cần lấy id và tên
*/
Manufacturer DeletedManufacturerIO::getRow(string &dataText) const
{

    // tạo Manufacturer mới
    Manufacturer manufacturer;
    // gán dữ liệu từ file vào
    int id = stoi(getData(dataText));
    manufacturer.setId(id);

    manufacturer.setName(getData(dataText));

    // return
    return manufacturer;
}
/** 
 * MATERIAL_IO
*/
MaterialIO::MaterialIO()
{
    path = "D:\\PBL2\\Material.txt";
    title = "	Ma vat tu	Ten vat tu		Ma LVT		Ma NSX		Don vi tinh	So luong	Don gia";
}
/** 
 * Chèn vào file
*/
void MaterialIO::insertRow(const Material &material, ofstream &out) const
{

    out << endl;
    int len;
    // cột id :  2 tab
    int id = material.getId();

    len = getLength(id);
    out << "\t" << id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột tên : 3 tab
    string name = material.getName();
    len = name.length();
    out << name;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 3, len);

    // cột Ma loại VT : 2 tab
    int categoryId = material.getCategory().getId();
    len = getLength(categoryId);
    out << categoryId;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột Ma NSX : 2 tab
    int manufacturerId = material.getManufacturer().getId();
    len = getLength(manufacturerId);
    out << manufacturerId;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột đơn vị tính : 2 tab
    string calculationUnit = material.getCalculationUnit();
    len = calculationUnit.length();
    out << calculationUnit;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột số lượng : 2 tab
    int quantity = material.getQuantity();
    len = getLength(quantity);
    out << quantity;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột đơn giá,  2 tab
    unsigned long unitPrice = material.getUnitPrice();
    out << unitPrice;
}
/**
 * Cần lấy loại VT và NSX từ 2 file lquan.
*/
Material MaterialIO::getRow(string &dataText) const
{

    // tạo material mới
    Material material;
    // gán dữ liệu từ file vào
    material.setId(stoi(getData(dataText)));
    material.setName(getData(dataText));

    int categoryId = stoi(getData(dataText));
    material.setCategoryId(categoryId);
    
    int manufacturerId = stoi(getData(dataText));
    material.setManufacturerId(manufacturerId);

    material.setCalculationUnit(getData(dataText));
    material.setQuantity(stoi(getData(dataText)));
    material.setUnitPrice(stoul(getData(dataText)));
    // return
    return material;
}

/**
 * CategoryIO
 */
CategoryIO::CategoryIO()
{
    path = "D:\\PBL2\\Category.txt";
    title = "	Ma loai vat tu	Ten loai vat tu";
}
void CategoryIO::insertRow(const Category &category, ofstream &out) const
{

    out << endl;

    int len;
    // cột id :  2 tab
    int id = category.getId();

    len = getLength(id);
    out << "\t" << id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột tên ,2 tab
    string name = category.getName();
    out << name;
}
/** 
 * Lấy ds VT từ file VT
*/
Category CategoryIO::getRow(string &dataText) const
{

    
    MaterialIO mIO;
    ArrayList<Material> fullMList = mIO.getList();

   
    // tạo Category mới
    Category category;
    // gán dữ liệu từ file vào
    int id = stoi(getData(dataText));
    category.setId(id);

    ArrayList<Material> mList = fullMList.getGroup(findByCategoryId, id);
    category.setMaterialList(&mList);


    category.setName(getData(dataText));

    return category;
}
/**
 * DELETED_CATEGORY_IO
 * */
DeletedCategoryIO::DeletedCategoryIO()
{
    title = "	Ma loai vat tu	Ten loai vat tu";
    path = "D:/PBL2/src/DeletedCategory.txt";
}
/** 
 * insert vào mã và tên
*/
void DeletedCategoryIO::insertRow(const Category &category, ofstream &out) const
{

    out << endl;

    int len;
    // cột id :  2 tab
    int id = category.getId();

    len = getLength(id);
    out << "\t" << id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột tên ,2 tab
    string name = category.getName();
    out << name;
}
/**
 * DS Category đã xoá chỉ cần  quản lý mã và tên 
*/
Category DeletedCategoryIO::getRow(string &dataText) const
{
    Category category;
    // gán dữ liệu từ file vào
    int id = stoi(getData(dataText));
    category.setId(id);
    category.setName(getData(dataText));

    // return
    return category;
}
/**
 * ManufacturerIO
 */

/**
 * OrderIO
 */

OrderIO::OrderIO()
{
    path = "D:\\PBL2\\Order.txt";
    title = "	Ma don hang	Thoi gian dat		Dia chi giao hang			Trang thai giao";
}
void OrderIO::insertRow(const Order &order, ofstream &out)
{

    out << endl;

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
/** 
 * Lấy DS Detail và TotalPrice
*/
Order OrderIO::getRow(string &dataText) const
{
    // tạo order mới
    Order order;
    // gán dữ liệu từ file vào
    int id = stoi(getData(dataText));
    order.setId(id);
    order.setTime(Time(getData(dataText)));
    order.setShippingAddress(getData(dataText));
    order.setShippingStatus(getData(dataText));
    //! 1. Lấy ds orderDetails
    OrderDetailIO odIO;
    ArrayList<OrderDetail> fullODList = odIO.getList();
    ArrayList<OrderDetail> odList = fullODList.getGroup(findByOrderId, id);
    order.setOrderDetailList(odList);

    //! 2. Lấy total Price
    unsigned long totalWithoutDiscount = 0;
    for (int i = 0; i < odList.size; i++)
    {
        totalWithoutDiscount += odList[i].getMaterial().getUnitPrice() * odList[i].getQuantity();
    }
    unsigned long totalPrice = totalWithoutDiscount - getDiscount(totalWithoutDiscount);

    order.setTotalPrice(totalPrice);
    return order;
}
/**
 * OrderDetailIO
 */

OrderDetailIO::OrderDetailIO()
{
    path = "D:\\PBL2\\OrderDetail.txt";
    title = "	Ma vat tu	Ten vat tu		Loai vat tu	Nha cung cap		Don vi tinh	So luong	Don gia";
}
void OrderDetailIO::insertRow(const OrderDetail &orderDetail, ofstream &out)
{
    out << endl;

    int len;
    // cột id :  2 tab
    int orderId = orderDetail.getOrderId();

    len = getLength(orderId);
    out << "\t" << orderId;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột mã VT : 2 tab
    int materialId = orderDetail.getMaterial().getId();

    len = getLength(materialId);
    out << materialId;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột số lượng
    out << orderDetail.getQuantity();
}
/** 
 * lấy VT (kể cả đã xoá)
*/
OrderDetail OrderDetailIO::getRow(string &dataText) const
{

    // tạo orderDetail mới
    OrderDetail orderDetail;
    // gán dữ liệu từ file vào
    int orderId = stoi(getData(dataText));
    orderDetail.setOrderId(orderId);

    int materialId = stoi(getData(dataText));

    MaterialIO mIO;
    ArrayList<Material> fullMList = mIO.getList();
    Material material;
    try
    {
        material = fullMList.get(findById, materialId);
    }
    catch (non_existent_element &e)
    {
        DeletedMaterialIO dmIO;
        ArrayList<Material> fullDMList = dmIO.getList();
        material = fullDMList.get(findById, materialId);
    }
    orderDetail.setMaterial(material);

    orderDetail.setQuantity(stoi(getData(dataText)));
    // return
    return orderDetail;
}
/**
 * DeletedMaterialIO
 */

DeletedMaterialIO::DeletedMaterialIO()
{
    path = "D:\\PBL2\\DeletedMaterial.txt ";
    title = "	Ma vat tư	Ten vat tu		Loai vat tu	Nha cung cap		Don vi tinh	Don gia";
}
void DeletedMaterialIO::insertRow(const Material &material, ofstream &out)
{

    // xuống dòng mới
    out << endl;
   
    int len;
    // cột id :  2 tab
    int id = material.getId();

    len = getLength(id);
    out << "\t" << id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột tên : 3 tab
    string name = material.getName();
    len = name.length();
    out << name;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 3, len);

    // cột loại VT : 2 tab
    int categoryId = material.getCategory().getId();
    len = getLength(categoryId);
    out << categoryId;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột NSX : 3 tab
    int manufacturerId = material.getManufacturer().getId();
    len = getLength(manufacturerId);
    out << manufacturerId;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 3, len);

    // cột đơn vị tính : 2 tab
    string calculationUnit = material.getCalculationUnit();
    len = calculationUnit.length();
    out << calculationUnit;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột đơn giá,  2 tab
    unsigned long unitPrice = material.getUnitPrice();
    out << unitPrice;
}
// cần lấy DS LVT và NSX, kể cả trường hợp LVT, NSX đã bị xoá 
Material DeletedMaterialIO::getRow(string &dataText) const
{
   

    // tạo material mới
    Material material;
    // gán dữ liệu từ file vào
    material.setId(stoi(getData(dataText)));
    material.setName(getData(dataText));

    int categoryId = stoi(getData(dataText));
    material.setCategoryId(categoryId);

    int manufacturerId = stoi(getData(dataText));
    material.setManufacturerId(manufacturerId);

    material.setCalculationUnit(getData(dataText));
    material.setQuantity(stoi(getData(dataText)));
    material.setUnitPrice(stoul(getData(dataText)));
    return material;
}
int main(){
    /* CategoryIO mIO;
    ArrayList<Category> mList=mIO.getList();

    for (int i = 0; i < mList.size; i++)
    {
        cout << mList[i];
    } */
/* 
   OrderIO oIO;
   ArrayList<Order> oList = oIO.getList();
   cout << oList.size;
   for (int i = 0; i < oList.size; i++)
   {
       cout << oList[i];
   } */
    MaterialIO mIO;
    ArrayList<Material> mList = mIO.getList();

    for (int i = 0; i < mList.size; i++)
    {
        cout << mList[i];
    }

   cout << "Da vao dc day";
   system("pause");
}