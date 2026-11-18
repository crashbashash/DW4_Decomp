#ifndef DW4_IGGUICOMPONENTLIST_H
#define DW4_IGGUICOMPONENTLIST_H

#ifdef __cplusplus
extern "C" {
#endif

void igGuiComponentList_EnsureRegistered(void);

struct igMetaObject *igGuiComponentList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
