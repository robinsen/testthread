#include "dclass.h"
#include "dclass_p.h"

DClass::DClass(QObject *parent):
    QObject(parent),
    d_ptr(new DClassPrivate(this))
{

}

DClass::~DClass()
{
    DPTR(DClass);
    delete d;
}

void DClass::testFool()
{
   DPTR(DClass);
   d->fool();
}
