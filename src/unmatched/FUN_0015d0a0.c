/* Receiver: igPointSpriteExt (its sibling helpers at 0x15d050/0x15d070 read _spriteSize at +28;
 * the caller switches on _spriteSizeSpace at +36). */
#include "dw4/reflected.h"
void FUN_0015d0a0(igPointSpriteExt *arg0, int arg1, void *arg2) {
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(((igVertexArray *)(arg0->_vertexArray))->_vdata) + 60) + (arg1 * 8));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
}
