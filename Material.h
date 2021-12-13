
#ifndef MATERIAL_H
#define MATERIAL_H
#include "utils.h"
#include "IO/ManufacturerIO.h"
#include "IO/DeletedManufacturerIO.h"
#include "IO/CategoryIO.h"
#include "IO/DeletedCategoryIO.h"
class Material
{

    int id;
    string name;
    int categoryId;
    int manufacturerId;
    string calculationUnit;
    int quantity;
    unsigned long unitPrice; // đơn giá

public:
    Material() { id = 0; };
    Material(int id, string name, Category category, Manufacturer manufacturer, string calculationUnit, int quantity, unsigned long unitPrice);

    // GET
    int getId() const;
    string getName() const;
    int getCategoryId() const;
    int getManufacturerId() const;
    Category getCategory() const;
    Manufacturer getManufacturer() const;
    string getCalculationUnit() const;
    int getQuantity() const;
    unsigned long getUnitPrice() const;

    // SET
    void setId(int);
    void setName(string name);
    void setCategoryId(int categoryId);
    void setManufacturerId(int manufacturerId);
    void setCalculationUnit(string calculationUnit);
    void setQuantity(int quantity);
    void setUnitPrice(unsigned long unitPrice);
    // OPERATOR
    bool operator==(const Material &) const;
    bool operator!=(const Material &) const;
    // FRIEND
    friend ostream &operator<<(ostream &out, const Material &material);
};

Material::Material(int id, string name, Category category, Manufacturer manufacturer, string calculationUnit, int quantity, unsigned long unitPrice)
{
    setId(id);
    setName(name);
    setCategoryId(categoryId);
    setManufacturerId(manufacturerId);
    setCalculationUnit(calculationUnit);
    setQuantity(quantity);
    setUnitPrice(unitPrice);
}

bool Material::operator==(const Material &m) const
{
    return (this->name == m.name) && (this->getManufacturer() == m.getManufacturer()) && (this->unitPrice == m.unitPrice);
}
bool Material::operator!=(const Material &m) const
{
    return (this->name != m.name) || (this->getManufacturer() == m.getManufacturer()) && (this->unitPrice != m.unitPrice);
}
void Material::setId(int id)
{
    this->id = id;
}
void Material::setName(string name)
{
    this->name = name;
}
void Material::setCategoryId(int categoryId)
{
    this->categoryId = categoryId;
}
void Material::setManufacturerId(int manufacturerId)
{
    this->manufacturerId = manufacturerId;
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
string Material::getName() const
{
    return this->name;
}
Category Material::getCategory() const
{
    CategoryIO cIO;
    ArrayList<Category> categoryList = cIO.getList();
    DeletedCategoryIO dcIO;
    ArrayList<Category> deletedCategoryList = dcIO.getList();
    Category category;
    try
    {
        category = categoryList.get(findById, this->categoryId);
    }
    catch (non_existent_element &exception)
    {
        category = deletedCategoryList.get(findById, this->categoryId);
    }

    return category;
}
Manufacturer Material::getManufacturer() const
{
    ManufacturerIO pIO;
    ArrayList<Manufacturer> manufacturerList = pIO.getList();
    DeletedManufacturerIO dpIO;
    ArrayList<Manufacturer> deletedManufacturerList = dpIO.getList();
    Manufacturer manufacturer;
    try
    {
        manufacturer = manufacturerList.get(findById, this->manufacturerId);
    }
    catch (non_existent_element &exception)
    {
        manufacturer = deletedManufacturerList.get(findById, this->manufacturerId);
    }

    return manufacturer;
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
int Material::getCategoryId() const
{
    return this->categoryId;
}
int Material::getManufacturerId() const
{
    return this->categoryId;
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
#endif