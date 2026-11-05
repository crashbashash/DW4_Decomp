extern "C" {
typedef struct F { char p0[12]; int f12; char p1[4]; int f20; char p2[20]; unsigned char b44; char p3[51]; int f96; } F;
typedef struct Ent { char p[16]; short s16; short s18; } Ent;
typedef struct Tab { char p[16]; Ent **data; } Tab;
int strcpy(char *, int);
int FUN_002618c0(char *, int);
int FUN_00261b78(int, int);
int FUN_003082b0(...);
int FUN_00333440(int);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_004fffa0[4];
extern int DAT_004fffe0[4];
extern int DAT_00500020[4];
extern Tab *DAT_00587620[4];
extern unsigned char GPR_00554de8;
extern unsigned char GPR_00554df0;
extern unsigned char GPR_00554df4;
extern unsigned char GPR_00554df8;
void Gap__igAdxFile__vfunc_21(int *out, F *f, unsigned int mode) {
    char sp30[256];
    int r, idx;
    Ent *e;
    if (GPR_00554de8 == 0) {
        *out = DAT_004fb418[0];
        return;
    }
    if (f->b44 != 0) {
        *out = DAT_004fb410[0];
        return;
    }
    if (mode == 8) {
        mode = f->f20;
    }
    switch (mode) {
    case 0:
        if (GPR_00554df0 == 0) {
            r = FUN_003082b0(DAT_004fffa0, f->f12);
            if (r != 1 && r == 2) GPR_00554df0 = 1;
        }
        goto L4;
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
        if (GPR_00554df4 == 0) {
            r = FUN_003082b0(DAT_004fffe0, f->f12);
            if (r != 1 && r == 2) GPR_00554df4 = 1;
        }
        *out = DAT_004fb418[0];
        return;
    default:
        if (GPR_00554df8 == 0) {
            r = FUN_003082b0(DAT_00500020);
            if (r != 1 && r == 2) GPR_00554df8 = 1;
        }
        *out = DAT_004fb418[0];
        return;
    case 4:
L4:
        idx = FUN_00333440(f->f12);
        if (idx != -1) {
            e = DAT_00587620[0]->data[idx];
            f->f96 = FUN_00261b78(e->s16, e->s18);
        } else {
            strcpy(sp30, f->f12);
            f->f96 = FUN_002618c0(sp30, 0);
        }
        if (f->f96 == 0) {
            *out = DAT_004fb418[0];
            return;
        }
        f->b44 = 1;
        *out = DAT_004fb410[0];
        return;
    }
}
}
