void Gap__Core__igIntArrayMetaField__vfunc_52(igIntArrayMetaField *self, int passThrough, int perElement) {
    void **elementDescriptor;

    elementDescriptor = (void **)(((void **)igIntMetaField_GetDefaultDescriptor()));
    ((DW4VC_208_2 *)(elementDescriptor))->vX((int)(passThrough), (int)(perElement * self->_num));
}

int Gap__Core__igIntArrayMetaField__vfunc_25(void *arg0) {
    return (*(int *)((char *)(arg0) + 52) * 4) & 0xFFFF;
}

void FUN_002ea290(void **arg0, int arg1) {
    int *p;
    S_2ea290 *o = (S_2ea290 *)arg0;
    ((DW4VC_140_1 *)arg0)->vX(0);
    int i;
    p = o->arr;
    for (i = 0; i < o->n; i++) {
        p[i] = arg1;
    }
}

