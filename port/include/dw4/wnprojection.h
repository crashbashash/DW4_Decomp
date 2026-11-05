#ifndef DW4_WNPROJECTION_H
#define DW4_WNPROJECTION_H
/* p2 mode-three upload (1fbce0) and the VU viewport path. The captured retail
 * context uses guard-band factor 6, with nearest scalar reciprocal and
 * toward-zero multiply/add. This is the verified emulator reference policy;
 * it does not establish physical EE/VU rounding on every input. */
void dw4_wn_projection_normalize(const float projection[16],float normalized[16]);
void dw4_wn_projection_xy(const float camera[4],const float normalized[16],float xy[2]);
/* Dimension is signed (negative for Y), origin is the positive GS origin.
 * Return the raw GS position after FTOI4; callers subtract XYOFFSET. W > 0. */
float dw4_wn_viewport(float normalized,float clip_w,float dimension,float origin);
#endif
