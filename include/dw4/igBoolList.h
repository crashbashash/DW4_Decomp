#ifndef DW4_IGBOOLLIST_H
#define DW4_IGBOOLLIST_H

/* igBoolList: the list class's registration. */
struct igMetaObject;
struct igBoolList;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igBoolList_GetOrCreateMetaObject(void);
struct igBoolList *igBoolList_Create(int pool);

#ifdef __cplusplus
}
#endif

#endif
