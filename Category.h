#ifndef CATEGORY_H
#define CATEGORY_H
#include "utils.h"
#include "D:/PBL2/src/List.h"
class Material;
class Category
{

    int id;
    string name;
    ArrayList<Material>* materialList;
public:
    Category() { id = 0;
        materialList = new ArrayList<Material>();
    };
    Category(int, string);
    Category(int, string,ArrayList<Material>*);
    ~Category();
    int getId() const;
    string getName() const;
    ArrayList<Material>* getMaterialList();
    void setId(int id);
    void setName(string name);
    void setMaterialList(const ArrayList<Material> *mList);
    bool operator==(const Category &c) const;
    bool operator!=(const Category &c) const;
    const Category& operator=(const Category &c);
    friend ostream &out(ostream &out, const Category &category);
};

Category::Category(int id, string name)
{
    setId(id);
    setName(name);
    // materialList = new ArrayList<Material>();
}
Category::Category(int id, string name, ArrayList<Material> *mList){
    setId(id);
    setName(name);
    setMaterialList(mList);
}
Category::~Category(){
    delete materialList;
}
void Category::setId(int id)
{
    this->id = id;
}
void Category::setName(string name)
{
    this->name = name;
}
int Category::getId() const
{
    return id;
}
string Category::getName() const
{
    return name;
}
ArrayList<Material>* Category::getMaterialList()
{
    return this->materialList;
}
void Category::setMaterialList(const ArrayList<Material> *mList)
{
    (*(this->materialList)) = (*mList);
}
bool Category::operator==(const Category &c) const
{
    return (isEqual(this->name, c.name));
}
bool Category::operator!=(const Category &c) const
{
    return (!(isEqual(this->name, c.name)));
}
const Category& Category::operator=(const Category &c){
    setId(c.id);
    setName(c.name);
    setMaterialList(c.materialList);
    return (*this);
}

ostream &operator<<(ostream &out, const Category &category)
{
    out << setw(5) << "";
    out << setw(20) << left << category.getId();
    out << category.getName() << endl;
    return out;
}
#endif