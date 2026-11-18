#ifndef DW4_IGRADIOGROUP_H
#define DW4_IGRADIOGROUP_H

#ifdef __cplusplus
extern "C" {
#endif

void igRadioGroup_EnsureRegistered(void);

struct igMetaObject *igRadioGroup_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
