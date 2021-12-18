#ifndef MANUFACTURERIO_H
#define MANUFACTURERIO_H

#include "BaseIO.h"
#include "D:/PBL2/src/Entity/Manufacturer.h"
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/Common/List.h"
#include "D:/PBL2/src/Common/Find.h"
#include "MaterialIO.h"
class ManufacturerIO : public BaseIO<Manufacturer>
{
public:
    ManufacturerIO();
    virtual void insertRow(const Manufacturer &manufacturer, ofstream &out) const;
    virtual Manufacturer getRow(string &dataText) const;
};

#endif