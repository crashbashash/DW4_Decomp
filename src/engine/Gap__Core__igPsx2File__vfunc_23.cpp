class FO {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual char *v164(char *);
    virtual void d40();
    int pad4;
    char pad8[4];
    int f12;
    char pad16[4];
    int f20;
    int f24;
    char pad28[16];
    int f44;
    int f48;
    int f52;
    char pad56[4];
    int f60;
    int f64;
};
extern "C" {
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
int FUN_0010f330(...);
int FUN_0010f738(...);
int FUN_0010f970(...);
int FUN_0012a1e8(...);
unsigned char FUN_002e31c0(int);
int FUN_002e3220(int);
int FUN_002e34a0(void);
unsigned char FUN_002e34d0(int *, char *, int);
int FUN_0032b5b0(...);
}
extern "C" void Gap__Core__igPsx2File__vfunc_23(int *arg0, FO *arg1, unsigned arg2) {
//DECL
    int sp2BC;
    char buf[512];
    volatile unsigned char sA0[16];
    int s0;
    unsigned char s5;
    int s4;
    int s3;
    char *s7;
    int s8;
    int v0;
    char *p;
    unsigned n;
    int m;
    int neg;
//ENDDECL
    s0 = 0;
    if (arg2 == 8) arg2 = arg1->f20;
    if (arg1->f64 == 1 && arg1->f20 == arg2) {
        *arg0 = DAT_004fb410[0];
    } else {
        switch (arg2) {
        case 0: case 1: case 2: case 3: case 8:
            arg1->f60 = 0;
            break;
        case 4: case 5: case 6: case 7:
            arg1->f60 = 1;
            break;
        }
        switch (arg2) {
        case 1: case 5: s0 = 0x602; break;
        case 2: case 6: s0 = 0x300; break;
        case 3: case 7: s0 = 0x203; break;
        case 0: case 4: case 8: s0 = 1; break;
        }
        arg1->f48 = 0;
        p = buf;
        arg1->f52 = 0;
        n = 0x200;
        arg1->f64 = 0;
        if (p != 0) {
            do {
                *p = 0;
                n -= 1;
                p += 1;
            } while (n != 0);
        }
        s5 = 1;
        sA0[0] = FUN_002e31c0(arg1->f12);
        s8 = FUN_002e3220(arg1->f12) & 0xFF;
        sp2BC = FUN_002e34a0();
        s4 = 0;
        while (s5 && s4 < 0x100) {
            if (sA0[0] != 0) {
                buf[0] = 0;
                s5 = 0;
                goto L23;
            }
            if (s8 != 0) {
                buf[0] = 0;
                s8 = 0;
                goto L23;
            }
            s5 = FUN_002e34d0(&sp2BC, buf, 0x200);
            if (s5) {
L23:
                FUN_0012a1e8(buf, arg1->f12);
                s7 = arg1->v164(buf);
                if (*s7 == 0x63) {
                    s3 = 10;
                    while ((v0 = FUN_0010f330(s7, s0)) < 0 && s3 != 0) {
                        s3 -= 1;
                    }
                } else {
                    v0 = FUN_0010f330(s7, s0, 0x1B6);
                }
                arg1->f24 = v0;
                if (!(0 > v0)) break;
            }
            s4 += 1;
        }
        if (arg1->f24 < 0) {
            *arg0 = DAT_004fb418[0];
        } else {
            if (arg2 == 6) FUN_0010f738(arg1->f24, 0, 2);
            if (arg1->f60 == 0) {
                m = FUN_0010f738(arg1->f24, 0, 2);
                FUN_0032b5b0(arg1, m);
                FUN_0010f738(arg1->f24, 0, 0);
                if (m > 0) {
                    v0 = FUN_0010f970(arg1->f24, arg1->f44, m);
                    if (v0 != m) FUN_0032b5b0(arg1, v0);
                }
                if (arg2 == 2) arg1->f52 = m;
                else arg1->f52 = 0;
            }
            arg1->f20 = arg2;
            arg1->f64 = 1;
            *arg0 = DAT_004fb410[0];
        }
    }
}
