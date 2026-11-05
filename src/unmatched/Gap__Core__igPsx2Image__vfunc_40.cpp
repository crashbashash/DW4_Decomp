class Strm {
public:
    virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();
    virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();
    virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();
    virtual void d24();
    virtual void Read(void *, int, int);
};
struct Img {
    char p0[8];
    int f8, f12, f16, f20, f24, f28, f32, f36, f40, f44, f48, f52;
    int pad56;
    unsigned char f60;
    char p61[3];
    int f64;
    char p68[4];
    int f72;
    char p76[8];
    int f84;
};
extern "C" int FUN_00159f00(int);
extern "C" void FUN_0015a600(Img *);
extern "C" int FUN_00300db0(Img *, int, int);
extern "C" int Gap__Core__igPsx2Image__vfunc_40(Img *p, Strm *s) {
    unsigned int b;
    unsigned int a;
    s->Read(&p->f48, 4, 1);
    s->Read(&p->f8, 4, 1);
    s->Read(&p->f12, 4, 1);
    s->Read(&p->f16, 4, 1);
    s->Read(&p->f20, 4, 1);
    s->Read(&a, 4, 1);
    p->f28 = (a >> 24) & 0xFF;
    p->f32 = (a >> 16) & 0xFF;
    p->f36 = (a >> 8) & 0xFF;
    p->f40 = (unsigned char)a;
    p->f72 = 0;
    p->f64 = 0;
    p->f84 = 0;
    s->Read(&b, 4, 1);
    s->Read(&b, 4, 1);
    p->f52 = FUN_00300db0(p, p->f48, 0x80);
    p->f60 = 1;
    s->Read((void *)p->f52, 1, p->f48);
    s->d24();
    p->f44 = FUN_00159f00(p->f16);
    p->f24 = 0x66;
    FUN_0015a600(p);
    return 1;
}
