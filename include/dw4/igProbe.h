#ifndef DW4_IGPROBE_H
#define DW4_IGPROBE_H

struct igMetaObject;
struct igProbe;

#ifdef __cplusplus
extern "C" {
#endif

struct igProbe *igProbe_Create(int allocator);
void igProbe_EnsureRegistered(void);
struct igMetaObject *igProbe_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
