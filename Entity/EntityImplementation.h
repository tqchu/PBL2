#include "D:/PBL2/src/IO/MaterialIO.h"
#include "Manufacturer.h"
#include "Category.h"
#include "Order.h"
#include "OrderDetail.h"

template <typename T>
bool findByMaterial(const T &t, const Material &u)
{
    return t.getT() == u;
}
template <typename T>
bool findByCategory(const T &t, const Category &u)
{
    return t.getT() == u;
}
/** 
 * MATERIAL
*/

Material::Material()
{
    id = 0;
    category = new Category();
    manufacturer = new Manufacturer();
}
Material::Material(int id, string name, const Category *category, const Manufacturer *manufacturer, string calculationUnit, int quantity, unsigned long unitPrice)
{
    category = new Category();
    manufacturer = new Manufacturer();
    setId(id);
    setName(name);
    setCategory(category);
    setManufacturer(manufacturer);
    setCalculationUnit(calculationUnit);
    setQuantity(quantity);
    setUnitPrice(unitPrice);
}
Material::Material(const Material &m){
    category = new Category();
    manufacturer = new Manufacturer();
    setId(m.id);
    setName(m.name);
    setCategory(m.category);
    setManufacturer(m.manufacturer);
    setCalculationUnit(m.calculationUnit);
    setQuantity(m.quantity);
    setUnitPrice(m.unitPrice);
}
Material::~Material()
{
    delete category;
    delete manufacturer;
}

// STATIC METHOD
void Material::printTitle(){
    cout << setw(5) << "";
    cout << setw(10) << left << "Ma VT";
    cout << setw(24) << left << "Ten VT";
    cout << setw(16) << left << "Ten loai VT";
    cout << setw(24) << left << "Ten nha san xuat";
    cout << setw(15) << left << "Don vi tinh";
    cout << setw(15) << left << "So luong";
    cout << setw(12)<<"Don gia";
}

// OPERATOR 
bool Material::operator==(const Material &m) const
{
    return ((id==m.id)||((this->name == m.name) && (this->getManufacturer() == m.getManufacturer()) && (this->unitPrice == m.unitPrice)));
}
bool Material::operator!=(const Material &m) const
{
    return (this->name != m.name) || (this->getManufacturer() == m.getManufacturer()) && (this->unitPrice != m.unitPrice);
}
const Material& Material::operator=(const Material &material)
{
    setId(material.id);
    setName(material.name);
    setCategory(material.category);
    setManufacturer(material.manufacturer);
    setCalculationUnit(material.calculationUnit);
    setQuantity(material.quantity);
    setUnitPrice(material.unitPrice);
    return (*this);
}
// SET
void Material::setId(int id)
{
    this->id = id;
}
void Material::setName(string name)
{
    this->name = name;
}
void Material::setCategory(const Category *category)
{
    (*(this->category)) = (*category);
}
void Material::setManufacturer(const Manufacturer *manufacturer)
{
    (*(this->manufacturer)) = (*manufacturer);
}
void Material::setCalculationUnit(string calculationUnit)
{
    this->calculationUnit = calculationUnit;
}
void Material::setQuantity(int quantity)
{
    this->quantity = quantity;
}
void Material::setUnitPrice(unsigned long unitPrice)
{
    this->unitPrice = unitPrice;
}
int Material::getId() const
{
    return id;
}

// GET
string Material::getName() const
{
    return this->name;
}
Category Material::getCategory() const
{
    return (*category);
}
Manufacturer Material::getManufacturer() const
{
    return (*manufacturer);
}
string Material::getCalculationUnit() const
{
    return this->calculationUnit;
}
int Material::getQuantity() const
{
    return this->quantity;
}
unsigned long Material::getUnitPrice() const
{
    return this->unitPrice;
}
// FRIEND 
ostream &operator<<(ostream &out, const Material &material)
{
    out << endl;
    out
        << setw(5) << "";
    out << setw(10) << left << material.getId();
    out << setw(24) << left << material.getName();
    out << setw(16) << left << material.getCategory().getName();
    out << setw(24) << left << material.getManufacturer().getName();
    out << setw(15) << left << material.getCalculationUnit();
    out << setw(15) << left << material.getQuantity();
    out << setw(10)<<material.getUnitPrice();
    return out;
}

/** 
 * CATEGORY
*/

Category::Category(int id, string name)
{
    setId(id);
    setName(name);
}

// STATIC METHOD
void Category::printTitle(){
    cout << setw(45) << "";
    cout << setw(20) << left << "Ma LVT";
    cout << setw(20)<<"Ten LVT";
}

// GET
int Category::getId() const
{
    return id;
}
string Category::getName() const
{
    return name;
}

/**
 * Trả về mảng Vật tư
 * Mảng vật tư không phải là member của Category
 */
ArrayList<Material> Category::getMaterialList()
{
    MaterialIO mIO;
    ArrayList<Material> fullMList = mIO.getList();

    return (fullMList.getGroup(findByCategoryId, id));
}

// SET
void Category::setId(int id)
{
    this->id = id;
}
void Category::setName(string name)
{
    this->name = name;
}

// OPERATOR
bool Category::operator==(const Category &c) const
{
    return ((id==c.id)||(isEqual(this->name, c.name)));
}
bool Category::operator!=(const Category &c) const
{
    return (!(isEqual(this->name, c.name)));
}

