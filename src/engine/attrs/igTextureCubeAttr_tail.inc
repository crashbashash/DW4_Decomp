void Gap__Attrs__igTextureCubeAttr__vfunc_24(int *arg0, int *arg1) {
    int a4 = arg0[9];
    if (a4 < 0) {
        switch (arg0[24]) {
        case 0:
            if (((VB_141080 *)arg1)->v148(0x15, 2) != 0 && arg0[18] != 0) {
                arg0[24] = 1;
            } else {
                arg0[24] = 2;
            }
            ((VA_141080 *)arg0)->v96(arg1);
            break;
        case 1:
            if (a4 < 0) {
                arg0[24] = 2;
                ((VA_141080 *)arg0)->v96(arg1);
            }
            break;
        case 2:
            Gap__Attrs__igTextureAttr__vfunc_24();
            break;
        }
        if (arg0[9] >= 0) {
            goto b14;
        }
    } else {
b14:
        Gap__Attrs__igTextureAttr__vfunc_24(arg0, arg1);
    }
}

void Gap__Attrs__igTextureCubeAttr__vfunc_12(void **arg0) {
    Gap__Attrs__igTextureAttr__vfunc_12(arg0);
}

void FUN_00141190(int *arg0, int arg1) {
    int i;
    R_141190 *p;
    if (arg1 == 1) {
        for (i = 0; i < 6; i++) {
            p = (R_141190 *)arg0[18 + i];
            if (p != 0) {
                if (p != 0) {
                    p->refs = p->refs - 1;
                    if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(p);
                    }
                }
                arg0[18 + i] = 0;
            }
        }
    } else if (arg1 == 2) {
        FUN_00140ad0((T_140ad0 *)arg0, (int *)0, 0);
    }
}

