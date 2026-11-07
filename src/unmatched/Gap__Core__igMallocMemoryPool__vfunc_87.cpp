class Pool { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual long long Used(); int f4; unsigned long long s8, s16, s24, s32, s40, s48, s56, s64, s72, s80, s88, s96; char pad[48]; int name; };
extern "C" {
extern struct Ctx { char p[36]; int on; } *DAT_00586dc8[4];
extern char DAT_004f7910[], DAT_004f90b0[], DAT_004fef30[];
void FUN_00304430(const char *, ...);
void FUN_00304680(void);
int FUN_002ce1b0(void);
char *FUN_00312140(char *, int, int, int);
}
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_87(Pool *self, char *title) {
    char buf[64];
    char *name;
    if (title != 0 && title[0] != 0) {
        FUN_00304430(DAT_004f90b0);
        FUN_00304680();
    }
    if (DAT_00586dc8[0]->on != 0) {
        name = FUN_00312140(buf, 64, self->name, FUN_002ce1b0());
    } else {
        name = DAT_004f7910;
    }
    {
        long long v96 = self->s96;
        long long v88 = self->s88;
        long long v80 = self->s80;
        long long v72 = self->s72;
        long long v64 = self->s64;
        long long v56 = self->s56;
        long long v48 = self->s48;
        long long v40 = self->s40;
        long long v32 = self->s32;
        long long v24 = self->s24;
        long long v16 = self->s16;
        long long v8 = self->s8;
        FUN_00304430(DAT_004fef30, (int)v8, (int)v16, (int)v24, (int)v32, (int)v40, (int)v48, (int)v56, (int)v64, (int)v72, (int)v80, (int)v88, (int)v96, (int)self->Used(), name);
    }
    FUN_00304680();
}
