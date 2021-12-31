#pragma once

#include <QObject>


template <typename T> static inline T *GetPtrHelper(T *ptr) { return ptr; }

#define DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private*>(GetPtrHelper(d_ptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private*>(GetPtrHelper(d_ptr)); }\
    friend class Class##Private;

#define DPTR(Class) Class##Private * const d  = d_func()

class DClassPrivate;

class DClass : public QObject {
    Q_OBJECT
public:
    explicit DClass(QObject* parent=0);
    virtual ~DClass();

    void testFool();

protected:
    DClass(DClassPrivate &d);

private:
    DClassPrivate* const d_ptr;
    DECLARE_PRIVATE(DClass)
    DClass(const DClass&);
    DClass& operator =(const DClass&);
};
