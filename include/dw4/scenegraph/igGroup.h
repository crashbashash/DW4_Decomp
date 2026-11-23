#ifndef DW4_IGGROUP_H
#define DW4_IGGROUP_H

struct CallbackArray;
struct igGroup;
struct igMetaObject;
struct igNode;

#ifdef __cplusplus
extern "C" {
#endif

struct igGroup *igGroup_Destroy(struct igGroup *self, short deleteFlag);
extern int g_igGroup_vtable[4];

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "dw4/core/igSmartPointer.h"
/* The removed child, still holding the reference the group dropped. */
#endif

#endif
