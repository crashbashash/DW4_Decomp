void Gap__Attrs__igClearAttr__vfunc_24(void *arg0, igPsx2VisualContext *arg1) {
    int temp_a1;

    Gap__Gfx__igPsx2VisualContext__vfunc_181(arg1, *(float *)((char *)(arg0) + 64));
    Gap__Gfx__igPsx2VisualContext__vfunc_178(arg1, *(int *)((char *)(arg0) + 60));
    Gap__Gfx__igPsx2VisualContext__vfunc_183(arg1, *(int *)((char *)(arg0) + 56));
    temp_a1 = *(int *)((char *)(arg0) + 12);
    if (temp_a1 != 0) {
        Gap__Gfx__igPsx2VisualContext__vfunc_176(arg1, temp_a1);
    }
}

void Gap__Attrs__igClearAttr__vfunc_26(void *arg0, void **arg1) {
    float temp_f0;

    *(int *)((char *)(arg0) + 56) = ((DW4VC_736_0 *)(arg1))->vX();
    temp_f0 = ((DW4VC_728_0 *)(arg1))->vX();
    *(double *)((char *)(arg0) + 48) = fptodp(temp_f0);
    *(float *)((char *)(arg0) + 64) = temp_f0;
    *(int *)((char *)(arg0) + 60) = ((DW4VC_720_0 *)(arg1))->vX();
}

void Gap__Attrs__igClearAttr__vfunc_11(void *arg0) {
    igObject_InitDefaults((igObject *)arg0);
    *(int *)((char *)(arg0) + 60) = igVec4f_PackColor((const float *)((char *)arg0 + 0x10), 1);
    *(float *)((char *)(arg0) + 64) = dptofp(*(double *)((char *)(arg0) + 48));
}

void Gap__Attrs__igClearAttr__vfunc_17(void *arg0) {
    FUN_0013b820(arg0);
    *(int *)((char *)(arg0) + 60) = igVec4f_PackColor((const float *)((char *)arg0 + 0x10), 1);
    *(float *)((char *)(arg0) + 64) = dptofp(*(double *)((char *)(arg0) + 48));
}