// FRIEND
ostream &operator<<(ostream &out, const Category &category)
{
    out << endl;
    out << setw(45) << "";
    out << setw(20) << left << category.getId();
    out << setw(20)<<category.getName();
    return out;
}

/** 
 * MANUFACTURER
*/

Manufacturer::Manufacturer(int id, string name, string phoneNumber, Date date, string address)
{
    setId(id);
    setName(name);
    setPhoneNumber(phoneNumber);
    setDate(date);
    setAddress(address);
}
// STATIC METHOD
void Manufacturer::printTitle(){
    cout << setw(5) << "";
    cout << setw(10) << left << "Ma NSX";
    cout << setw(32) << left << "Ten NSX";
    cout << setw(16) << left << "SDT";
    cout << setw(16) << left << "Ngay hop tac";
    cout << setw(50)<<"Dia chi";
}

// GET
int Manufacturer::getId() const
{
    return id;
}
string Manufacturer::getName() const
{
    return this->name;
}
string Manufacturer::getPhoneNumber() const
{
    return this->phoneNumber;
}
Date Manufacturer::getDate() const
{
    return this->date;
}
string Manufacturer::getAddress() const
{
    return this->address;
}

/**
 * Trả về mảng Vật tư
 * Mảng vật tư không phải là member của Category
 */

ArrayList<Material> Manufacturer::getMaterialList()
{
    MaterialIO mIO;
    ArrayList<Material> fullMList = mIO.getList();
    return (fullMList.getGroup(findByManufacturerId, id));
}

// SET
void Manufacturer::setId(int id)
{
    this->id = id;
}
void Manufacturer::setName(string name)
{
    this->name = name;
}
void Manufacturer::setPhoneNumber(string phoneNumber)
{
    this->phoneNumber = phoneNumber;
}
void Manufacturer::setDate(Date date)
{
    this->date = date;
}
void Manufacturer::setAddress(string address)
{
    this->address = address;
}

// OPERATOR
bool Manufacturer::operator==(const Manufacturer &man) const
{
    return ((id==man.getId())||(isEqual(this->name, man.name)) && (this->phoneNumber == man.phoneNumber));
}
bool Manufacturer::operator!=(const Manufacturer &man) const
{
    return !((isEqual(this->name, man.name)) && (this->phoneNumber == man.phoneNumber));
}

// FRIEND
ostream &operator<<(ostream &out, const Manufacturer &p)
{
    out << endl;
    out << setw(5) << "";
    out << setw(10) << left << p.getId();
    out << setw(32) << left << p.getName();
    out << setw(16) << left << p.getPhoneNumber();
    out << setw(16) << p.getDate().toString("dmy");
    out << setw(50) << p.getAddress();
    return out;
}

/**
 * ORDER_DETAIL
 */

OrderDetail::OrderDetail(int orderId, const Material &material, int quantity)
{
    setOrderId(orderId);
    setMaterial(material);
    setQuantity(quantity);
}

// STATIC METHOD
void OrderDetail::printTitle(){
    cout << setw(5) << "";

    // in ten VT
    cout << setw(25) << "Ten VT";
    cout << setw(10) << "Loai VT";
    cout << setw(25) << "NSX";
    cout << setw(20) << "Don vi tinh";
    cout << setw(10) << "So luong";
    cout << setw(10) << "Don gia";
    cout << setw(15) << "Thanh tien" ;
}

// GET
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
unsigned long OrderDetail::getUnitPrice() const{
    return this->unitPrice;
}

// SET
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
void OrderDetail::setUnitPrice(unsigned long unitPrice){
    this->unitPrice = unitPrice;
}

// FRIEND
ostream &operator<<(ostream &out, const OrderDetail &orderDetail)
{
    Material material = orderDetail.getMaterial();
    out << endl;
    out << setw(5) << "";
    out << setw(25) << left << material.getName();
    out << setw(10) << left << material.getCategory().getName();
    out << setw(25) << left << material.getManufacturer().getName();
    out << setw(20) << left << material.getCalculationUnit();
    out << setw(10) << left << orderDetail.getQuantity();
    out << setw(10) << left << orderDetail.getUnitPrice();

    unsigned long price = orderDetail.getQuantity() * orderDetail.getUnitPrice();
    out << setw(20) << price ;
    return out;
}

/**
 * ORDER
 */

Order::Order(int id, unsigned long totalPrice, const Time &time, string shippingAddress, string shippingStatus, const ArrayList<OrderDetail> &orderDetailList)
{
    setId(id);
    setTotalPrice(totalPrice);
    setTime(time);
    setShippingAddress(shippingAddress);
    setShippingStatus(shippingStatus);
}

// STATIC METHOD
void Order::printTitle(){

    cout << setw(5) << "";
    cout << setw(15) << left << "Ma DH";
    cout << setw(15) << left << "Thanh tien";
    cout << setw(20) << left << "Thoi gian dat";
    cout << setw(30) << left << "Dia chi giao hang";
    cout << setw(25)<<"Trang thai giao" ;
    cout << endl;
}

// GET
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

// SET
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
bool Order::operator==(const Order &order){
    return id == order.getId();
}
// FRIEND
ostream &operator<<(ostream &out, const Order &order)
{
    cout << endl;
    out << setw(5) << "";
    out << setw(15) << left << order.getId();
    out << setw(15) << left << order.getTotalPrice();
    out << setw(20) << left << order.getTime().toString("hmdmy");
    out << setw(30) << left << order.getShippingAddress();
    out << setw(30) << order.getShippingStatus();
    return out;
}
