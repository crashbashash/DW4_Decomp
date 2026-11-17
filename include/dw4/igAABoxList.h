#ifndef DW4_IGAABOXLIST_H
#define DW4_IGAABOXLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
void igAABoxList_EnsureRegistered(void);
struct igMetaObject *igAABoxList_GetOrCreateMetaObject(void);
#ifdef __cplusplus
}
#endif

#endif
