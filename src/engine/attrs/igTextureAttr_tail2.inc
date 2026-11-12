void Gap__Attrs__igTextureAttr__vfunc_32(igTextureAttr *arg0, int arg1) {
    arg0->_magFilter = arg1;
}

void Gap__Attrs__igTextureAttr__vfunc_33(igTextureAttr *arg0, int arg1) {
    arg0->_minFilter = arg1;
}

void Gap__Attrs__igTextureAttr__vfunc_34(igTextureAttr *arg0, int arg1) {
    arg0->_wrapS = arg1;
}

void Gap__Attrs__igTextureAttr__vfunc_35(igTextureAttr *arg0, int arg1) {
    arg0->_wrapT = arg1;
}

void Gap__Attrs__igTextureAttr__vfunc_36(S0_142400 *arg0, S1_142400 *arg1) {
    S_temp_a0_142400 *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (S_temp_a0_142400 *)((void *)(arg0->fC));
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->fC = (int)(arg1);
}

