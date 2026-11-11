void Gap__Core__igBoolArrayMetaField__vfunc_52(igBoolArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)FUN_002cce00()));
    ((MetaFieldSwapBytesSlot *)(elementField))->SwapBytes((int)(buffer), (int)(count * self->_num));
}

unsigned short Gap__Core__igBoolArrayMetaField__vfunc_25(void *arg0) {
    return *(int *)((char *)(arg0) + 52);
}

void FUN_002d35d0(C_2d35d0 *arg0, int arg1) {
    char *base;
    int i;
    arg0->vX(0);
    base = arg0->f32;
    for (i = 0; i < arg0->f52; i++) {
        base[i] = arg1;
    }
}

