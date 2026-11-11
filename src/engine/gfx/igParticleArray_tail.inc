int Gap__Gfx__igParticleArray__vfunc_28(PA *arg0, int arg1, int arg2, int *arg3, float fparg0) {
    int sp70[8];
    int temp_s0;
    O44 *a;
    O44 *t;
    O48 *b;
    O48 *u;
    arg0->f28 = fparg0;
    if (!(fparg0 <= arg0->f24 + arg0->f84)) {
        *arg3 = 1;
        return 1;
    }
    if (fparg0 < arg0->f20) {
        *arg3 = 2;
        return 1;
    }
    DAT_00560668[0] += 1;
    if (arg0->f44 == 0) {
        if (arg0->f44 == 0) {
            a = (O44 *)FUN_00166d40();
            if (a != 0) {
                a->refs = a->refs + 1;
            }
            t = arg0->f44;
            if (t != 0) {
                t->refs = t->refs - 1;
                if (((unsigned long long)((long long)t->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
            arg0->f44 = a;
            if (arg0->f73 != 0 && arg0->f8->f32 != 0 && arg0->f48 == 0) {
                b = arg0->f44->v104(&DAT_004dc000[0]);
                if (b != 0) {
                    b->refs = b->refs + 1;
                }
                u = arg0->f48;
                if (u != 0) {
                    u->refs = u->refs - 1;
                    if (((unsigned long long)((long long)u->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(u);
                    }
                }
                arg0->f48 = b;
            }
        }
        if (arg0->f44 != 0) {
            if (arg0->f73 == 0) {
                arg0->v92((int)arg0->f8, arg0->f12, arg0->f44, arg0->f20, arg0->f24);
            }
            goto L24;
        }
        *arg3 = 1;
        return 0;
    }
L24:
    arg0->f56 = arg1;
    arg0->f88 = arg1;
    arg0->f52 = arg2;
    FUN_0015db90(sp70);
    sp70[1] = 0;
    sp70[0] = 0;
    arg0->f40->v108(sp70, 1);
    arg0->f40->v112(sp70, 2);
    temp_s0 = arg0->f8->f44 > 0;
    if (arg0->f72 == 0 && temp_s0 == 0) {
        FUN_0015b880(arg0);
    }
    if (arg0->f76 != 0) {
        if (arg0->f48 != 0) {
            arg0->f48->v136(arg0->f8->f36);
        }
        arg0->f76(fparg0, arg1, arg2, arg0->f36, arg0->f32, arg0->f40, arg0->f48);
    } else if (temp_s0 == 0) {
        FUN_0015bc20(arg0, temp_s0, 1);
    } else {
        FUN_0015bc20(arg0, temp_s0, 0);
    }
    arg0->f72 = 1;
    *arg3 = 0;
    return 1;
}

