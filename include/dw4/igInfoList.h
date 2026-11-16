#ifndef DW4_IGINFOLIST_H
#define DW4_IGINFOLIST_H

/* igInfoList: the list class's registration. */
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct igMetaObject *igInfoList_GetOrCreateMetaObject(void);
void igInfoList_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
