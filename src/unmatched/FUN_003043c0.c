/* 0x003043c0 - FUN_003043c0. retain/release of a global reference; typed pointer, count field read as int Verified byte-identical by tools/verify.py. */
typedef struct R { char pad4[4]; int f4; } R;
int igObject_Destroy();
extern R *DAT_005871b8[4];
void FUN_003043c0(R *arg0) {
    R *p;
    int rc;
    p = DAT_005871b8[0];
    if (p != 0) {
        rc = p->f4 - 1;
        p->f4 = rc;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    if (arg0 != 0) {
        arg0->f4 = arg0->f4 + 1;
    }
    DAT_005871b8[0] = arg0;
}
