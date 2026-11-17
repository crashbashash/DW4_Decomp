#ifndef DW4_IGCAMERA_H
#define DW4_IGCAMERA_H

struct igCamera;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igCamera_metaObject;
struct igCamera *igCamera_CreateInstance(int allocator);
struct igMetaObject *igCamera_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
