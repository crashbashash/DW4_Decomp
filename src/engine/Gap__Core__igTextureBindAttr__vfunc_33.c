#include "dw4/reflected.h"
int igObject_Destroy();

/* slot 33 of igTextureBindAttr: set the _texture reference (+12). Reference-counted assignment:
 * retain the new object, release the old one (destroying it when its 23-bit count reaches zero),
 * then store the new one. */
void Gap__Core__igTextureBindAttr__vfunc_33(igTextureBindAttr *self, igObject *texture) {
    igObject *previousTexture;
    if (texture != 0) {
        texture->_refCount = texture->_refCount + 1;
    }
    previousTexture = (igObject *)(self->_texture);
    if (previousTexture != 0) {
        previousTexture->_refCount = previousTexture->_refCount - 1;
        if ((previousTexture->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousTexture);
        }
    }
    self->_texture = (int)texture;
}
