
#ifndef MANUFACTURER_H
#define MANUFACTURER_H
#include "utils.h"
#include "DateTime.h"
#include "Find.h"
class Material;
class Manufacturer
{
    int id;
    string name;
    string phoneNumber;
    Date date;
    string address;

public:
    Manufacturer()
    {
        id = 0;
    };
    Manufacturer(int id, string name, string phoneNumber, Date date, string address);

    // GET
    int getId() const;
    string getName() const;
    string getPhoneNumber() const;
    Date getDate() const;
    string getAddress() const;
    ArrayList<Material> getMaterialList();

    // SET
    void setId(int);
    void setName(string);
    void setPhoneNumber(string);
    void setDate(Date);
    void setAddress(string);

    // OPERATOR
    bool operator==(const Manufacturer &man) const;
    bool operator!=(const Manufacturer &man) const;

    // FRIEND
    friend ostream &operator<<(ostream &out, const Manufacturer &p);
};

#endif