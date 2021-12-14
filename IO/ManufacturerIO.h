#ifndef MANUFACTURERIO_H
#define MANUFACTURERIO_H

#include "BaseIO.h"
#include "D:/PBL2/src/Manufacturer.h"
#include "D:/PBL2/src/utils.h"
#include "D:/PBL2/src/List.h"
#include "D:/PBL2/src/Find.h"
#include "MaterialIO.h"
class ManufacturerIO : public BaseIO<Manufacturer>
{
    /** inherited from BaseIO
     *  getList(), update()
     *  path,title
     * */
public:
    ManufacturerIO();
    virtual void insertRow(const Manufacturer &manufacturer, ofstream &out) const;
    virtual Manufacturer getRow(string &dataText) const;
};

#endif