#ifndef DW4_BESAVEMEMORYOBJ_H
#define DW4_BESAVEMEMORYOBJ_H

struct beSaveMemoryObj;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beSaveMemoryObj *beSaveMemoryObj_CreateInstance(int allocator);

extern struct igMetaObject *g_beSaveMemoryObj_metaObject;

#ifdef __cplusplus
}
#endif

#endif
