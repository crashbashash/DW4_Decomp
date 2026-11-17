#ifndef DW4_IGINTLIST_H
#define DW4_IGINTLIST_H

/* igIntList: the list class's registration. */

#ifdef __cplusplus
extern "C" {
#endif

int igIntList_GetOrCreateMetaObject(void);
void igIntList_EnsureRegistered(void);

#ifdef __cplusplus
}
#endif

#endif
