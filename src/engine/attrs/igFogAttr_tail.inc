void igFogAttr_apply(igFogAttr *arg0, int arg1) {
    igPsx2VisualContext_SetFogMode((igPsx2VisualContext *)arg1, (unsigned int)arg0->_mode);
    igPsx2VisualContext_SetFogDensity((igPsx2VisualContext *)arg1, arg0->_density);
    igPsx2VisualContext_SetFogColor((igPsx2VisualContext *)arg1, &arg0->_color);
    igPsx2VisualContext_SetFogNear((igPsx2VisualContext *)arg1, arg0->_nearVal);
    igPsx2VisualContext_SetFogFar((igPsx2VisualContext *)arg1, arg0->_farVal);
}

void igFogAttr_SynchronizeDefault(F_13cd90 *arg0, C *arg1) {
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

