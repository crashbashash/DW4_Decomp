void Gap__Core__igRawRefArrayMetaField__vfunc_52(igRawRefArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)igRawRefMetaField_GetDefaultDescriptor()));
    ((DW4VC_208_2 *)(descriptor))->vX((int)(item), (int)(count * self->_num));
}

int Gap__Core__igRawRefArrayMetaField__vfunc_51(F_305210 *self, int src, void *dst, int a3, int a4) {
    int s;
    int d;
    int start;
    int i;

    s = src;
    d = (int)dst;
    start = d;
    for (i = 0; i < self->_num; i++) {
        d += igRefMetaField_ReadRawFieldMem((void *)self, s, (int *)d, a3, a4);
        s += 4;
    }
    return d - start;
}

int Gap__Core__igRawRefArrayMetaField__vfunc_50(F_3052b0 *self, int src, void *dst, int a3, int a4) {
    int s;
    int d;
    int start;
    int i;

    s = src;
    d = (int)dst;
    start = d;
    for (i = 0; i < self->_num; i++) {
        d += igMemoryRefMetaField_WriteRawFieldMem(self, s, d, a3, a4);
        s += 4;
    }
    return ((d - start) + 3) & ~3;
}

/* Storage size in bytes of an array field of _num raw references (4 bytes each), truncated to 16
 * bits. Vtable slot 25 is the element-size query. */

int Gap__Core__igRawRefArrayMetaField__vfunc_25(igRawRefArrayMetaField *self) {
    return (self->_num * sizeof(int)) & 0xFFFF;
}

/* IgPluginRepositoryList slot 53, a constant-returning override that returns 4. */

int FUN_00305370(igPluginRepositoryList *self) {
    return 4;
}

