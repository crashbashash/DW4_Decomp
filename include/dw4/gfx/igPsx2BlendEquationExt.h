#ifndef DW4_IGPSX2BLENDEQUATIONEXT_H
#define DW4_IGPSX2BLENDEQUATIONEXT_H

struct igPsx2BlendEquationExt;

#ifdef __cplusplus
extern "C" {
#endif

void igPsx2BlendEquationExt_SetBlendFactors(struct igPsx2BlendEquationExt *self, int blendA, int blendB, int blendC, int blendD, char blendConstant);

#ifdef __cplusplus
}
#endif

#endif
