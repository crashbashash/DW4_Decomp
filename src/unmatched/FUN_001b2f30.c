extern float GPR_0055490c;
extern float GPR_00554910;
struct B { float f0, f4, f8, f12, f16, f20, f24, f28; };
struct O { int f0, f4; long long f8; unsigned char b16, b17; short pad; struct B *f20; };
int FUN_001b2970(struct B *, struct B *, int, int, unsigned char, unsigned char, long long);
void FUN_001b2f30(struct O *arg0, int arg1, struct B *arg2) {
    float a, b;
    struct B *p;
    arg0->b17 = 0;
    a = GPR_0055490c;
    arg2->f16 = a; arg2->f12 = a; arg2->f8 = a;
    b = GPR_00554910;
    arg2->f28 = b; arg2->f24 = b; arg2->f20 = b;
    p = arg0->f20;
    a = GPR_0055490c;
    p->f16 = a; p->f12 = a; p->f8 = a;
    b = GPR_00554910;
    p->f28 = b; p->f24 = b; p->f20 = b;
    FUN_001b2970(arg2, arg0->f20, arg1, 0, arg0->b16, arg0->b17, arg0->f8);
}
