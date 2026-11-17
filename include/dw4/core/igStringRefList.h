#ifndef DW4_IGSTRINGREFLIST_H
#define DW4_IGSTRINGREFLIST_H

/* igStringRefList: the list class's registration. */
#include "dw4/core/igTDataList.h"
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igStringRefList_GetOrCreateMetaObject(void);
void igStringRefList_EnsureRegistered(void);
void StringList_Resize(igTDataList<char *> *list, int count);

#ifdef __cplusplus
}
#endif

#endif
