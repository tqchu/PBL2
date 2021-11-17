
#include "func.h"
#ifndef CATEGORY_H
// đường dẫn tới file Loại vật tư
string LVT="D:\\PBL2\\LVT.txt";
string titleLVT="	Ma loai vat tu	Ten loai vat tu";
int maxCategoryRecords = 100;
class Category{

    int id;
    string name;
    // List categoryList;
    public:
        Category() { id = 0; };
        Category(int, string);
        int getId();
        string getName();
        void setId(int id);
        void setName(string name);
};
Category::Category(int id,string name){
    setId(id);
    setName(name);
}
void Category::setId(int id){
    this->id=id;
}
void Category::setName(string name){
    this->name=name;
}
int Category::getId(){
    return id;
}
string Category::getName(){
    return name;
}
Category getCategory(string &categoryText)
{
    // tạo Category mới
    Category category;
    // gán dữ liệu từ file vào
    category.setId(stoi(getData(categoryText)));
    category.setName(getData(categoryText));
    // return 
    return category;
}
Category* getCategoryList(){
    Category* categoryList= new Category[maxCategoryRecords];
    // count để đếm số phần tử của list
    int count=0;

    // dùng để lưu từng line trong file
    string categoryText;
    
    ifstream src(LVT);
    // đọc 1 dòng thừa
    getline(src,categoryText);
    // bắt đầu đọc dữ liệu
    while (getline(src,categoryText)){
        // thêm vào List
        categoryList[count++]=getCategory(categoryText);
    }
    src.close();
    return categoryList;
}

void insertCategory(Category &category,ofstream& out){
    // mở file để viết vào cuối
    // xuống dòng mới
    out<<endl;
    // nhập file vào theo độ rộng, độ rộng 1 cột được tính từ đầu cột đó đến hết các dấu tab kề sau nó

    /*  cách tính số tab :
        gọi n là số kí tự trong chuỗi dữ liệu nhập vào.
        số tab của cột = n/8 + số tab phía sau 
    */
    // dùng để tính chiều dài chuỗi dữ liệu
    int len;
    // cột id :  2 tab 
    int id=category.getId();
    
    len=getLength(id);
    out<<"\t"<<id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,2,len);

    // cột tên ,2 tab
    string name=category.getName();
    out<<name;
}

bool checkCategoryByName(string& categoryName)
{
    Category *categoryList = getCategoryList();
    int numberOfRecords = getNumberOfRecords(categoryList, maxCategoryRecords);
    // check
    for (int i = 0; i < numberOfRecords; i++)
    {
        if (isEqual(categoryList[i].getName(),categoryName))
            {   // nếu bằng thì gán luôn vào cái đã có để đồng bộ
                categoryName = categoryList[i].getName();
                return true;
                }
    }
    delete[] categoryList;
    return false;
}
void updateLVT(int numberOfRecords, Category *categoryList)
{
     // mở file ghi đè
    ofstream out(LVT);
    // in lại title ( tiêu đề)
    out << titleLVT;
    // in lại toàn bộ ds mới
    for (int i = 0; i < numberOfRecords; i++)
        insertCategory(categoryList[i], out);
    // đóng file
    out.close();
}

#endif
