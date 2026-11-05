class VT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual int v42(); virtual void d43(); virtual void d44(); virtual int v45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual int v65(int); };
struct Obj { int p0; int refs; };
struct L { char pad[4]; int f4; int f8; int f12; char pad2[8]; Obj *f24; };
struct S { char f0; char pad1[3]; int f4; int f8; int f12; char pad2[4]; char f20; char pad3[3]; Obj *f24; char pad4[8]; Obj *f36; char pad5[4]; int f44; char pad6[64]; Obj *f112; };
extern "C" {
int FUN_002e3280(...);
int FUN_002eb010(...);
int FUN_0032aea0(...);
int InternalObjectList_SetAtRetained(...);
int InternalObjectList_SetCount(...);
int StringPool_Construct(...);
int StringPool_Destroy(...);
int igArray_Destruct(...);
int igObject_Destroy(...);
extern int DAT_00586f20[4];
extern VT *DAT_00586fd0[4];
extern Obj *DAT_00587188[4];
void FUN_002d2e60(S *arg0);
}
void FUN_002d2e60(S *arg0) {
    int i;
    int v;
    Obj *o;
    o = arg0->f36;
    o->refs = o->refs - 1;
    if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
    arg0->f36 = 0;
    FUN_002e3280(0);
    igArray_Destruct(arg0->f44, 1);
    if (DAT_00586fd0[0] != 0) {
        DAT_00586fd0[0]->v45();
    }
    InternalObjectList_SetCount(DAT_00587188[0], arg0->f8);
    for (i = arg0->f12 - 1; i >= arg0->f4; i--) {
        InternalObjectList_SetAtRetained(arg0->f24, i, 0);
    }
    arg0->f0 = 0;
    o = DAT_00587188[0];
    o->refs = o->refs - 1;
    if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
    o = arg0->f24;
    o->refs = o->refs - 1;
    if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
    o = arg0->f112;
    if (o != 0) {
        o->refs = o->refs - 1;
        if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o);
    }
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) v = StringPool_Construct(v);
        DAT_00586f20[0] = v;
    }
    StringPool_Destroy(DAT_00586f20[0], 1);
    arg0->f20 = 0;
    if (DAT_00586fd0[0] != 0) {
        DAT_00586fd0[0]->v42();
        if (DAT_00586fd0[0] != 0) {
            DAT_00586fd0[0]->v65(1);
        }
        DAT_00586fd0[0] = 0;
    }
    FUN_0032aea0();
}
