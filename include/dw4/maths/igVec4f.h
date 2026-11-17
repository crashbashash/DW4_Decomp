#ifndef DW4_IGVEC4F_H
#define DW4_IGVEC4F_H

struct Color4f;

#ifdef __cplusplus
extern "C" {
#endif
int igVec4f_PackColor(const float *color, unsigned int format);
void Color4f_Unpack(struct Color4f *out, unsigned int format, unsigned int packed);
#ifdef __cplusplus
}
#endif

#endif
