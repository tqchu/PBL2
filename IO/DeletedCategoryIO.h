#ifndef DELETEDCATEGORYIO_H
#define DELETEDCATEGORYIO_H
#include "CategoryIO.h"
class DeletedCategoryIO:public BaseIO<Category>{
    public:
        DeletedCategoryIO();
        virtual void insertRow(const Category &t, ofstream &out) const;
        virtual Category getRow(string &dataText) const;
};
#endif