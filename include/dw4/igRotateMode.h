#ifndef DW4_IGROTATEMODE_H
#define DW4_IGROTATEMODE_H

struct igMetaObject;
struct igRotateMode;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igRotateMode_metaObject;
struct igRotateMode *igRotateMode_Create(int allocator);

#ifdef __cplusplus
}
#endif

#endif
