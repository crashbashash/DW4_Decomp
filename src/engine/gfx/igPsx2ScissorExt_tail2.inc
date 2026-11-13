/* Setter: stores the owning visual context in the extension's `_context`. */

void Gap__Gfx__igPsx2ScissorExt__vfunc_29(igPsx2ScissorExt *self, int context) {
    self->_context = context;
}

void Gap__Gfx__igPsx2ScissorExt__vfunc_30(int *arg0, int arg1) {
    int sp2C;
    int sp28;
    int sp24;
    int sp20;
    ((char *)arg0)[24] = arg1;
    if (arg1 != 0) {
        ((A_1700f0 *)arg0)->vX(arg0[7], arg0[8], arg0[9], arg0[10]);
        return;
    }
    sp2C = 0;
    sp24 = 0x280;
    sp28 = 0;
    sp20 = 0x1C0;
    ((B_1700f0 *)arg0[5])->vX(&sp2C, &sp28, &sp24, &sp20);
    ((A_1700f0 *)arg0)->vX(sp2C, sp28, sp24, sp20);
}

/* Reports whether scissoring is enabled: returns _scissorEnable (+24). */

unsigned char Gap__Gfx__igPsx2ScissorExt__vfunc_31(igPsx2ScissorExt *self) {
    return self->_scissorEnable;
}

void Gap__Gfx__igPsx2ScissorExt__vfunc_32(igPsx2ScissorExt *arg0, int arg1, int arg2, int arg3, int arg4) {
    arg0->_scissorOrgX = arg1;
    arg0->_scissorOrgY = arg2;
    arg0->_scissorWidth = arg3;
    arg0->_scissorHeight = arg4;
    p2SetScissor(arg1, arg2, arg3, arg4);
}

/* Getter for the scissor rectangle: origin and size into the four out parameters. */

void Gap__Gfx__igPsx2ScissorExt__vfunc_33(igPsx2ScissorExt *self, int *originX, int *originY, int *width, int *height) {
    *originX = self->_scissorOrgX;
    *originY = self->_scissorOrgY;
    *width = self->_scissorWidth;
    *height = self->_scissorHeight;
}

