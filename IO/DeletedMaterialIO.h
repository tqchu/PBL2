#ifndef DELETEDMATERIALIO_H
#define DELETEDMATERIALIO_H
#include "D:/PBL2/src/Entity/Material.h"
#include "D:/PBL2/src/Common/List.h"
#include "D:/PBL2/src/Common/utils.h"
#include "BaseIO.h"
class DeletedMaterialIO:public BaseIO<Material>{
public:
    DeletedMaterialIO();
    virtual void insertRow(const Material &material, ofstream &out) const;
    virtual Material getRow(string &dataText) const;
};

#endif