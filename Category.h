#ifndef CATEGORY_H
#define CATEGORY_H
#include "utils.h"
#include "D:/PBL2/src/List.h"
class Material;
class Category
{

    int id;
    string name;
public:
    Category() { id = 0;
    };
    Category(int, string);
    int getId() const;
    string getName() const;
    ArrayList<Material> getMaterialList();
    void setId(int id);
    void setName(string name);
    bool operator==(const Category &c) const;
    bool operator!=(const Category &c) const;
    friend ostream & operator <<(ostream &out, const Category &category);
};
#endif