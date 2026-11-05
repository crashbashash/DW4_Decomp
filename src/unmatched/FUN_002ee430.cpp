/* 0x002ee430 — FUN_002ee430. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int FUN_00126308(...);
int FUN_0032f300(...);
extern void ** DAT_00587218[4];
void FUN_002ee430(int arg0);
}
class DW4VC_16_1 { public: virtual void d0(); virtual void d1(); virtual int vX(int); };
void FUN_002ee430(int arg0) {
    if (DAT_00587218[0] == 0) {
        FUN_0032f300();
    }
    if (DAT_00587218[0] != 0) {
        ((DW4VC_16_1 *)(DAT_00587218[0]))->vX((int)(arg0));
        return;
    }
    FUN_00126308(arg0);
}
