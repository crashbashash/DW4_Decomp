typedef struct S_ref { char pad4[4]; int f4; } S_ref;
int igObject_Destroy();
extern S_ref *DAT_00562730[4];
extern S_ref *DAT_00562738[4];
extern S_ref *DAT_00562740[4];
extern S_ref *DAT_00562758[4];
void FUN_001c1f90(void) {
    S_ref *p;
    p = DAT_00562730[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(p);
        DAT_00562730[0] = 0;
    }
    p = DAT_00562738[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(p);
        DAT_00562738[0] = 0;
    }
    p = DAT_00562740[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(p);
        DAT_00562740[0] = 0;
    }
    p = DAT_00562758[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) igObject_Destroy(p);
    }
    DAT_00562758[0] = 0;
}
