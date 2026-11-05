/* 0x0030c430 - StringTable_NotifyEmptyChunk. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
struct STc { int first; int pad[4]; int cnt; };
extern "C" {
int StringChunk_Destroy(...);
extern void ** DAT_005871c8[4];
void StringTable_NotifyEmptyChunk(STc *arg0, void *arg1);
}
struct DW4SR4 { int w0; };
class DW4VCSR_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual DW4SR4 vX(); };
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(int); };
void StringTable_NotifyEmptyChunk(STc *arg0, void *arg1) {
    DW4SR4 sp3C;
    DW4SR4 sp38;
    int temp_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v1_2;

    if (DAT_005871c8[0] != 0) {
        sp3C = ((DW4VCSR_132_1 *)(DAT_005871c8[0]))->vX((int)(1));
    }
    temp_v1 = arg0->cnt;
    if (temp_v1 > 0) {
        temp_v0 = (void *)(arg0->first);
        temp_v0_2 = (void *)(*(int *)((char *)(temp_v0) + 4));
        if (arg1 == temp_v0_2) {
            *(int *)((char *)(temp_v0) + 4) = (int)((int) *(int *)((char *)(temp_v0_2) + 4));
        } else {
            temp_v1_2 = (void *)(*(int *)((char *)(arg1) + 8));
            *(int *)((char *)(temp_v1_2) + 4) = (int)((int) *(int *)((char *)(arg1) + 4));
            temp_v0_3 = (void *)(*(int *)((char *)(temp_v1_2) + 4));
            if (temp_v0_3 != 0) {
                *(int *)((char *)(temp_v0_3) + 8) = (int)(temp_v1_2);
            }
        }
        StringChunk_Destroy(arg1, 1);
    } else {
        arg0->cnt = temp_v1 + 1;
    }
    if (DAT_005871c8[0] != 0) {
        sp38 = ((DW4VCSR_124_0 *)(DAT_005871c8[0]))->vX();
    }
}
