#ifndef DW4_IGMATRIXSTACK_H
#define DW4_IGMATRIXSTACK_H

/* igMatrixStack: a list of 4x4 float matrices whose last entry is the top. The push forms copy the
 * top (or the matrix itself on an empty stack) and return the index the stack had before. */
struct igMatrixStack;

#ifdef __cplusplus
extern "C" {
#endif
int igMatrixStack_PushPreMultiply(struct igMatrixStack *self, const float *matrix);
int igMatrixStack_PushPostMultiply(struct igMatrixStack *self, const float *matrix);
void igMatrixStack_PreMultiply(struct igMatrixStack *self, const float *matrix);
void igMatrixStack_PostMultiply(struct igMatrixStack *self, const float *matrix);
#ifdef __cplusplus
}
#endif

#endif
