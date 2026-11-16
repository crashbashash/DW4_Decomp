#ifndef DW4_IGIMAGE_H
#define DW4_IGIMAGE_H

struct igImage;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igImage_metaObject;
struct igImage *igImage_CreateInstance(int allocator);
struct igMetaObject *igImage_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
