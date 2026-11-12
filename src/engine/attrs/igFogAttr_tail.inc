void Gap__Attrs__igFogAttr__vfunc_24(igFogAttr *arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_245(arg1, (unsigned int)arg0->_mode);
    Gap__Gfx__igPsx2VisualContext__vfunc_243(arg1, arg0->_density);
    Gap__Gfx__igPsx2VisualContext__vfunc_247(arg1, arg0->_color);
    Gap__Gfx__igPsx2VisualContext__vfunc_249(arg1, arg0->_nearVal);
    Gap__Gfx__igPsx2VisualContext__vfunc_251(arg1, arg0->_farVal);
}

void Gap__Attrs__igFogAttr__vfunc_26(F_13cd90 *arg0, C *arg1) {
    float v[4];
    float t;

    arg0->w12 = arg1->f244();
    arg0->f24 = arg1->f242();
    arg1->f246(v);
    arg0->f28 = v[0];
    arg0->f32 = v[1];
    arg0->f36 = v[2];
    arg0->f40 = v[3];
    t = arg1->f250();
    arg0->f16 = arg1->f248();
    arg0->f20 = t;
}

