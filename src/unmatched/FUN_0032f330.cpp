/* 0x0032f330 — FUN_0032f330. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
extern void ** DAT_00587218[4];
void FUN_0032f330(void);
}
class DW4VC_12_0 { public: virtual void d0(); virtual int vX(); };
void FUN_0032f330(void) {
    if (DAT_00587218[0] != 0) {
        ((DW4VC_12_0 *)(DAT_00587218[0]))->vX();
    }
}
