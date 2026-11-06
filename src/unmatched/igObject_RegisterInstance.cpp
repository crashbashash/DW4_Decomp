extern "C" {
int ObjectPointerList_Append(...);
void igObject_RegisterInstance(void **arg0, void *arg1);
}
class DW4VC_12_1 { public: virtual void d0(); virtual int vX(int); };
class DW4VC_36_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vX(int); };
class DW4VC_52_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual int vX(int); };
class DW4VC_80_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual int vX(); };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
void igObject_RegisterInstance(void **arg0, void *arg1) {
    int temp_a0;
    void *temp_v0;

    if ((arg1 != 0) && (*(int *)((char *)(arg1) + 60) != 0)) {
        ((DW4VC_80_0 *)(arg0))->vX();
    }
    ((DW4VC_12_1 *)(arg0))->vX((int)(0));
    ((DW4VC_52_1 *)(arg0))->vX((int)(0));
    ((DW4VC_36_1 *)(arg0))->vX((int)(1));
    temp_v0 = (void *)(((DW4VC_88_0 *)(arg0))->vX());
    if (temp_v0 != 0) {
        *(int *)((char *)(temp_v0) + 44) = (int)((int) (*(int *)((char *)(temp_v0) + 44) + 1));
        temp_a0 = *(int *)((char *)(temp_v0) + 48);
        if (temp_a0 != 0) {
            ObjectPointerList_Append(temp_a0, arg0);
        }
    }
}
