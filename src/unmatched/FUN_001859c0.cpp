class B {
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
    virtual int v116(unsigned, float *);
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual int v144(unsigned, float *);
    virtual void d35();
    virtual int v152(unsigned, int);
    virtual void d37();
    virtual void d38();
    virtual int v164(unsigned, int);
    int f4;
    char pad8[16];
    B *f24;
};
extern "C" {
int FUN_001818a0(int);
int FUN_001818b0(int);
int FUN_00182100(int);
int FUN_001820f0(int);
int FUN_001824c0(int);
int FUN_00183fc0(int);
void FUN_00183f60(float *, int, int, int, float, float);
void FUN_00182440(float *, int, int, int, float, float);
int FUN_001931b0(float *, int);
int igObject_Destroy(...);
}
extern "C" void FUN_001859c0(int arg0, unsigned arg1, int arg2, int arg3, B *arg4, B *arg5, float fparg0) {
//DECL
    B *t;
    B *t2;
    float temp_f20;
    float spB0[4];
    float spA0[4];
    int temp_s0_2;
    int temp_s1;
    int temp_s0;
    int temp_s1_2;
    int temp_s1_4;
    int temp_s2;
    int temp_s1_3;
    int temp_s2_2;
    int temp_s6;
    int temp_s6_2;
    unsigned temp_s7;
    unsigned temp_s7_2;
//ENDDECL
    temp_f20 = fparg0 * fparg0;
    if (arg5 != 0) {
        if (arg4 != 0) {
            arg4->f4 = arg4->f4 + 1;
        }
        t = arg5->f24;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg5->f24 = arg4;
        temp_s7 = arg1 + arg0;
        for (; arg1 < temp_s7; arg1++) {
            temp_s1 = arg2 + arg1 * arg3;
            temp_s0 = FUN_001818b0(temp_s1);
            temp_s6 = FUN_001818a0(temp_s1);
            FUN_00183f60(spB0, temp_s0, temp_s6, FUN_00183fc0(temp_s1), fparg0, temp_f20);
            temp_s0_2 = FUN_00182100(temp_s1);
            temp_s1_2 = FUN_001820f0(temp_s1);
            FUN_00182440(spA0, temp_s0_2, temp_s1_2, FUN_001824c0(temp_s1), fparg0, temp_f20);
            arg5->v144(arg1, spB0);
            arg5->v152(arg1, FUN_001931b0(spA0, 1));
        }
        t2 = arg5->f24;
        if (t2 != 0) {
            t2->f4 = t2->f4 - 1;
            if (((unsigned long long)((long long)t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t2);
            }
        }
        arg5->f24 = 0;
    } else {
        temp_s7_2 = arg1 + arg0;
        for (; arg1 < temp_s7_2; arg1++) {
            temp_s2 = arg2 + arg1 * arg3;
            temp_s1_3 = FUN_001818b0(temp_s2);
            temp_s6_2 = FUN_001818a0(temp_s2);
            FUN_00183f60(spB0, temp_s1_3, temp_s6_2, FUN_00183fc0(temp_s2), fparg0, temp_f20);
            temp_s1_4 = FUN_00182100(temp_s2);
            temp_s2_2 = FUN_001820f0(temp_s2);
            FUN_00182440(spA0, temp_s1_4, temp_s2_2, FUN_001824c0(temp_s2), fparg0, temp_f20);
            arg4->v116(arg1, spB0);
            arg4->v164(arg1, FUN_001931b0(spA0, 1));
        }
    }
}
