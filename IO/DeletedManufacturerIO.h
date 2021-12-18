#ifndef DELETEDMANUFACTURERIO_H
#define DELETEDMANUFACTURERIO_H
#include "BaseIO.h"

class DeletedManufacturerIO:public BaseIO<Manufacturer>{

public:
    DeletedManufacturerIO();
    virtual void insertRow(const Manufacturer &manufacturer, ofstream &out) const;
    virtual Manufacturer getRow(string &dataText) const;
};
#endif