int igMemoryRefMetaField_WriteRawFieldMem();
typedef struct F { char pad[56]; int _num; } F;
int Gap__Core__igRawRefArrayMetaField__vfunc_50(F *self, int src, void *dst, int a3, int a4) {
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
