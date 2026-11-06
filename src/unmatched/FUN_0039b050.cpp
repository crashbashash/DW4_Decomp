struct Q { char p0[20]; float f20; float f24; char p1[20]; int f48; int f52; int f56; int f60; int f64; char p2[28]; int f96; int f100; };
extern "C" {
int FUN_0039b110(Q *, int *, float *);
void FUN_0039b050(struct Q *arg0, float *arg1);
}
void FUN_0039b050(struct Q *arg0, float *arg1) {
    float sp28[2];
    int a;
    int v;
    arg0->f20 = arg1[0];
    arg0->f24 = arg1[1];
    arg0->f60 = arg0->f56;
    sp28[0] = arg0->f20;
    sp28[1] = arg0->f24;
    FUN_0039b110(arg0, &arg0->f56, sp28);
    a = arg0->f56;
    arg0->f48 = a & (arg0->f60 ^ a);
    if ((arg0->f60 ^ arg0->f56) != 0) {
        arg0->f52 = arg0->f48;
        arg0->f64 = arg0->f96;
        return;
    }
    v = arg0->f64 - 1;
    arg0->f64 = v;
    if (v != 0) {
        arg0->f52 = 0;
        return;
    }
    arg0->f52 = arg0->f56;
    arg0->f64 = arg0->f100;
}
