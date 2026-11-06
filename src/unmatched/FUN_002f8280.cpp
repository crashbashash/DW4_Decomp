/* The flag tests are `((x & m) ? 1 : 0) &&`; the ternary gives the materialised sltu. The two
 * later virtual slots are dummy-virtual stubs. */
struct Res {
    virtual void r0();
    virtual void r1();
    virtual void r2();
    virtual void r3();
    virtual void r4();
    virtual void r5();
    virtual void r6();
    virtual void r7();
    virtual void r8();
    virtual void r9();
    virtual void r10();
    virtual void r11();
    virtual void r12();
    virtual void r13();
    virtual void r14();
    virtual void r15();
    virtual void r16();
    virtual void r17();
    virtual void r18();
    virtual void r19();
    virtual void r20();
    virtual void r21();
    virtual void r22();
    virtual void r23();
    virtual void v24(int *, int);
    int p[3];
    int flags;
    int p2;
    int mask;
};
struct Dev {
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
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual Res *getRes();
};
struct Slot { char p[20]; Dev *dev; char q[120]; };
extern "C" int FUN_002e2250(int *, int, int, int, int, int, int, int, long long, long long);
extern "C" int FUN_002e2300(int *, int);
extern "C" void FUN_002f8280(Slot *arg0, int arg1, int arg2, int arg3);
void FUN_002f8280(Slot *arg0, int arg1, int arg2, int arg3) {
    int sp[40];
    int i;
    int j;
    int found;
    Res *r;
    Dev *d;
    for (i = 0; i < 46; i++) {
        d = arg0[i].dev;
        if (d != 0) {
            r = d->getRes();
            found = 0;
            if (r != 0) {
                for (j = 0; j < i; j++) {
                    Dev *e = arg0[j].dev;
                    if (e != 0 && e->getRes() == r) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0 && r != 0 && ((r->flags & 0x2000) ? 1 : 0) && ((r->mask & (1 << arg1)) ? 1 : 0)) {
                    FUN_002e2250(sp, arg1, arg2, arg3, 0, 0, 0, 0, 0, 0);
                    r->v24(sp, -1);
                    FUN_002e2300(sp, -1);
                }
            }
        }
    }
}
