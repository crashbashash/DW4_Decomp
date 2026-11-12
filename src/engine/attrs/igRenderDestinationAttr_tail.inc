void Gap__Attrs__igRenderDestinationAttr__vfunc_26(OO *arg0, void **arg1) {
    int sp4C;
    int sp48;
    int temp_s0;
    int *pp;
    int t;

    temp_s0 = ((DW4VC_200_0 *)(arg1))->vX();
    arg0->f20 = ((DW4VC_200_0 *)(arg1))->vX();
    arg0->f48 = ((DW4VC_216_1 *)(arg1))->vX(temp_s0);
    arg0->f52 = ((DW4VC_220_1 *)(arg1))->vX(temp_s0);
    arg0->f56 = ((DW4VC_224_1 *)(arg1))->vX(temp_s0);
    arg0->f60 = ((DW4VC_228_1 *)(arg1))->vX(temp_s0);
    pp = (int *)((int)&sp4C + 0);
    ((DW4VC_212_3 *)(arg1))->vX(temp_s0, &sp48, pp);
    t = *pp;
    arg0->f40 = sp48;
    arg0->f44 = t;
}

void Gap__Attrs__igRenderDestinationAttr__vfunc_12(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    Gap__Core__igObject__vfunc_10(arg0);
}

void Gap__Attrs__igRenderDestinationAttr__vfunc_28(X_13fea0 *arg0) {
    int temp_a1;
    R_13fea0 *temp_a0;
    R_13fea0 *temp_a0_2;

    if (arg0->w12 != 2) {
        temp_a0 = arg0->obj;
        if (temp_a0 != 0) {
            temp_a1 = arg0->w20;
            if (temp_a1 >= 0) {
                ((DW4VC_188 *)temp_a0)->vX(temp_a1);
            }
        }
        temp_a0_2 = arg0->obj;
        if (temp_a0_2 != 0) {
            temp_a0_2->refs = temp_a0_2->refs - 1;
            if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->obj = 0;
        arg0->w20 = -1;
    }
}

