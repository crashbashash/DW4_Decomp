#ifndef DW4_BETIMER_H
#define DW4_BETIMER_H

struct beTimer;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beTimer *beTimer_CreateInstance(int allocator);

extern struct igMetaObject *g_beTimer_metaObject;

#ifdef __cplusplus
}
#endif

#endif
