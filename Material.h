#include "func.h"
#ifndef MATERIAL_H
// đường dẫn tới file Vật tư
string VT = "D:\\PBL2\\VT.txt";
string titleVT = "	Ma vat tư	Ten vat tu			Loai vat tu	Nha cung cap			Don vi tinh	So luong		Don gia";
int maxMaterialRecords = 200;
class Material
{

    int id;
    // không quá 31 kí tự
    string name;
    // tên loại vật liệu , không quá 15 kí tự
    string categoryName;
    // tên NSX  ,không quá 31 kí tự
    string providerName;
    // đơn vị tính , không quá 15 kí tự
    string calculationUnit;

    int quantity;
    unsigned long unitPrice; // đơn giá
public:
    Material() { id = 0; };
    Material(int id, string name, string categoryName, string providerName, string calculationUnit, int quantity, unsigned long unitPrice);
    Material(int, string, string, string, int, unsigned long, unsigned long, string);

    int getId();
    string getName();
    string getCategoryName();
    string getProviderName();
    string getCalculationUnit();
    int getQuantity();
    unsigned long getUnitPrice();
    void setId(int);
    void setName(string name);
    void setCategoryName(string categoryName);
    void setProviderName(string providerName);
    void setCalculationUnit(string calculationUnit);
    void setQuantity(int quantity);
    void setUnitPrice(unsigned long unitPrice);
};
Material::Material(int id, string name, string categoryName, string providerName, string calculationUnit, int quantity, unsigned long unitPrice)
{
    setId(id);
    setName(name);
    setCategoryName(categoryName);
    setProviderName(providerName);
    setCalculationUnit(calculationUnit);
    setQuantity(quantity);
    setUnitPrice(unitPrice);
}
void Material::setId(int id)
{
    this->id = id;
}
void Material::setName(string name)
{
    this->name = name;
}
void Material::setCategoryName(string categoryName)
{
    this->categoryName = categoryName;
}
void Material::setProviderName(string providerName)
{
    this->providerName = providerName;
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
int Material::getId()
{
    return id;
}
string Material::getName()
{
    return this->name;
}
string Material::getCategoryName()
{
    return this->categoryName;
}
string Material::getProviderName()
{
    return this->providerName;
}
string Material::getCalculationUnit()
{
    return this->calculationUnit;
}
int Material::getQuantity()
{
    return this->quantity;
}
unsigned long Material::getUnitPrice()
{
    return this->unitPrice;
}

Material getMaterial(string &materialText)
{
    // tạo material mới
    Material material;
    // gán dữ liệu từ file vào
    material.setId(stoi(getData(materialText)));
    material.setName(getData(materialText));
    material.setCategoryName(getData(materialText));
    material.setProviderName(getData(materialText));
    material.setCalculationUnit(getData(materialText));
    material.setQuantity(stoi(getData(materialText)));
    material.setUnitPrice(stod(getData(materialText)));
    // return
    return material;
}

Material *getMaterialList()
{
    Material *materialList = new Material[100];
    // count để đếm số phần tử của list
    int mListCount = 0;

    // dùng để lưu từng line trong file
    string materialText;

    ifstream src(VT);
    // đọc 1 dòng thừa
    getline(src, materialText);
    // bắt đầu đọc dữ liệu
    while (getline(src, materialText))
    {
        // getMaterial trong class 
        // T.getMaterial()
        // thêm vào List
        materialList[mListCount++] = getMaterial(materialText);
    }
    src.close();
    return materialList;
}

void insertMaterial(Material &material, ofstream &out)
{

    // xuống dòng mới
    out << endl;
    // nhập file vào theo độ rộng, độ rộng 1 cột được tính từ đầu cột đó đến hết các dấu tab kề sau nó

    /*  cách tính số tab :
        gọi n là số kí tự trong chuỗi dữ liệu nhập vào.
        số tab của cột = n/8 + số tab phía sau
    */
    // dùng để tính chiều dài chuỗi dữ liệu
    int len;
    // cột id :  2 tab
    int id = material.getId();

    len = getLength(id);
    out << "\t" << id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột tên : 4 tab
    string name = material.getName();
    len = name.length();
    out << name;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 4, len);
    // cột loại VT : 2 tab
    string categoryName = material.getCategoryName();
    len = categoryName.length();
    out << categoryName;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột NSX : 4 tab
    string providerName = material.getProviderName();
    len = providerName.length();
    out << providerName;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 4, len);

    // cột đơn vị tính : 2 tab
    string calculationUnit = material.getCalculationUnit();
    len = calculationUnit.length();
    out << calculationUnit;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 2, len);

    // cột số lượng : 3 tab
    int quantity = material.getQuantity();
    len = getLength(quantity);
    out << quantity;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out, 3, len);
    // cột đơn giá
    unsigned long unitPrice = material.getUnitPrice();
    out << unitPrice;
}
void updateVT(int numberOfRecords, Material *materialList)
{
    // mở file ghi đè
    ofstream out(VT);
    // in lại title ( tiêu đề)
    out << titleVT;
    // in lại toàn bộ ds mới
    for (int i = 0; i < numberOfRecords; i++)
        insertMaterial(materialList[i], out);
    // đóng file
    out.close();
}

