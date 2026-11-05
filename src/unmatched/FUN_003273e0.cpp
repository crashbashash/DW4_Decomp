/* 0x003273e0 - FUN_003273e0. Stream/object helper: three virtual error paths each store the status and return; vtable dummies (offset-8)/4, fields through a plain struct. Alternate -O3. */
extern "C" {
extern char DAT_00500000[];
int memset(...);
int FUN_00304430(...);
int FUN_00304680(...);
int igObject_AllocateStorage(...);
extern int DAT_004fb418[4];
extern int DAT_004fb410[4];
extern int DAT_004fdda0[4];
extern int DAT_004ff510[4];
extern int DAT_004ff540[4];
struct OF;
void FUN_003273e0(int *arg0, OF *arg1, int arg2, int arg3, int *arg4);
}
struct SR4 { int w0; };
class Strm;
class Strm { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v27(int, int, int); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int v38(int, int); };

class Obj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual SR4 v25(); };
struct OF { int vt; int p4; int f8; Strm *f12; };
void FUN_003273e0(int *arg0, OF *arg1, int arg2, int arg3, int *arg4) {
    SR4 sp6C;
    SR4 sp68;
    SR4 sp64;
    Strm *s;
    s = arg1->f12;
    if (s->v38(arg2, 0) == -1) {
        FUN_00304430(&DAT_004ff510[0], arg2, arg1->f8);
        FUN_00304680();
        sp6C = ((Obj *)arg1)->v25();
        *arg0 = DAT_004fb418[0];
        return;
    }
    if (*arg4 == 0) {
        *arg4 = igObject_AllocateStorage(arg1, arg3);
        if (*arg4 == 0) {
            FUN_00304430(&DAT_004ff540[0], arg3, arg1->f8);
            FUN_00304680();
            sp68 = ((Obj *)arg1)->v25();
            *arg0 = DAT_004fb418[0];
            return;
        }
    }
    memset(*arg4, 0, arg3);
    s = arg1->f12;
    if (s->v27(*arg4, arg3, 1) != 1) {
        FUN_00304430(&DAT_004fdda0[0], arg1->f8);
        FUN_00304680();
        sp64 = ((Obj *)arg1)->v25();
        *arg0 = DAT_004fb418[0];
        return;
    }
    *arg0 = DAT_004fb410[0];
}
