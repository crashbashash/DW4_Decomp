void Gap__Gfx__igPsx2BlendEquationExt__vfunc_29(Obj_16e180 *arg0, int arg1) {
    if ((arg1 != 0) && (arg0->f24 == 0)) {
        arg0->f24 = arg1;
    }
}

void Gap__Gfx__igPsx2BlendEquationExt__vfunc_30(igPsx2BlendEquationExt *ext) {
    int source;
    int destination;

    if (ext->_equation == 2) {
        source = ((igBlendContextView *)ext->_context)->getBlendSource();
        destination = ((igBlendContextView *)ext->_context)->getBlendDestination();
        if (source == 8 && destination == 1) {
            p2SetBlendEquation(2, 0, 1, 1, 0);
        } else {
            p2SetBlendEquation(1, 0, 2, 2, 128);
        }
    } else if (ext->_equation == 1) {
        p2SetBlendEquation(0, 1, 2, 2, 128);
    } else if (ext->_equation == 4) {
        p2SetBlendEquation(ext->_blendA, ext->_blendB, ext->_blendC, ext->_blendD, ext->_blendConstant);
    }
}

void FUN_0016e290(igPsx2BlendEquationExt *arg0, int arg1, int arg2, int arg3, int arg4, char arg5) {
    arg0->_blendA = arg1;
    arg0->_blendB = arg2;
    arg0->_blendC = arg3;
    arg0->_blendD = arg4;
    arg0->_blendConstant = arg5;
}