Material getMaterialById(int id)
{
    Material *materialList = getMaterialList();
    int i;
    for (i = 0; i < getNumberOfRecords(materialList,maxMaterialRecords); i++)
    {
        if (materialList[i].getId() == id)
            break;
    }
    return materialList[i];
}

Material updateMaterialById(int id, int quantityToBeSubTracted, Material* materialList, int numberOfRecords)
{    
    if (id<=numberOfRecords){

        // kiem tra dieu kien con du hang
        int oldQuantity = materialList[id-1].getQuantity();
        if (oldQuantity >= quantityToBeSubTracted)
        {
            // chinh sua vat tu
            materialList[id-1]
                .setQuantity(oldQuantity - quantityToBeSubTracted);
            return materialList[id-1];
        }
        // khong du so luong vat tu
        else
        {
            cout << "So luong vat tu nay trong kho chi con " << oldQuantity << ", khong du de ban ! " << endl;
            Material nullMaterial;
            return nullMaterial;
        }
    }
    // khong ton tai vat tu
    else {
        cout << "Khong co vat tu tuong ung voi ma ban vua nhap ! Vui long nhap lai !"<<endl;
        Material negativeMaterial;
        negativeMaterial.setId(-1);
        return negativeMaterial;
    }
}
bool checkMaterialQuantityByProviderName(string providerName){
    Material *materialList = getMaterialList();
    int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);
    int materialIdNumber[numberOfMaterialRecords], count = 0;
    for (int i = 0; i < numberOfMaterialRecords;i++){
        if (materialList[i].getProviderName() == providerName)
        {
            if (materialList[i].getQuantity() > 0)
                return false;
            // =0
            // luu id cua nhung vat tu can xoa
            else
            {
                materialIdNumber[count++] = i+1;
            }
        }
    }
    // neu khong co vat tu nao trong list VT , thi return luon , khong lam gi het
    if (count == 0)
        return true;
    // thoa dieu kien de xoa NSX, ta tien hanh xoa toan bo VT
    int j = 0;
    // mở file ghi đè
    ofstream out(VT);
    // in lại title ( tiêu đề)
    out << titleVT;
    // in lại toàn bộ ds mới

    for (int i = 0; i < numberOfMaterialRecords; i++)
    {
        if ((j < count) && (materialList[i].getId() == materialIdNumber[j]))
        {
            j++;
        }
        else{
            if (j>0)
                materialList[i].setId(i + 1 - j);
            insertMaterial(materialList[i], out);
        }   
    }
    // đóng file
    out.close();

    return true;
}
bool checkMaterialQuantityByCategoryName(string categoryName){
    Material *materialList = getMaterialList();
    
    int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);
    int materialIdNumber[numberOfMaterialRecords], count=0;
    for (int i = 0; i < numberOfMaterialRecords; i++)
    {
        if (materialList[i].getCategoryName() == categoryName)
        {
            if (materialList[i].getQuantity() > 0)
                return false;
            // =0    
            // luu id cua nhung vat tu can xoa
            else {
                
                materialIdNumber[count++] = i+1;
            }
        }
    }
    // neu khong co vat tu nao trong list VT , thi return luon , khong lam gi het
    if (count==0)
        return true;
    // thoa dieu kien de xoa NSX, ta tien hanh xoa toan bo VT
    int j=0;
    // mở file ghi đè
    ofstream out(VT);
    // in lại title ( tiêu đề)
    out << titleVT;
    // in lại toàn bộ ds mới
        
    for (int i = 0; i < numberOfMaterialRecords;i++){
        if ((j<count) && (materialList[i].getId() == materialIdNumber[j])){
              j++;
        }
        else {
            if (j > 0)
            materialList[i].setId(i + 1 - j);
            insertMaterial(materialList[i], out);
        }
    }
    // đóng file
    out.close();

    return true;
}
#endif
