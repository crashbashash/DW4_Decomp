typedef struct { char p0[316]; unsigned int w; unsigned int h; char p2[8]; int br; int vbv; int prog; int chroma; char p3[1796]; int f2144; } M;
extern char DAT_004d2310[];
extern char DAT_004d2338[];
unsigned int FUN_00106c88(M *, int);
int FUN_00109b10(M *, char *);
void FUN_00105228(int);
void FUN_0010a218(M *m) {
    unsigned int v;
    unsigned int id, brx, hsx, vsx, vbvx;
    m->f2144 = 1;
    FUN_00105228(0);
    v = FUN_00106c88(m, 28);
    brx = (v >> 1) & 0xfff;
    m->chroma = (v >> 17) & 3;
    vsx = (v >> 13) & 3;
    hsx = (v >> 15) & 3;
    if (m->chroma != 1) FUN_00109b10(m, DAT_004d2310);
    m->prog = (v >> 19) & 1;
    id = v >> 20;
    vbvx = FUN_00106c88(m, 16) >> 8;
    if (id != 0x48 && id != 0x58 && id != 0x44) FUN_00109b10(m, DAT_004d2338);
    m->w = (hsx << 12) | (m->w & 0xfff);
    m->h = (vsx << 12) | (m->h & 0xfff);
    m->br += brx << 18;
    m->vbv += vbvx << 10;
}
