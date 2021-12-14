#ifndef BASEUTILS_H
#define BASEUTILS_H
#include "D:/PBL2/src/IO/BaseIO.h"
#include "D:/PBL2/src/IO/IOImplementation.h"
template <typename T>
class BaseUtils{
    protected:
        BaseIO<T> *io;
        string title;
        ArrayList<T> list;
        ArrayList<T> virtualList;

    public:
        BaseUtils();
        void manage();
        void display();
        // sub-method của manage
        virtual void control()=0;
         // sub-method của display
        virtual void printTitle()=0;
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
void BaseUtils<T>::manage(){
    printBox(title);
    display();
    control();
}
template <typename T>
void BaseUtils<T>::display(){

    printHyphen(lineWidth);
    // in tiêu đề
    printTitle();
    // in ds
    cout << virtualList;
    printHyphen(lineWidth);
}
#endif

