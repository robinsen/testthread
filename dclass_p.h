#pragma once

#include <QObject>
#include "dclass.h"

#define DECLARE_PUBLIC(Class) \
    inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class;

#define QPTR(Class) Class * const q = q_func()

class DClassPrivate : public QObject {
    Q_OBJECT
public:
    explicit DClassPrivate(DClass* qptr, QObject* parent=0);
    virtual ~DClassPrivate(){}

    void fool();

signals:
    void testsignal();

public slots:
    void on_signal();

private:
    DClass* const q_ptr;
    DECLARE_PUBLIC(DClass)
};
