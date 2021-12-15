#ifndef BASEIO_H
#define BASEIO_H
#include <fstream>
#include "D:/PBL2/src/Common/List.h"
template <typename T>
class BaseIO
{
protected:
    string path;
    string title;
public:
    virtual void insertRow(const T &t, ofstream &out) const ;
    virtual T getRow(string &dataText) const  ;
   void update(const ArrayList<T> &list) const ;
   ArrayList<T> getList();
};

template <typename T>
void BaseIO<T>::update(const ArrayList<T> &list) const
{
    // mở file ghi đè
    ofstream out(path);
    // in lại title ( tiêu đề)
    out << title;
    // in lại toàn bộ ds mới
    for (int i = 0; i < list.size; i++)
        insertRow(list[i], out);
    // đóng file
    out.close();
}
template <typename T>
ArrayList<T> BaseIO<T>::getList()
{
    ArrayList<T> list;
    // dùng để lưu từng line trong file
    string dataText;
    ifstream src(path);
    // đọc 1 dòng thừa
    getline(src, dataText);


    // bắt đầu đọc dữ liệu
    while (getline(src, dataText))
    {   
        T t = getRow(dataText);
        list.add(t);

    }
    src.close();
    return list;
}
template <typename T>
void BaseIO<T>::insertRow(const T &t, ofstream &out) const{
}
template <typename T>
T BaseIO<T>::getRow(string &dataText) const
{
    T t;
    return t;
}
#endif