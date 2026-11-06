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
