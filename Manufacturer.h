
#ifndef MANUFACTURER_H
#define MANUFACTURER_H
#include "utils.h"
#include "DateTime.h"
class Material;
class Manufacturer
{
    int id;
    string name;
    string phoneNumber;
    Date date;
    string address;
    ArrayList<Material> *materialList;
public:
    Manufacturer()
    {
        id = 0;
        materialList = new ArrayList<Material>();
    };
    Manufacturer(int id, string name, string phoneNumber, Date date, string address);
    Manufacturer(int id, string name, string phoneNumber, Date date, string address,
    ArrayList<Material>* mList);
    ~Manufacturer();
    int getId() const;
    string getName() const;
    string getPhoneNumber() const;
    Date getDate() const;
    string getAddress() const;
    ArrayList<Material>* getMaterialList();

    void setId(int);
    void setName(string);
    void setPhoneNumber(string);
    void setDate(Date);
    void setAddress(string);
    bool operator==(const Manufacturer &man) const;
    bool operator!=(const Manufacturer &man) const;
    const Manufacturer& operator=(const Manufacturer &man);
    void setMaterialList(const ArrayList<Material> *mList);
    friend ostream &operator<<(ostream &out, const Manufacturer &p);
    // materialList
};

Manufacturer::Manufacturer(int id, string name, string phoneNumber, Date date, string address)
{
    setId(id);
    setName(name);
    setPhoneNumber(phoneNumber);
    setDate(date);
    setAddress(address);
    materialList = new ArrayList<Material>();
}
Manufacturer::Manufacturer(int id, string name, string phoneNumber, Date date, string address, ArrayList<Material> *mList){

    setId(id);
    setName(name);
    setPhoneNumber(phoneNumber);
    setDate(date);
    setAddress(address);
    setMaterialList(mList);
}
Manufacturer::~Manufacturer(){
    delete materialList;
}
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
bool Manufacturer::operator==(const Manufacturer &man) const
{
    return (isEqual(this->name, man.name)) && (this->phoneNumber == man.phoneNumber);
}
bool Manufacturer::operator!=(const Manufacturer &man) const
{
    return !((isEqual(this->name, man.name)) && (this->phoneNumber == man.phoneNumber));
}

ArrayList<Material>* Manufacturer::getMaterialList()
{
    return this->materialList;
}

void Manufacturer::setMaterialList(const ArrayList<Material> *mList)
{
    (*(this->materialList)) = (*mList);
}
const Manufacturer& Manufacturer::operator=(const Manufacturer &man) {
    setId(man.id);
    setName(man.name);
    setPhoneNumber(man.phoneNumber);
    setDate(man.date);
    setAddress(man.address);
    setMaterialList(man.materialList);
    return (*this);
}

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

#endif