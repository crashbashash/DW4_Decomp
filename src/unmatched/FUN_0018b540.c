typedef struct B { char p0[8]; float f8; char p1[8]; float f20; } B;
typedef struct P { char p0[8]; float f8; float f12; float f16; float f20; float f24; float f28; float f32; } P;
int FUN_0018b170();
int FUN_0018b630();
int FUN_0018b540(void *parg0, P *b) {
    int a = (int)parg0;
    float v[3];
    float t;
    int s0, v0;
    if (!(((B *)a)->f8 <= ((B *)a)->f20)) return 0;
    s0 = FUN_0018b630(a, &b->f8) != 0;
    t = b->f32;
    v[0] = b->f8 + t * b->f20;
    v[1] = b->f12 + t * b->f24;
    v[2] = b->f16 + t * b->f28;
    v0 = FUN_0018b630(a, v) != 0;
    if (s0 != 0 && v0 != 0) return 2;
    if (s0 != 0 || v0 != 0 || FUN_0018b170(a, b) != 0) return 1;
    return 0;
}
