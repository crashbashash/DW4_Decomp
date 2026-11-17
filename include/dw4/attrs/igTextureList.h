#ifndef DW4_IGTEXTURELIST_H
#define DW4_IGTEXTURELIST_H

struct igMetaObject;
struct igTextureList;

#ifdef __cplusplus
extern "C" {
#endif

struct igTextureList *igTextureList_CreateInstance(int allocator);
struct igMetaObject *igTextureList_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
