int FUN_002d8a80(int,void*,int,int,int,int,int,unsigned char);
int igObject_IsKindOf();
unsigned int Memory_GetBufferSize();
extern int DAT_00585d80[4];
extern int DAT_00585b20[4];
typedef struct F { char p0[8]; int base; char p1[26]; unsigned char f38; char p2[21]; int f60; char p3[4]; int f68; } F;
typedef struct F2 { char p[66]; unsigned char f66; } F2;
int igMemoryRefMetaField_Write(F *f, int off, int a2) {
    int s0;
    int s1;
    int p;
    unsigned int n;
    if (f->f38 == 0) return -1;
    p = *(int *)(off + f->base);
    if (p == 0) return -1;
    if (igObject_IsKindOf(f->f60, DAT_00585d80[0]) != 0) {
        n = Memory_GetBufferSize(p) >> 2;
        s1 = FUN_002d8a80(a2, f, p, f->f60, f->f68, 0, 0, 1);
        for (s0 = 0; s0 < (int)n; s0++) {
            int e = *(int *)(p + s0 * 4);
            if (e != 0) FUN_002d8a80(a2, f, e, 0, f->f68, 0, 0, 1);
        }
        return s1;
    }
    if (igObject_IsKindOf(f->f60, DAT_00585b20[0]) != 0) {
        s1 = FUN_002d8a80(a2, f, p, f->f60, f->f68, 0, 0, ((F2 *)f)->f66);
        return s1;
    }
    return FUN_002d8a80(a2, f, p, f->f60, f->f68, 0, 0, 1);
}
