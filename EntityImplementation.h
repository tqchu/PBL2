#include "IO/MaterialIO.h"
#include "Manufacturer.h"
#include "Category.h"
#include "Order.h"
#include "OrderDetail.h"

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

// OPERATOR 
bool Material::operator==(const Material &m) const
{
    return (this->name == m.name) && (this->getManufacturer() == m.getManufacturer()) && (this->unitPrice == m.unitPrice);
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
/*
 void restoreMaterial(int id, int quantityToAdd, Material *materialList, int &numberOfRecords, Material *deletedMaterialList, int &numberOfDeletedMaterialRecords)
 {
     int i;
     for (i = 0; i < numberOfRecords; i++)
     {
         if (materialList[i].getId() == id)
             break;
     }
     if (i < numberOfRecords)
     {
         materialList[i].setQuantity(materialList[i].getQuantity() + quantityToAdd);
     }

     // * vật tư ở file đã xoá

     else
     {
         // * I. đầu tiên là phải tìm vật tư trong file đã xoá
         // * 1. Lấy ds và số lượng : đã có từ tham số

         // * 2. Tìm vật tư đó
         int j = 0;
         for (; j < numberOfDeletedMaterialRecords; j++)
         {
             if (deletedMaterialList[j].getId() == id)
                 break;
         }
         // * => deletedMaterialList[i]

         //* 3. Thêm vật tư đó vào list Material đã có
         // * 3.1. Phuc hoi số lượng
         deletedMaterialList[j].setQuantity(quantityToAdd);
         // * 3.2. Đưa record mới nhất thành vật tư đó
         materialList[numberOfRecords++] = deletedMaterialList[j];

         //* 4. Xoa vat tu do ra khoi ds xoa
         for (int z = j; z < numberOfDeletedMaterialRecords - 1; z++)
         {
             deletedMaterialList[z] = deletedMaterialList[z + 1];
         }
         numberOfDeletedMaterialRecords--;
     }
 } */

// FRIEND 
ostream &operator<<(ostream &out, const Material &material)
{
    out
        << setw(5) << "";
    out << setw(10) << left << material.getId();
    out << setw(24) << left << material.getName();
    out << setw(16) << left << material.getCategory().getName();
    out << setw(24) << left << material.getManufacturer().getName();
    out << setw(15) << left << material.getCalculationUnit();
    out << setw(15) << left << material.getQuantity();
    out << material.getUnitPrice() << endl;
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
    return (isEqual(this->name, c.name));
}
bool Category::operator!=(const Category &c) const
{
    return (!(isEqual(this->name, c.name)));
}

// FRIEND
ostream &operator<<(ostream &out, const Category &category)
{
    out << setw(5) << "";
    out << setw(20) << left << category.getId();
    out << category.getName() << endl;
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
    return (isEqual(this->name, man.name)) && (this->phoneNumber == man.phoneNumber);
}
bool Manufacturer::operator!=(const Manufacturer &man) const
{
    return !((isEqual(this->name, man.name)) && (this->phoneNumber == man.phoneNumber));
}

// FRIEND
ostream &operator<<(ostream &out, const Manufacturer &p)
{
    out << setw(5) << "";

    out << setw(10) << left << p.getId();
    out << setw(32) << left << p.getName();
    out << setw(16) << left << p.getPhoneNumber();
    out << setw(16) << p.getDate().toString("dmy");
    out << p.getAddress() << endl;
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

// FRIEND
ostream &operator<<(ostream &out, const OrderDetail &orderDetail)
{
    Material material = orderDetail.getMaterial();
    out << setw(25) <<left<< material.getName();
    out << setw(10) <<left<< material.getCategory().getName();
    out << setw(25) <<left<< material.getManufacturer().getName();
    out << setw(20) <<left<< material.getCalculationUnit();
    out << setw(10) <<left<< orderDetail.getQuantity();
    out << setw(10) <<left<< material.getUnitPrice();

    unsigned long price = orderDetail.getQuantity() * material.getUnitPrice();
    out << price << endl;
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

// FRIEND
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
