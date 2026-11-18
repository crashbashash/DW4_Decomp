#ifndef DW4_IGATTRDEFAULTMANAGER_H
#define DW4_IGATTRDEFAULTMANAGER_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igAttrDefaultManager_EnsureRegistered(void);
struct igMetaObject *igAttrDefaultManager_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
