struct Src { char p0[8]; int n; int p12; int *d; };
struct G { char p0[8]; int f8; };
struct S { char p0[12]; unsigned char f12; unsigned char f13; char p14[2]; int f16; int f20; struct Src *f24; };
extern struct G *DAT_00562bc8[4];
int FUN_001419f0(void *, void *, void *);
int FUN_00180030(int, int, int);
int FUN_001904f0(int, void *, int);
int FUN_00300db0(void *, int, int);
int Matrix44_Copy(int, int);

void Gap__Core__igVertexBlendMatrixListAttr__vfunc_24(struct S *arg0, int arg1) {
    int i;
    int n;
    n = arg0->f24->n;
    if (arg0->f13 == 0) {
        FUN_001419f0(arg0, (char *)arg0 + 0x1C, (char *)arg0 + 0x5C);
    }
    if (arg0->f16 == 0 && n > 0) {
        arg0->f16 = FUN_00300db0(arg0, n << 6, 0x10);
        arg0->f20 = n;
    }
    if (arg0->f12 == 0) {
        for (i = 0; i < n; i++) {
            int o = arg0->f24->d[i];
            FUN_001904f0(arg0->f16 + (i << 6), (char *)arg0 + 0x1C, o + DAT_00562bc8[0]->f8);
        }
    } else {
        for (i = 0; i < n; i++) {
            int o = arg0->f24->d[i];
            Matrix44_Copy(arg0->f16 + (i << 6), o + DAT_00562bc8[0]->f8);
        }
    }
    FUN_00180030(arg1, n, arg0->f16);
}
