#include "func.h"
#ifndef PROVIDER_H
// đường dẫn tới file Nhà sản xuất
string NSX="D:\\PBL2\\NSX.txt";
// max records
int maxProviderRecords = 60;
string titleNSX = "	Ma NSX		Ten NSX				SDT		Ngay hop tac	Dia chi";
class Provider{
    int id;
    string name;
    string phoneNumber;
    string date;
    string address;
    // materialList
public:
    Provider() { id = 0; };
    Provider(int id, string name, string phoneNumber, string date, string address);
    int getId();
    string getName();
    string getPhoneNumber();
    string getDate();
    string getAddress();
    // materialList
    void setId(int);
    void setName(string);
    void setPhoneNumber(string);
    void setDate(string);
    void setAddress(string);
    // materialList
};
Provider::Provider(int id, string name, string phoneNumber, string date, string address)
{
    setId(id);
    setName(name);
    setPhoneNumber(phoneNumber);
    setDate(date);
    setAddress(address);
}
int Provider::getId(){
    return id;
}
string Provider::getName(){
    return this->name;
}
string Provider::getPhoneNumber(){
    return this->phoneNumber;
}
string Provider::getDate(){
    return this->date;
}
string Provider::getAddress(){
    return this->address;
}
void Provider::setId(int id)
{
    this->id=id;
}
void Provider::setName(string name){
    this->name=name;
}
void Provider::setPhoneNumber(string phoneNumber){
    this->phoneNumber=phoneNumber;
}
void Provider::setDate(string date){
    this->date=date;
}
void Provider::setAddress(string address){
    this->address=address;
}
Provider getProvider(string& providerText){
    // tạo Provider mới
    Provider provider;
    // gán dữ liệu từ file vào

    provider.setId(stoi(getData(providerText)));
    provider.setName(getData(providerText));
    provider.setPhoneNumber(getData(providerText));
    provider.setDate(getData(providerText));
    provider.setAddress(getData(providerText));
    // return 
    return provider;
}
Provider* getProviderList(){
    Provider* providerList= new Provider[maxProviderRecords];
    // count để đếm số phần tử của list
    int count=0;

    // dùng để lưu từng line trong file
    string providerText;
    
    ifstream src(NSX);
    // đọc 1 dòng thừa
    getline(src,providerText);
    // bắt đầu đọc dữ liệu
    while (getline(src,providerText)){
        // thêm vào List
        providerList[count++]=getProvider(providerText);
    }
    src.close();
    return providerList;
}
void insertProvider(Provider &provider,ofstream& out){
    
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
    int id=provider.getId();
    
    len=getLength(id);
    out<<"\t"<<id;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,2,len);

    // cột tên : 4 tab
    string name=provider.getName();
    len=name.length();
    out<<name;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,4,len);
    // cột sdt : 2 tab
    string phoneNumber=provider.getPhoneNumber();
    len=phoneNumber.length();
    out<<phoneNumber;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,2,len);

    // cột ngày hợp tác : 2 tab
    string date=provider.getDate();
    len=date.length();
    out<<date;
    // in những tab còn lại ứng với độ rộng của cột
    insertTab(out,2,len);

    string address = provider.getAddress();
    out << address;
}
void updateNSX(int numberOfRecords,Provider* providerList){
    // mở file ghi đè
    ofstream out(NSX);
    // in lại title ( tiêu đề)
    out << titleNSX;
    // in lại toàn bộ ds mới
    for (int i = 0; i < numberOfRecords; i++)
        insertProvider(providerList[i], out);
    // đóng file
    out.close();
}
// check điều kiện viết thường và đổi luôn tham số đưa vào
bool checkProviderByName(string& providerName){
    Provider *providerList = getProviderList();
    int numberOfRecords;
    for (numberOfRecords = 0; numberOfRecords < maxProviderRecords; numberOfRecords++)
    {
        if (providerList[numberOfRecords].getId()==0 )
            break;
    }
    // check
    for (int i = 0; i < numberOfRecords;i++){
        if (isEqual(providerList[i].getName(), providerName))
        { // nếu bằng thì gán luôn vào cái đã có để đồng bộ
            providerName = providerList[i].getName();
            return true;
        }
    }
    delete[] providerList;
    return false;
}

void sortByDate(Provider *providerList, int numberOfRecords, bool (*func_ptr)(string, string))
{
    int i, j;
    for (i = 0; i < numberOfRecords - 1; i++)
    {
        for (j = 0; j < numberOfRecords - i - 1; j++)
        {
            if ((*func_ptr)(providerList[j].getDate(), providerList[j + 1].getDate()))
                SWAP(providerList[j], providerList[j + 1]);
        }
    }
}
#endif