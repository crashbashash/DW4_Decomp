#ifndef DW4_META_OBJECT_H
#define DW4_META_OBJECT_H

#include "dw4/reflected.h"

inline bool igMetaObject_IsRegistered(igMetaObject *meta) {
    return (meta->_validity & 4) != 0;
}

#endif
