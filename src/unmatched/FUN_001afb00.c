/* 0x001afb00 - FUN_001afb00. reference release of a global; pointer typed, count field read as int Verified byte-identical by tools/verify.py. */
typedef struct R { char pad4[4]; int f4; } R;
int igObject_Destroy();
extern R *DAT_00562578[4];
void FUN_001afb00(void) {
    R *p;
    int rc;
    p = DAT_00562578[0];
    if (p != 0) {
        rc = p->f4 - 1;
        p->f4 = rc;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    DAT_00562578[0] = 0;
}
