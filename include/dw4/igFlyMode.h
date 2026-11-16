#ifndef DW4_IGFLYMODE_H
#define DW4_IGFLYMODE_H

struct igMetaObject;
struct igFlyMode;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igFlyMode_metaObject;
struct igFlyMode *igFlyMode_Create(int allocator);

#ifdef __cplusplus
}
#endif

#endif
