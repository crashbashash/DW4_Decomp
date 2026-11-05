extern "C" {
int memcpy(...);
int FUN_00300f50(...);
int igMetaField_AllocateArray(...);
void *igMetaObject_GetFieldAt(...);
int igObject_GetAllocator(...);
}
struct Tc { char pad[18]; short f18; };
extern "C" Tc *DAT_005867a0[4];
class V100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v100(); };
struct Fld { char pad[60]; V100 *f60; };
class L { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void* v88(); int f4; int f8; int fc; int f10; };
extern "C" void List_Reserve(L *arg0, int arg1, int arg2) {
    int sp7C;
    if (arg1 == 0) {
        FUN_00300f50(arg0, arg0->f10);
        arg0->f10 = 0;
    } else {
        int s1 = arg0->f10;
        Fld *fld = (Fld *)igMetaObject_GetFieldAt(arg0->v88(), DAT_005867a0[0]->f18);
        unsigned s5 = (unsigned)(arg1 * arg2) / (unsigned)(fld->f60->v100() & 0xFFFF);
        igMetaField_AllocateArray(&sp7C, fld, arg0, s5, igObject_GetAllocator(arg0));
        if (s1 != 0) {
            int v = arg0->fc;
            int n = (v < arg1) ? v : arg1;
            memcpy(arg0->f10, s1, n * arg2);
            FUN_00300f50(arg0, s1);
        }
    }
    arg0->fc = arg1;
}
