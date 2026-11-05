int FUN_00100610();
int FUN_001007e0();
int FUN_00238110();
int FUN_004578c0();
int StringChunk_ReleaseHeader();
extern int DAT_0058ca58[4];
extern int DAT_0058ca60[4];
extern int DAT_0058ca68[4];
extern int DAT_0058ca70[4];
extern int DAT_0058ca78[4];
extern int DAT_0058ca80[4];
extern int DAT_0058ca88[4];
extern int DAT_0058ca90[4];
extern int DAT_0058ca98[4];
extern int DAT_0058caa0[4];
extern int DAT_0058caa8[4];
extern int DAT_0058ca38[4];
extern int DAT_0058ca40[4];
extern int DAT_0058ca48[4];
extern int DAT_0058ca50[4];
typedef struct Frame {
    void *f0;
    char pad[88];
    unsigned char f92; unsigned char f93; unsigned char f94; unsigned char f95; unsigned char f96;
    char pad2[67];
    unsigned char f164; unsigned char f165; unsigned char f166; unsigned char f167; unsigned char f168; unsigned char f169;
    char pad3[62];
    int f232;
    void *f236;
} Frame;
typedef struct Sub { char pad[8]; int f8; } Sub;
typedef struct W { char pad[184]; unsigned char f184; unsigned char f185; unsigned char f186; unsigned char f187; int f188; unsigned char f192; unsigned char f193; unsigned char f194; unsigned char f195; unsigned char f196; unsigned char f197; unsigned char f198; unsigned char f199; unsigned char f200; unsigned char f201; unsigned char f202; } W;
typedef struct Arg { char pad[12]; W *f12; char pad2[44]; Sub *f60; } Arg;
extern Frame *DAT_0056dc50[4];
void FUN_0045f930(Arg *arg0) {
    int sp0[3];
    int sp1[3];
    int sp2[3];
    int sp3[3];
    int sp4[3];
    int sp5[3];
    int sp6[3];
    int sp7[3];
    int sp8[3];
    int sp9[3];
    int sp10[3];
    int sp11[3];
    int sp12[3];
    int sp13[3];
    int sp14[3];
    Frame *f;
    Frame *s0;
    Frame *g;
    unsigned char s1;
    int v;
    int s1i;
    void *p;
    int *h;
    int rc;
    if (DAT_0056dc50[0] == 0) {
        f = (Frame *)FUN_001007e0(240);
        if (f != 0) f = (Frame *)FUN_00238110(f);
        DAT_0056dc50[0] = f;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    s0 = DAT_0056dc50[0];
    s1 = arg0->f60->f8 > 0;
    if (s0->f92 != 0) {
        arg0->f12->f192 = s1;
    } else {
        arg0->f12->f192 = s0->f94;
    }
    sp0[1] = 0;
    sp0[0] = 2;
    sp0[2] = DAT_0058ca58[0];
    FUN_004578c0(arg0->f12, sp0);
    if (s0->f93 != 0) {
        v = !s1;
    } else {
        v = s0->f95;
    }
    s1i = v & 0xFF;
    arg0->f12->f193 = (s1i & ((!s0->f96) & 0xFF)) != 0;
    sp1[1] = 0;
    sp1[0] = 2;
    sp1[2] = DAT_0058ca60[0];
    FUN_004578c0(arg0->f12, sp1);
    arg0->f12->f194 = (s1i & s0->f96) != 0;
    sp2[1] = 0;
    sp2[0] = 2;
    sp2[2] = DAT_0058ca68[0];
    FUN_004578c0(arg0->f12, sp2);
    arg0->f12->f195 = s0->f168;
    sp3[1] = 0;
    sp3[0] = 2;
    sp3[2] = DAT_0058ca70[0];
    FUN_004578c0(arg0->f12, sp3);
    arg0->f12->f196 = s0->f169;
    sp4[1] = 0;
    sp4[0] = 2;
    sp4[2] = DAT_0058ca78[0];
    FUN_004578c0(arg0->f12, sp4);
    arg0->f12->f197 = s0->f166;
    sp5[1] = 0;
    sp5[0] = 2;
    sp5[2] = DAT_0058ca80[0];
    FUN_004578c0(arg0->f12, sp5);
    arg0->f12->f198 = s0->f167;
    sp6[1] = 0;
    sp6[0] = 2;
    sp6[2] = DAT_0058ca88[0];
    FUN_004578c0(arg0->f12, sp6);
    arg0->f12->f199 = s0->f164;
    sp7[1] = 0;
    sp7[0] = 2;
    sp7[2] = DAT_0058ca90[0];
    FUN_004578c0(arg0->f12, sp7);
    arg0->f12->f200 = s0->f165;
    sp8[1] = 0;
    sp8[0] = 2;
    sp8[2] = DAT_0058ca98[0];
    FUN_004578c0(arg0->f12, sp8);
    arg0->f12->f201 = 0;
    sp9[1] = 0;
    sp9[0] = 2;
    sp9[2] = DAT_0058caa0[0];
    FUN_004578c0(arg0->f12, sp9);
    arg0->f12->f202 = 0;
    sp10[1] = 0;
    sp10[0] = 2;
    sp10[2] = DAT_0058caa8[0];
    FUN_004578c0(arg0->f12, sp10);
    arg0->f12->f184 = 0;
    sp11[1] = 0;
    sp11[0] = 2;
    sp11[2] = DAT_0058ca38[0];
    FUN_004578c0(arg0->f12, sp11);
    arg0->f12->f185 = 1;
    sp12[1] = 0;
    sp12[0] = 2;
    sp12[2] = DAT_0058ca40[0];
    FUN_004578c0(arg0->f12, sp12);
    arg0->f12->f186 = 0;
    sp13[1] = 0;
    sp13[0] = 2;
    sp13[2] = DAT_0058ca48[0];
    FUN_004578c0(arg0->f12, sp13);
    arg0->f12->f188 = 0;
    sp14[1] = 0;
    sp14[0] = 2;
    sp14[2] = DAT_0058ca50[0];
    FUN_004578c0(arg0->f12, sp14);
    if (DAT_0056dc50[0] != 0) {
        if (--DAT_0056dc50[0]->f232 <= 0) {
            f = DAT_0056dc50[0];
            if (f != 0) {
                if (&f->f236) {
                    p = f->f236;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (f != 0) {
                    p = f->f0;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                FUN_00100610(f);
            }
            DAT_0056dc50[0] = 0;
        }
    }
}
