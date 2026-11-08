extern "C" {
int free(...);
int FUN_0032f300(...);
extern void ** DAT_00587218[4];
void FUN_002ee4a0(int arg0);
}
class DW4VC_36_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vX(int); };
void FUN_002ee4a0(int arg0) {
    if (DAT_00587218[0] == 0) {
        FUN_0032f300();
    }
    if (DAT_00587218[0] != 0) {
        ((DW4VC_36_1 *)(DAT_00587218[0]))->vX((int)(arg0));
        return;
    }
    free(arg0);
}
