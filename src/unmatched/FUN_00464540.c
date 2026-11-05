int FUN_00100610();
int FUN_001007e0();
int FUN_00238110();
int FUN_004578c0();
int FUN_00464170();
int StringChunk_ReleaseHeader();
extern int DAT_0058cd48[4];
extern int DAT_0058cd50[4];
extern int DAT_0058cd58[4];
typedef struct Obj { char p[80]; float f80; float f84; float f88; } Obj;
typedef struct Arg { char p[12]; Obj *o; } Arg;
typedef struct Rec { int t; int z; int v; } Rec;
typedef struct Frame {
    void *f0;
    char pad[60];
    float f64;
    unsigned char b68;
    char pad2[3];
    float f72;
    float f76;
    char pad3[152];
    int f232;
    void *f236;
} Frame;
extern Frame *DAT_0056dc50[4];
void FUN_00464540(Arg *arg0, int arg1) {
    int sp60[3];
    float sp6C;
    Rec r1;
    Rec r2;
    Rec r3;
    Frame *s0;
    Frame *f;
    void *p;
    int *h;
    int rc;
    FUN_00464170(arg1, sp60, &sp6C, 1, -1);
    if (DAT_0056dc50[0] == 0) {
        f = (Frame *)FUN_001007e0(240);
        if (f != 0) f = (Frame *)FUN_00238110(f);
        DAT_0056dc50[0] = f;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    s0 = DAT_0056dc50[0];
    if (!(sp6C <= 0.0f) && s0->b68 != 0) {
        arg0->o->f84 = sp6C / 100.0f;
        arg0->o->f88 = 3.0f * sp6C;
    } else {
        arg0->o->f84 = s0->f72;
        arg0->o->f88 = s0->f76;
    }
    r1.z = 0;
    r1.t = 2;
    r1.v = DAT_0058cd50[0];
    FUN_004578c0(arg0->o, &r1);
    r2.t = 2;
    r2.z = 0;
    r2.v = DAT_0058cd58[0];
    FUN_004578c0(arg0->o, &r2);
    arg0->o->f80 = s0->f64;
    r3.t = 2;
    r3.z = 0;
    r3.v = DAT_0058cd48[0];
    FUN_004578c0(arg0->o, &r3);
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
