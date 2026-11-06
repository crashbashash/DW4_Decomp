typedef struct T { unsigned short a0; unsigned short a2; unsigned short a4; char p6[2]; short *f8; int f12; } T;
typedef struct O { char p8[8]; int f8; char p12[8]; int f20; char p24[4]; T *f28; } O;
int FUN_0010b7d8();
int FUN_002ed2e0();
int FUN_00300db0();
int Gap__Core__igObject__vfunc_01();
T *Memory_AllocateDefaultBuffer();

void Gap__Core__igPsx2Media__vfunc_03(O *arg0) {
    int i;
    int a;
    T *t;

    Gap__Core__igObject__vfunc_01(arg0);
    arg0->f8 = FUN_00300db0(arg0, 0x80, 0x40);
    arg0->f20 = FUN_00300db0(arg0, 0x90, 0x10);
    a = arg0->f8;
    FUN_0010b7d8(a, a + 0x80);
    t = Memory_AllocateDefaultBuffer(0x10);
    if (t != 0) {
        t->a0 = 8;
        t->a4 = 8;
        t->a2 = 8;
        t->f12 = FUN_002ed2e0(t->a0, 0xC);
        t->f8 = (short *)FUN_002ed2e0(t->a2, 2);
        for (i = 0; i < t->a4; i++) {
            t->f8[i] = i;
        }
    }
    arg0->f28 = t;
}
