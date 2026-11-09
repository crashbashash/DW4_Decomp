#include "dw4/igSmartPointer.h"

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
