void Gap__Attrs__igModelViewMatrixAttr__vfunc_24(char * arg0, int arg1) {
    Gap__Gfx__igPsx2VisualContext__vfunc_203(arg1, 1, (arg0 + 12));
}

void FUN_0013f670(void) {

}

X_13f680 *FUN_0013f680(void) { int s0, r1, r2; X_13f680 *t;
    if (DAT_0055f508[0] == 0) {
        if (g_useOwnerAllocator != 0) { r1 = Memory_GetAllocatorBySelector(DAT_00587028[0]); s0 = r1; } else { r2 = Memory_GetAllocatorBySelector(DAT_005870f8[0]); s0 = r2; }
        t = DAT_0055f508[0];
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        DAT_0055f508[0] = (X_13f680 *)FUN_001356b0(s0);
    }
    return DAT_0055f508[0];
}

void FUN_0013f730(void) {
    Q *p;

    p = (Q *)DAT_0055f508[0];
    if (p != 0) {
        p->f4 -= 1;
        if ((p->f4 & 0x7fffff) == 0) {
            igObject_Destroy(p);
        }
    }
    DAT_0055f508[0] = 0;
}

void Gap__Attrs__igModelViewMatrixAttr__vfunc_26(void *arg0, void *arg1) {
    float m[16];
    igMatrix44f_SetIdentity(m);
    ((VA *)arg1)->vX(1, m);
    ((VB_13f790 *)arg0)->vY(m);
}

void Gap__Attrs__igModelViewMatrixAttr__vfunc_32(int a0) {
    Matrix44_Copy((char *)a0 + 12);
}

void FUN_0013f800(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 20) = arg1;
}

