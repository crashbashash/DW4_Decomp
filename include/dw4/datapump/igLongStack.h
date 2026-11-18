#ifndef DW4_IGLONGSTACK_H
#define DW4_IGLONGSTACK_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void igLongStack_EnsureRegistered(void);
struct igMetaObject *igLongStack_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
