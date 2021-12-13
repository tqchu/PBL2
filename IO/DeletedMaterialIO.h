#ifndef DELETEDMATERIALIO_H
#define DELETEDMATERIALIO_H
#include "D:/PBL2/src/List.h"
#include "D:/PBL2/src/Material.h"
#include "D:/PBL2/src/utils.h"
#include "BaseIO.h"
class DeletedMaterialIO:public BaseIO<Material>{
public:
    DeletedMaterialIO();
    virtual void insertRow(const Material &material, ofstream &out);
    virtual Material getRow(string &dataText) const;
};

#endif