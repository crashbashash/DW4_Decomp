int FUN_001b2790(Obj_1b2750 *arg0, Dev *arg1) {
    if (igObject_IsKindOf(arg1, g_igTransformSequence_metaObject[0]) != 0) {
        Ref_1b2750 a((Obj_1b2750 *)FUN_0018a660(FUN_00301000(arg0)));
        FUN_00190060(a.o, arg0);
        Ref_1b2750 b((Obj_1b2750 *)FUN_0018a660(FUN_00301000(arg0)));
        Obj_1b2750 *p = b.o;
        p->f8 = p->f12 = p->f16 = 3.402823466e+38f;
        p->f20 = p->f24 = p->f28 = -3.402823466e+38f;
        unsigned n;
        unsigned i;
        n = arg1->count();
        char sp50[64];
        for (i = 0; i < n; i++) {
            igMatrix44f_SetIdentity(sp50);
            arg1->get(i, sp50);
            FUN_0018ac80(arg0, sp50);
            FUN_00190060(b.o, arg0);
            arg0->f8 = arg0->f12 = arg0->f16 = 3.402823466e+38f;
            arg0->f20 = arg0->f24 = arg0->f28 = -3.402823466e+38f;
            FUN_00190060(arg0, a.o);
        }
        arg0->f8 = arg0->f12 = arg0->f16 = 3.402823466e+38f;
        arg0->f20 = arg0->f24 = arg0->f28 = -3.402823466e+38f;
        FUN_00190060(arg0, b.o);
        return 1;
    }
    return 0;
}

int FUN_001b2ed0(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = (int)FUN_0018a660(((void *)igObject_GetAllocator((void *)arg1)));
    FUN_001b2f30((struct O_1b2750 *)arg0, arg1, (struct B_1b2750 *)temp_v0);
    return temp_v0;
}

void FUN_001b2f30(struct O_1b2750 *arg0, int arg1, struct B_1b2750 *arg2) {
    struct B_1b2750 *p;
    arg0->b17 = 0;
    arg2->f8 = arg2->f12 = arg2->f16 = 3.402823466e+38f;
    arg2->f20 = arg2->f24 = arg2->f28 = -3.402823466e+38f;
    p = arg0->f20;
    p->f8 = p->f12 = p->f16 = 3.402823466e+38f;
    p->f20 = p->f24 = p->f28 = -3.402823466e+38f;
    FUN_001b2970(arg2, arg0->f20, arg1, 0, arg0->b16, arg0->b17, arg0->f8);
}

