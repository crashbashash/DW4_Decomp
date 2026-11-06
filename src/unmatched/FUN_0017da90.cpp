/* Fills a vertex-stream descriptor (pointer + element size) for stream type 0..9 of the vertex
 * array; the descriptor index is re-read volatile in the plain cases (retail does not reuse the
 * early copy there), the base pointer of case 4 is added last. Dummy-virtual class for slot 23;
 * alternate compiler -O3. */
#define RD *(volatile int *)&arg1->f8
extern "C" int FUN_001f05a0(...);
struct P { int f0; int f4; int f8; int pad[12]; int f60; int pad2[1]; int f68; int f72; };
struct VA {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual unsigned *flags();
    int pad;
    P *f8;
    int f12;
    int pad2;
    int f20;
    int pad3[2];
    char *f32;
    char *f36;
    int pad4[6];
    long long f64;
};
struct St { int f0; int f4; int f8; int f12; char *f16; int f20; int f24; };
extern "C" void FUN_0017da90(VA *arg0, St *arg1);
void FUN_0017da90(VA *arg0, St *arg1) {
    int m;
    int t;
    int s1;
    char *bs;
    int s0;

    if (arg1->f12 == 0) {
        arg1->f12 = arg0->f12 - arg1->f8;
    }
    t = arg1->f4;
    s0 = arg1->f0;
    s1 = arg1->f8;
    switch (t) {
    case 0:
        arg1->f16 = (char *)(arg0->f8->f0 + RD * 12);
        arg1->f20 = 12;
        break;
    case 1:
        arg1->f16 = (char *)(arg0->f8->f4 + RD * 12);
        arg1->f20 = 12;
        break;
    case 2:
        arg1->f16 = (char *)(arg0->f8->f8 + RD * 4);
        arg1->f20 = 4;
        break;
    case 4: {
        int n = ((*arg0->flags() & 0xF0) >> 4) & 0xFF;
        m = (s0 + s1 * n) * 4; arg1->f16 = m + arg0->f32;
        arg1->f20 = n * 4;
        break;
    }
    case 5: {
        int n = ((*arg0->flags() & 0xF00) >> 8) & 0xFF;
        bs = arg0->f36; arg1->f16 = bs + (s0 + s1 * n);
        arg1->f20 = n;
        break;
    }
    case 3:
        arg1->f16 = (char *)(*(int *)((char *)arg0->f8 + (s0 + 11) * 4) + RD * 8);
        arg1->f20 = 8;
        break;
    case 6:
        arg1->f16 = (char *)(arg0->f8->f60 + RD * 4);
        arg1->f20 = (((*arg0->flags() & 0x300000) >> 0x14) & 0xFF) * 4;
        break;
    case 9:
        arg1->f16 = (char *)(arg0->f8->f60 + RD * 4);
        arg1->f20 = 4;
        break;
    case 7:
        arg1->f16 = (char *)(arg0->f8->f68 + RD * 12);
        arg1->f20 = 12;
        break;
    case 8:
        arg1->f16 = (char *)(arg0->f8->f72 + RD * 12);
        arg1->f20 = 12;
        break;
    }
    arg1->f24 = 0;
    if (arg0->f20 & 4) {
        FUN_001f05a0(1, arg0->f64);
    }
}
