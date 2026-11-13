void Gap__Gfx__igPsx2UserUCodeExt__vfunc_29(O_17cef0 *arg0, M_17cef0 *arg1) {
    R_17cef0 *temp_v0;
    R_17cef0 *temp_a0;

    arg0->m = arg1;
    temp_v0 = (R_17cef0 *)igMetaObject_FindFieldByName(arg0->m->meta(), &text_pDLists[0]);
    if (temp_v0 != 0) {
        temp_v0->refs = temp_v0->refs + 1;
    }
    temp_a0 = arg0->a;
    if (temp_a0 != 0) {
        temp_a0->refs = temp_a0->refs - 1;
        if ((temp_a0->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->a = temp_v0;
    temp_v0 = (R_17cef0 *)igMetaObject_FindFieldByName(arg0->m->meta(), &text_currentDListHandle[0]);
    if (temp_v0 != 0) {
        temp_v0->refs = temp_v0->refs + 1;
    }
    temp_a0 = arg0->b;
    if (temp_a0 != 0) {
        temp_a0->refs = temp_a0->refs - 1;
        if ((temp_a0->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->b = temp_v0;
}

