#ifndef DW4_BESECTL_H
#define DW4_BESECTL_H

struct beSeCtl;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSeCtl *beSeCtl_CreateInstance(int allocator);

extern struct igMetaObject *g_beSeCtl_metaObject;

#ifdef __cplusplus
}
#endif

#endif
