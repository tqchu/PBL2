
#ifndef MATERIAL_H
#define MATERIAL_H
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/IO/ManufacturerIO.h"
#include "D:/PBL2/src/IO/DeletedManufacturerIO.h"
// forward declaration
class Category;
class Manufacturer;
class Material
{

    int id;
    string name;
    Category *category;
    Manufacturer *manufacturer;
    string calculationUnit;
    int quantity;
    unsigned long unitPrice;

public:
    Material();
    Material(int id, string name, const Category *category, const Manufacturer *manufacturer, string calculationUnit, int quantity, unsigned long unitPrice);
    Material(const Material &m);

    ~Material();

    // GET
    int getId() const;
    string getName() const;
    Category getCategory() const;
    Manufacturer getManufacturer() const;
    string getCalculationUnit() const;
    int getQuantity() const;
    unsigned long getUnitPrice() const;

    // STATIC METHOD
    static void printTitle();

    // SET
    void setId(int);
    void setName(string name);
    void setCategory(const Category *category);
    void setManufacturer(const Manufacturer *manufacturer);
    void setCalculationUnit(string calculationUnit);
    void setQuantity(int quantity);
    void setUnitPrice(unsigned long unitPrice);

    // OPERATOR
    bool operator==(const Material &) const;
    bool operator!=(const Material &) const;
    const Material &operator=(const Material &material);

    // FRIEND
    friend ostream &operator<<(ostream &out, const Material &material);
};
#endif