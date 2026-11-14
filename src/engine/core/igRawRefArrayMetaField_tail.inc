void Gap__Core__igRawRefArrayMetaField__vfunc_52(igRawRefArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(((void **)igRawRefMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(descriptor))->SwapBytes((void *)(item), (int)(count * self->_num));
}

int Gap__Core__igRawRefArrayMetaField__vfunc_51(igRawRefArrayMetaField *self, int src, void *dst, int a3, int a4) {
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

int Gap__Core__igRawRefArrayMetaField__vfunc_50(igRawRefArrayMetaField *self, int src, void *dst, int a3, int a4) {
    int s;
    int d;
    int start;
    int i;

    s = src;
    d = (int)dst;
    start = d;
    for (i = 0; i < self->_num; i++) {
        d += igMemoryRefMetaField_WriteRawFieldMem((igMetaFieldView *)self, (int *)s, (void *)d, a3, a4);
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

