#ifndef CATEGORY_H
#define CATEGORY_H
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/Common/List.h"
// forward declaration
class Material;
class Category
{

    int id;
    string name;
public:
    Category() { id = 0;
    };
    Category(int, string);
    
    // STATIC METHOD
    static void printTitle();

    // GET
    int getId() const;
    string getName() const;
    
    // SET
    ArrayList<Material> getMaterialList();
    void setId(int id);
    void setName(string name);
    
    // OPERATOR 
    bool operator==(const Category &c) const;
    bool operator!=(const Category &c) const;
    
    // FRIEND
    friend ostream & operator <<(ostream &out, const Category &category);
};
#endif