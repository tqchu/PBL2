#ifndef MATERIALIO_H
#define MATERIALIO_H
#include "BaseIO.h"
#include "D:/PBL2/src/Entity/Material.h"
#include "D:/PBL2/src/IO/CategoryIO.h"
#include "D:/PBL2/src/IO/ManufacturerIO.h"
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/Common/List.h"
#include "D:/PBL2/src/Common/Find.h"
class ManufacturerIO;
class MaterialIO : public BaseIO<Material>
{
public:
    MaterialIO();
    virtual void insertRow(const Material &material, ofstream &out) const;
    virtual Material getRow(string &dataText) const;
};
#endif
