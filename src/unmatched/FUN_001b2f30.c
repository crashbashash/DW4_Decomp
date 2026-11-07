struct B { float f0, f4, f8, f12, f16, f20, f24, f28; };
struct O { int f0, f4; long long f8; unsigned char b16, b17; short pad; struct B *f20; };
int FUN_001b2970(struct B *, struct B *, int, int, unsigned char, unsigned char, long long);
void FUN_001b2f30(struct O *arg0, int arg1, struct B *arg2) {
    struct B *p;
    arg0->b17 = 0;
    arg2->f8 = arg2->f12 = arg2->f16 = 3.402823466e+38f;
    arg2->f20 = arg2->f24 = arg2->f28 = -3.402823466e+38f;
    p = arg0->f20;
    p->f8 = p->f12 = p->f16 = 3.402823466e+38f;
    p->f20 = p->f24 = p->f28 = -3.402823466e+38f;
    FUN_001b2970(arg2, arg0->f20, arg1, 0, arg0->b16, arg0->b17, arg0->f8);
}
