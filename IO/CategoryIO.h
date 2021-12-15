#ifndef CATEGORYIO_H
#define CATEGORYIO_H
#include "BaseIO.h"
#include "D:/PBL2/src/Entity/Category.h"
#include "D:/PBL2/src/Common/utils.h"
#include "D:/PBL2/src/Common/List.h"
#include "D:/PBL2/src/Common/Find.h"
#include "MaterialIO.h"

class CategoryIO : public BaseIO<Category>
{
    /** inherited from BaseIO
     *  getList(), update()
     *  path,title
     * */
public:
    CategoryIO();
    virtual void insertRow(const Category &category, ofstream &out) const;
    virtual Category getRow(string &dataText) const;
};

#endif