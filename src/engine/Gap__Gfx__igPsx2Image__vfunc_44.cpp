extern "C" {
int igObject_Destroy(...);
int FUN_00159320(...);
int FUN_00159a80(...);
int FUN_00159f00(int);
int FUN_0015a600(void *);
int FUN_00300db0(void *, int, int);
}
class Strm { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void v24(); virtual int v25(void *, int, int); };
struct Img { char pad[8]; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; char pad2[4]; char f60; char pad3[3]; int f64; char pad4[4]; int f72; int f76; char pad5[4]; int f84; };
extern "C" int Gap__Gfx__igPsx2Image__vfunc_44(Img *arg0, Strm *arg1);
int Gap__Gfx__igPsx2Image__vfunc_44(Img *arg0, Strm *arg1) {
    int sp6C;
    int sp68;
    int sp64;
    int sp60;
    int sp5C;
    int sp58;
    int sp54;
    int sp50;
    int sp4C;
    int sp48;
    int temp_s2;
    arg1->v25((char *)arg0 + 48, 4, 1);
    arg1->v25((char *)arg0 + 16, 4, 1);
    arg1->v25((char *)arg0 + 8, 4, 1);
    arg1->v25((char *)arg0 + 12, 4, 1);
    arg0->f20 = 1;
    arg0->f52 = FUN_00300db0(arg0, arg0->f48, 0x80);
    arg0->f60 = 1;
    arg1->v25((void *)arg0->f52, 1, arg0->f48);
    arg1->v24();
    arg0->f44 = FUN_00159f00(arg0->f16);
    FUN_0015a600(arg0);
    temp_s2 = arg0->f44;
    FUN_00159320(arg0, temp_s2, arg0->f8, arg0->f12, &sp6C, &sp68, &sp64);
    arg0->f76 = sp64;
    FUN_00159a80(temp_s2, &sp60, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48);
    arg0->f64 = sp60;
    arg0->f72 = sp5C;
    arg0->f28 = sp58;
    arg0->f32 = sp54;
    arg0->f36 = sp50;
    arg0->f40 = sp4C;
    arg0->f84 = sp48;
    arg0->f24 = 0x66;
    *(int *)((char *)arg1 + 4) = *(int *)((char *)arg1 + 4) - 1;
    if ((*(int *)((char *)arg1 + 4) & 0x7FFFFF) == 0) {
        igObject_Destroy(arg1);
    }
    return 1;
}
