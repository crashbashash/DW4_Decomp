#ifndef DW4_IGMOUSECURSOR_H
#define DW4_IGMOUSECURSOR_H

#ifdef __cplusplus
#include "dw4/core/igSmartPointer.h"
extern "C" {
#endif

void igMouseCursor_RunStaticInit(void);

struct igMetaObject *igMouseCursor_GetOrCreateMetaObject(void);

#ifdef __cplusplus
/* The out-of-line igSmartPointer<igMouseCursor> destructor the GUI system and the pick mode call by name. */
igSmartPointer<igObject> *igSmartPointer_igMouseCursor_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
}
#endif

#endif
