/* The 31-bit address word is a bit-field rather than shift arithmetic, and the low half is stored
 * through a short pointer from an int local. */
struct C { char pad0[48]; int *f48; };
struct W { unsigned addr : 31; unsigned flag : 1; };
int FUN_00208120();
extern int DAT_00491478[4];
extern int DAT_00491720[4];
extern struct W DAT_00491724[4];
extern int DAT_00491728[4];
extern int DAT_0049172c[4];
extern struct C *DAT_00568f04[4];
extern long long DAT_0056ae48[4];
extern int DAT_0056bfa8[4];
extern int DAT_0056bfb0[4];
void FUN_00207470(void) {
    int *p;
    int v;
    FUN_00208120();
    p = DAT_00568f04[0]->f48;
    DAT_00491724[0].addr = DAT_0056bfa8[0] & ~0xF;
    v = DAT_0056bfb0[0];
    *(short *)&DAT_00491720[0] = v;
    p[0] = DAT_00491720[0];
    p[1] = *(int *)&DAT_00491724[0];
    p[2] = DAT_00491728[0];
    p[3] = DAT_0049172c[0];
    DAT_00568f04[0]->f48 = p + 4;
    DAT_00491478[0] |= 0x40;
    DAT_0056ae48[0] |= 0x40122140 | ((long long)0x50A1 << 0x20);
}
