#ifndef BASEUTILS_H
#define BASEUTILS_H
#include "D:/PBL2/src/IO/BaseIO.h"
#include "D:/PBL2/src/Common/Comparator.h"
#include "D:/PBL2/src/IO/IOImplementation.h"
#include "D:/PBL2/src/Common/Find.h"

template <typename T>
class BaseUtils{
    protected:
        BaseIO<T> *io;
        string title;
        ArrayList<T> list;
        ArrayList<T> virtualList;

    public:
        BaseUtils();
        ~BaseUtils();
        void manage();
        void display();
        
        template <typename U>
        U getElement(const ArrayList<U> &list);

        // sub-method của manage
        virtual void control()=0;
         // sub-method của display
        virtual void add()=0;
        virtual void update()=0;
        virtual void sort()=0;
        virtual void search()=0;
};
template <typename T>
BaseUtils<T>::BaseUtils(){
    title = "QUAN LY ";
}
template <typename T>

BaseUtils<T>::~BaseUtils(){
    delete io;
}
template <typename T>
void BaseUtils<T>::manage(){
    printBox(title);
    display();
    control();
}
template <typename T>
void BaseUtils<T>::display(){

    printHyphen(lineWidth);
    // in tiêu đề
    T::printTitle();
    // in ds
    cout << virtualList;
    printHyphen(lineWidth);
}

// HÀM NHỎ

/**
 * Hàm lấy element trong 1 list từ id người dùng nhập
 * @param list danh sách cần kiểm tra
 * @return t
 */
template <typename T>
template <typename U>
U BaseUtils<T>::getElement(const ArrayList<U> &list)
{
    U t;
    string idString;
    int id;
    while (true)
    {
        // GET chuỗi và trim
        getline(cin, idString);
        idString = trim(idString);

        try
        { // Chuyển chuỗi thành số
            // throw invalid_input exception
            id = toNumber(idString, "Ma");

            // Get element từ list, và thoát khỏi vòng lặp
            // throw non_existent_element
            t = list.get(findById, id);
            return t;
        }
        catch (invalid_input &exception)
        {
            cout << exception.get_info();
        }
        catch (non_existent_element &exception)
        {
            cout << "Ma khong ton tai!";
        }
        // Nếu xảy ra 1 trong 2 exception ở trên
        cout << " Vui long nhap lai: ";
    }
}
#endif

