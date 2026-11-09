#include "dw4/reflected.h"
extern "C" int igObject_Destroy(igObject *);
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer() : p(0) {}
    ~igSmartPointer() {
        T *o = p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    igSmartPointer &operator=(T *object) {
        T *old;
        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
        old = p;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        p = object;
        return *this;
    }
    T *get() const { return p; }
};
extern "C" {
igObject *igMetaObject_FindFieldByName(igObject *, int);
igObject *igObjectSystem_FindMetaByNameDefault(int);
void Gap__igDataPump__vfunc_17(igDataPump *pump) {
    igSmartPointer<igObject> meta;
    meta = igObjectSystem_FindMetaByNameDefault(pump->_destMetaClassName);
    if (meta.get() != 0) {
        igObject *field = igMetaObject_FindFieldByName(meta.get(), pump->_destMetaFieldName);
        igObject *old;
        if (field != 0) {
            field->_refCount = field->_refCount + 1;
        }
        old = (igObject *)pump->_destMeta;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        pump->_destMeta = (int)field;
    }
}
}
