
#ifndef MANUFACTURER_H
#define MANUFACTURER_H
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/Common/DateTime.h"
#include "D:/PBL2/src/Common/Find.h"
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

    // STATIC METHOD
    static void printTitle();

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