void Gap__Gfx__igPsx2VisualContext__vfunc_261(int *arg0, int *arg1, int arg2) {
    int *old;
    int *slot;
    int idx;

    if (arg1 != 0) {
        arg1[1] = arg1[1] + 1;
    }
    idx = arg2 * 4;
    idx = idx + (int)arg0;
    slot = (int *)(idx + 240);
    old = (int *)*slot;
    if (old != 0) {
        old[1] = old[1] - 1;
        if ((old[1] & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = (int)arg1;
    if (arg1 != 0) {
        ((Obj_17dea0 *)arg0)->vX(0);
    }
}

bool FUN_0017e590(Self_17e590 *arg0, int arg1, int arg2, int *arg3, int *arg4) {
    Node *n2; VC_17e590 *s; VC_17e590 *r; VC_17e590 *o2;
    bool var_s2 = false;
    Node *n = (Node *)FUN_0015f4a0((S_15f430 *)arg1, 9, 0);
    if (n != 0) {
        if (n->obj->vX() == g_igFloatList_metaObject[0]) {
            *arg3 = n->obj->f16;
            FUN_001eb5e0(4, 0, 0, 0);
        } else if (n->obj->vX() == g_igVec2fList_metaObject[0]) {
            *arg3 = n->obj->f16;
            FUN_001eb5e0(4, 0, 0, 0);
        } else {
            VC_17e590 *o = n->obj;
            if (o->vX() == g_igCharList_metaObject[0]) {
                int a = n->f32;
                FUN_001eb5e0(4, 1, 7 - a, a);
                var_s2 = true;
                *arg3 = o->f16;
            } else if (o->vX() == g_igUnsignedCharList_metaObject[0]) {
                int a = n->f32;
                FUN_001eb5e0(4, 0, 8 - a, a);
                *arg3 = o->f16;
            } else if (o->vX() == g_igShortList_metaObject[0]) {
                int a = n->f32;
                FUN_001eb5e0(4, 1, 0xF - a, a);
                *arg3 = o->f16;
            } else if (o->vX() == g_igUnsignedShortList_metaObject[0]) {
                int a = n->f32;
                FUN_001eb5e0(4, 0, 0x10 - a, a);
                *arg3 = o->f16;
            }
        }
    } else {
        *arg3 = 0;
    }
    n2 = (Node *)FUN_0015f4a0((S_15f430 *)arg1, 4, 1);
    if (n2 != 0) {
        s = n2->obj;
        if (s != 0 && igObject_IsKindOf(s, g_igVec2fList_metaObject[0]) != 0) {
            r = s;
        } else {
            r = 0;
        }
        if (r != 0) {
            *arg4 = r->f16;
        } else {
            o2 = n2->obj;
            if (o2->vX() == g_igCharList_metaObject[0]) {
                int a = n2->f32;
                FUN_001eb5e0(2, 1, 7 - a, a);
                *arg4 = o2->f16;
            } else if (o2->vX() == g_igUnsignedCharList_metaObject[0]) {
                int a = n2->f32;
                FUN_001eb5e0(2, 0, 8 - a, a);
                *arg4 = o2->f16;
            } else if (o2->vX() == g_igShortList_metaObject[0]) {
                int a = n2->f32;
                FUN_001eb5e0(2, 1, 0xF - a, a);
                *arg4 = o2->f16;
            } else if (o2->vX() == g_igUnsignedShortList_metaObject[0]) {
                int a = n2->f32;
                FUN_001eb5e0(2, 0, 0x10 - a, a);
                *arg4 = o2->f16;
            }
        }
    } else {
        *arg4 = 0;
    }
    if (arg0->f944 == 0) {
        if (*arg3 != 0) *arg3 = *arg3 + arg2 * 4;
        if (*arg4 != 0) *arg4 = *arg4 + arg2 * 8;
    }
    return var_s2;
}

void FUN_0017e980(igPsx2VisualContext *h, int arg1, int arg2)
{
    int i;
    E_17e980 *e;
    int v;
    Obj_17e980 *o;

    if (h->_bMultiPassNum > 1 && h->_pixelPipelineMode == 3) {
        for (i = 1; i < h->_bMultiPassNum; i++) {
            e = (E_17e980 *)FUN_0015f4a0((S_15f430 *)arg1, 4, h->_texCoordIndex[i]);
            v = 0;
            if (e != 0) {
                o = e->obj;
                if (o != 0 && igObject_IsKindOf(o, g_igVec2fList_metaObject[0]) != 0) {
                    o = (Obj_17e980 *)o;
                } else {
                    o = 0;
                }
                if (o != 0) {
                    v = ((int *)o)[4];
                } else {
                    o = e->obj;
                    if (g_igCharList_metaObject[0] == o->meta()) {
                        FUN_001eb5e0(2, 1, 7 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if (g_igUnsignedCharList_metaObject[0] == o->meta()) {
                        FUN_001eb5e0(2, 0, 8 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if (g_igShortList_metaObject[0] == o->meta()) {
                        FUN_001eb5e0(2, 1, 15 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if (g_igUnsignedShortList_metaObject[0] == o->meta()) {
                        FUN_001eb5e0(2, 0, 16 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    }
                }
                if (h->_pIndexArray == 0) {
                    v += arg2 * 8;
                }
            }
            FUN_001f10c0(i, v);
        }
    }
}

void FUN_0017eb90(B_17eb90 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    int spBC;
    int spB8;
    int spB4;
    int spB0;
    int spAC;
    int spA8;
    int *var_s3;
    int var_s0;
    int var_s0_2;
    int var_s1;
    int var_s6;
    int temp_s7;
    struct C_17eb90 *c;

    c = arg0->f944;
    var_s1 = arg4;
    if (c != 0) {
        var_s0 = c->f12;
    } else {
        var_s0 = 0;
    }
    temp_s7 = FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4) & 0xFF;
    FUN_0017e980((igPsx2VisualContext *)arg0, arg1, var_s1);
    if ((temp_s7 != 0) || (arg6 != 0)) {
        FUN_001e74b0(0x1B);
    } else if (FUN_001e7560(0x1B) != 0) {
        FUN_001e7500(0x1B);
    }
    switch (arg2) {
    case 0x0:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        FUN_001f1120(arg3);
        break;
    case 0x1:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        FUN_001f14b0(arg3);
        break;
    case 0x2:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        FUN_001f1850(arg3);
        break;
    case 0x3:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        if (var_s0 == 0) {
            FUN_001f1c00(arg3);
        } else {
            FUN_001f3160(arg3, var_s0 + (var_s1 * 2));
        }
        break;
    case 0x4:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        if (var_s0 == 0) {
            FUN_001f1fe0(arg3);
        } else {
            FUN_001f2d90(arg3, var_s0 + (var_s1 * 2));
        }
        break;
    case 0x5:
        FUN_001f10f0(spBC, spB8, spAC, spB4);
        if (var_s0 == 0) {
            FUN_001f23a0(arg3);
        } else {
            FUN_001f3550(arg3, var_s0 + (var_s1 * 2));
        }
        break;
    case 0x1000:
        if (FUN_0017e590((Self_17e590 *)arg0, arg1, var_s1, &spA8, &spB0) && (temp_s7 == 0)) {
            FUN_001e74b0(0x1B);
        }
        FUN_001f10c0(1, spB0);
        FUN_001f10f0(spBC, spA8, spAC, spB4);
        if (var_s0 == 0) {
            FUN_001f3900(arg3);
        } else {
            FUN_001f3d00(arg3, var_s0 + (var_s1 * 2));
        }
        break;
    case 0x2000:
        var_s3 = arg0->f948->f8 + arg5;
        for (var_s0_2 = 0; var_s0_2 < arg3; var_s0_2++) {
            FUN_001f10f0(spBC, spB8, spAC, spB4);
            FUN_001f1850(*var_s3);
            var_s1 += *var_s3;
            var_s3 += 1;
            FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
            FUN_0017e980((igPsx2VisualContext *)arg0, arg1, var_s1);
        }
        break;
    case 0x2002:
        var_s3 = arg0->f948->f8 + arg5;
        for (var_s6 = 0; var_s6 < arg3; var_s6++) {
            FUN_001f10f0(spBC, spB8, spAC, spB4);
            if (var_s0 == 0) {
                FUN_001f23a0(*var_s3);
            } else {
                FUN_001f3550(*var_s3, var_s0 + (var_s1 * 2));
            }
            var_s1 += *var_s3;
            var_s3 += 1;
            FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
            FUN_0017e980((igPsx2VisualContext *)arg0, arg1, var_s1);
        }
        break;
    case 0x2001:
        var_s3 = arg0->f948->f8 + arg5;
        if (var_s0 == 0) {
            FUN_001f10f0(spBC, spB8, spAC, spB4);
            FUN_001f2730(arg3, var_s3);
        } else {
            for (var_s6 = 0; var_s6 < arg3; var_s6++) {
                FUN_001f10f0(spBC, spB8, spAC, spB4);
                FUN_001f2d90(*var_s3, var_s0 + (var_s1 * 2));
                var_s1 += *var_s3;
                var_s3 += 1;
                FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
                FUN_0017e980((igPsx2VisualContext *)arg0, arg1, var_s1);
            }
        }
        break;
    }
}

static inline void release_17f2b0(Rc_17f2b0 *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}

