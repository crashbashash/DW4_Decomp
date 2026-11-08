typedef struct { char p0[236]; int f236; char p1[76]; int w; int h; char p2[8]; int br; int vbv; char p3[1796]; int iqm; int niqm; char p4[16]; void *mp; } M;
extern char DAT_004d22f8[];
extern char DAT_00481d40[];
extern char DAT_00481d80[];
unsigned int FUN_00106c88(M *, int);
int FUN_00109b10(M *, char *);
void FUN_001064f8(M *);
void FUN_001064c8(M *, unsigned int);
void FUN_0010a138(M *, unsigned int, char *);
void FUN_001070c8(M *);
void FUN_00109db0(void *);
void FUN_00109c88(M *m) {
    unsigned int v;
    m->f236 = 0;
    v = FUN_00106c88(m, 32);
    m->w = v >> 20;
    m->h = (v >> 8) & 0xfff;
    if (m->h > 2800) FUN_00109b10(m, DAT_004d22f8);
    v = FUN_00106c88(m, 30);
    m->br = v >> 12;
    m->vbv = (v >> 1) & 0x3ff;
    if ((m->iqm = FUN_00106c88(m, 1)) != 0) {
        FUN_001064f8(m);
        FUN_001064c8(m, 0x50000000);
        FUN_001064f8(m);
    } else {
        FUN_0010a138(m, 0x50000000, DAT_00481d40);
    }
    if ((m->niqm = FUN_00106c88(m, 1)) != 0) {
        FUN_001064f8(m);
        FUN_001064c8(m, 0x58000000);
        FUN_001064f8(m);
    } else {
        FUN_0010a138(m, 0x58000000, DAT_00481d80);
    }
    FUN_001070c8(m);
    FUN_00109db0(m->mp);
}
