#ifndef DW4_IGPICKMODE_H
#define DW4_IGPICKMODE_H

struct igMetaObject;
struct igPickMode;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igPickMode_metaObject;
struct igPickMode *igPickMode_Create(int allocator);

#ifdef __cplusplus
}
#endif

#endif
