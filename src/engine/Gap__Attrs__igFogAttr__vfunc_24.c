#include "dw4/reflected.h"
int Gap__Gfx__igPsx2VisualContext__vfunc_245(int, int);
int Gap__Gfx__igPsx2VisualContext__vfunc_243(int, float);
int Gap__Gfx__igPsx2VisualContext__vfunc_247(int, void *);
int Gap__Gfx__igPsx2VisualContext__vfunc_249(int, float);
int Gap__Gfx__igPsx2VisualContext__vfunc_251(int, float);
void Gap__Attrs__igFogAttr__vfunc_24(igFogAttr *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_245(arg1, (unsigned int)arg0->_mode);
    Gap__Gfx__igPsx2VisualContext__vfunc_243(arg1, arg0->_density);
    Gap__Gfx__igPsx2VisualContext__vfunc_247(arg1, arg0->_color);
    Gap__Gfx__igPsx2VisualContext__vfunc_249(arg1, arg0->_nearVal);
    Gap__Gfx__igPsx2VisualContext__vfunc_251(arg1, arg0->_farVal);
}
