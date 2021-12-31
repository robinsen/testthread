#include "dclass_p.h"
#include <iostream>

DClassPrivate::DClassPrivate(DClass *qptr, QObject *parent):
    q_ptr(qptr),
    QObject(parent)
{
    connect(this, SIGNAL(testsignal()), this, SLOT(on_signal()));
}

void DClassPrivate::fool()
{
    emit testsignal();
}

void DClassPrivate::on_signal()
{
    std::cout<<" test d ptr && qpr "<<std::endl;
}
