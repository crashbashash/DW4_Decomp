#ifndef DW4_IGTEXTURECOORDSOURCEATTR_H
#define DW4_IGTEXTURECOORDSOURCEATTR_H

struct igTextureCoordSourceAttr;
struct igMemoryPoolView;

#ifdef __cplusplus
extern "C" {
#endif

struct igTextureCoordSourceAttr *igTextureCoordSourceAttr_Create(struct igMemoryPoolView *pool);

struct igMetaObject *igTextureCoordSourceAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}
#endif

#endif
