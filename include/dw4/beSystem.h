#ifndef DW4_BESYSTEM_H
#define DW4_BESYSTEM_H

struct beSystem;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSystem *beSystem_CreateInstance(int allocator);
void beSystem_EnsureRegistered(void);
struct igMetaObject *beSystem_GetOrCreateMetaObject(void);
int beSystem_IsRunning(struct beSystem *self);

extern struct igMetaObject *g_beSystem_metaObject;

#ifdef __cplusplus
}
#endif

#endif
