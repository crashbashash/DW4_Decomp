#ifndef DW4_BEACTIONSTARTER_H
#define DW4_BEACTIONSTARTER_H

struct beActionStarter;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beActionStarter *beActionStarter_CreateInstance(int allocator);

extern struct igMetaObject *g_beActionStarter_metaObject;

#ifdef __cplusplus
}
#endif

#endif
