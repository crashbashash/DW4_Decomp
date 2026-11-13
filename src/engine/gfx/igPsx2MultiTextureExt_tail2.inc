/* Setter: stores the owning visual context in the extension's `_context`. */

void Gap__Gfx__igPsx2MultiTextureExt__vfunc_29(igPsx2MultiTextureExt *self, int context) {
    self->_context = context;
}

void Gap__Gfx__igPsx2MultiTextureExt__vfunc_30(igPsx2MultiTextureExtView *self, int unit, int, int mode)
{
    self->_context->vfunc_146(unit, DAT_004df5e0[mode]);
}

void Gap__Gfx__igPsx2MultiTextureExt__vfunc_31(int a0, int a1, int a2, int a3) {
    *(int *)((char *)a0 + 24) = (int)a3;
    FUN_0016fea0((A_16fea0 *)a0, a1, a2, a3);
}

void Gap__Gfx__igPsx2MultiTextureExt__vfunc_32(void) {
}

void FUN_0016fea0(A_16fea0 *arg0, int arg1, int arg2, int arg3) {
    int var_a0;
    unsigned int temp_v1;

    if (arg1 > 1) {
        var_a0 = arg1 - 1;
    } else {
        var_a0 = 0;
    }
    p2CurrentProgram[0] = arg1;
    p2CurrentGsRegisters[0] = &p2GsRegisterSets[0] + var_a0;
    if (arg0->f28 != 0) {
        p2SetBlendEquation(arg0->f32, arg0->f36, arg0->f40, arg0->f44, arg0->f48);
    } else {
        temp_v1 = arg0->f24;
        switch (temp_v1) {
        case 0:
            p2SetBlendEquation(0, 2, 2, 2, 0x80U);
            break;
        case 2:
            p2SetBlendEquation(0, 2, 2, 1, 0x80U);
            break;
        case 3:
            p2SetBlendEquation(0, 1, 2, 2, 0x80U);
            break;
        case 4:
            p2SetBlendEquation(1, 0, 2, 2, 0x80U);
            break;
        case 1:
            p2SetBlendEquation(0, 2, 0, 2, 0x80U);
            break;
        case 5:
            p2SetBlendEquation(0, 2, 0, 1, 0x80U);
            break;
        case 6:
            p2SetBlendEquation(0, 1, 0, 2, 0x80U);
            break;
        case 7:
            p2SetBlendEquation(1, 0, 0, 2, 0x80U);
            break;
        case 8:
            p2SetBlendEquation(0, 2, 1, 2, 0x80U);
            break;
        case 9:
            p2SetBlendEquation(0, 2, 1, 1, 0x80U);
            break;
        case 10:
            p2SetBlendEquation(0, 1, 1, 2, 0x80U);
            break;
        case 11:
            p2SetBlendEquation(1, 0, 1, 2, 0x80U);
            break;
        }
    }
    p2CurrentProgram[0] = 0;
    p2CurrentGsRegisters[0] = &p2GsRegisterSets[0];
}

