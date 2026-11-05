#ifndef DW4_WNDEPTH_H
#define DW4_WNDEPTH_H
/* STATUS's 16-bit GS depth range, derived from authored projections and retail
 * XYZF2. Larger depth is nearer. Callers provide positive homogeneous W. */
float dw4_wn_depth(float clip_z,float clip_w,float near_z,float far_z);
#endif
