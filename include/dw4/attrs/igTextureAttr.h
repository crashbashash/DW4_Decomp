#ifndef DW4_IGTEXTUREATTR_H
#define DW4_IGTEXTUREATTR_H

struct igImage;
struct igMetaObject;
struct igTextureAttr;

#ifdef __cplusplus
extern "C" {
#endif

struct igTextureAttr *igTextureAttr_CreateInstance(int allocator);
struct igImage *igTextureAttr_GetImage(struct igTextureAttr *attr, int level);
struct igMetaObject *igTextureAttr_GetOrCreateMetaObject(void);
void igTextureAttr_SetImage(struct igTextureAttr *attr, struct igImage *image, int level);

#ifdef __cplusplus
}
#endif

#endif
