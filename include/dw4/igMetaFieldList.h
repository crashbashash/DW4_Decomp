#ifndef DW4_IGMETAFIELDLIST_H
#define DW4_IGMETAFIELDLIST_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif
void igMetaFieldList_EnsureRegistered(void);
struct igMetaObject *igMetaFieldList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
