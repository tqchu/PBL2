#ifndef MATERIALIO_H
#define MATERIALIO_H
#include "BaseIO.h"
#include "D:/PBL2/src/Material.h"
#include "D:/PBL2/src/IO/CategoryIO.h"
#include "D:/PBL2/src/IO/ManufacturerIO.h"
#include "D:/PBL2/src/utils.h"
#include "D:/PBL2/src/List.h"
#include "D:/PBL2/src/Find.h"
class ManufacturerIO;
class MaterialIO : public BaseIO<Material>
{
    /** inherited from BaseIO
     *  getList(), update()
     *  path,title
     * */
public:
    MaterialIO();
    virtual void insertRow(const Material &material, ofstream &out) const;
    virtual Material getRow(string &dataText) const;
};
#endif