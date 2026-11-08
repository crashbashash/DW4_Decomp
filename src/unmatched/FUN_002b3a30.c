extern void memset(void *p, int c, int n);
typedef struct {
    int f0, f4, f8, f12, f16;
    char pad20[24];
    int f44, f48;
    char pad52[8];
    int f60, f64, f68, f72, f76;
    char pad80[8];
    int f88, f92;
    char pad96[8];
    int f104;
    char pad108[8];
    int f116;
} V;
void FUN_002b3a30(V *v, int a, int b) {
    int base;
    memset(v, 0, 0x78);
    base = (a + 31) & ~31;
    v->f12 = 0;
    v->f16 = 0;
    v->f44 = 1;
    v->f0 = 1;
    v->f8 = 17;
    v->f48 = 0;
    v->f60 = 0;
    v->f64 = base;
    v->f68 = base + 0x400;
    v->f72 = base + 0x800;
    v->f76 = base + 0xC00;
    v->f88 = a;
    v->f92 = b;
    v->f104 = -1;
    v->f116 = 0;
    v->f4 = 0;
}
