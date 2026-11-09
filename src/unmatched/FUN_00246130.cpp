extern "C" {
int FUN_001007e0(int);
void FUN_00245e80(int, int, int, int);
}
struct R { int a; };
class VS { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R Init(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual R Unlock(); virtual void d30(); virtual R Acquire(int wait); };
class VT { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int w92(); };
struct S : VS { int refs; };
extern "C" S *FUN_002ba650(int);
extern "C" S *DAT_0056df58[4];
extern "C" int DAT_0056df50[4];
extern "C" VT *DAT_005871d0[4];
extern "C" int FUN_00246130(int arg0);
struct ScopedLock {
    S *l;
    ScopedLock(S *m) { l = m; l->Acquire(1); }
    ~ScopedLock() { l->Unlock(); }
};
int FUN_00246130(int arg0) {
    int node;
    if (DAT_0056df58[0] == 0) {
        S *created = FUN_002ba650(0);
        DAT_0056df58[0] = created;
        created->Init();
    } else {
        DAT_0056df58[0]->refs = DAT_0056df58[0]->refs + 1;
    }
    ScopedLock guard(DAT_0056df58[0]);
    node = FUN_001007e0(24);
    if (node != 0) {
        int a1 = DAT_005871d0[0]->w92();
        int a2 = DAT_0056df50[0];
        DAT_0056df50[0] = a2 + 1;
        FUN_00245e80(node, a1, a2, arg0);
    }
    return DAT_0056df50[0] - 1;
}
