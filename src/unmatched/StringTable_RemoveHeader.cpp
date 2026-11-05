extern "C" {
int StringTable_EraseAt(...);
int StringTable_SearchRetained(...);
extern void ** DAT_005871c8[4];
void StringTable_RemoveHeader(int arg0, int arg1);
}
struct DW4SR4 { int w0; };
class DW4VCSR_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual DW4SR4 vX(); };
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(int); };
void StringTable_RemoveHeader(int arg0, int arg1) {
    int sp3C;
    int sp38;
    DW4SR4 sp34;
    DW4SR4 sp30;

    if (DAT_005871c8[0] != 0) {
        sp34 = ((DW4VCSR_132_1 *)(DAT_005871c8[0]))->vX((int)(1));
    }
    sp3C = 0;
    sp38 = 0;
    StringTable_SearchRetained(arg0, arg1 + 8, &sp38, &sp3C);
    StringTable_EraseAt(arg0, sp3C);
    if (DAT_005871c8[0] != 0) {
        sp30 = ((DW4VCSR_124_0 *)(DAT_005871c8[0]))->vX();
    }
}
