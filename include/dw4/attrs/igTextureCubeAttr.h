#ifndef DW4_IGTEXTURECUBEATTR_H
#define DW4_IGTEXTURECUBEATTR_H

struct igMetaObject;

/* The six faces of a cube texture, in the order of igTextureCubeAttr's _cubeImage array. */
enum CubeFaceID {
    FACE_NEG_X,
    FACE_POS_X,
    FACE_NEG_Y,
    FACE_POS_Y,
    FACE_NEG_Z,
    FACE_POS_Z
};

#ifdef __cplusplus
extern "C" {
#endif

void igTextureCubeAttr_EnsureRegistered(void);
struct igMetaObject *igTextureCubeAttr_GetOrCreateMetaObject(void);

#ifdef __cplusplus
}

#include "dw4/support/reflected.h"

static inline igImage *igTextureCubeAttr_GetCubeImage(igTextureCubeAttr *self, CubeFaceID face) {
    return (igImage *)self->_cubeImage[face];
}
#endif

#endif
