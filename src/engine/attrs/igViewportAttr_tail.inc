void Gap__Attrs__igViewportAttr__vfunc_24(int *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_185(arg1, arg0[3], arg0[4], arg0[5], arg0[6], *(float *)&arg0[8], *(float *)&arg0[9]);
}

void Gap__Attrs__igViewportAttr__vfunc_26(igViewportAttr *arg0, void **arg1) {
    int sp3C;
    int sp38;
    int sp34;
    int sp30;
    float sp2C;
    float sp28;

    ((DW4VC_748_6 *)(arg1))->vX(&sp3C, &sp38, &sp34, &sp30, &sp2C, &sp28);
    arg0->_x = sp3C;
    arg0->_y = sp38;
    arg0->_w = sp34;
    arg0->_h = sp30;
    arg0->_nearZ = sp2C;
    arg0->_farZ = sp28;
}

