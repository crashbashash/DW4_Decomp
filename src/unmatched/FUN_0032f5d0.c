struct O { int w0; int w4; };
int FUN_002d6e60();
struct O *FUN_0032a100();
int FUN_0032a180();
int FUN_0032a1b0();
struct O *FUN_0032a1e0();
int FUN_0032a600();
int List_InsertWords();
void FUN_0032a260(void);
extern int DAT_004ffa98[4];
extern int DAT_004ffdd0[4];
extern int DAT_004ffdf0[4];
extern int DAT_004ffe00[4];
extern char DAT_00522440[];
extern char DAT_00522480[];
extern char DAT_00546fb0[];
extern char DAT_00554974[];
extern char DAT_0000050d[];
void FUN_0032f5d0(int arg0, int arg1) {
    struct O * sp3C;
    struct O *v;
    char *mid;

    FUN_0032a600();
    v = FUN_0032a1e0(0xA8);
    if (v != 0) {
        v = FUN_0032a100(v);
    }
    sp3C = v;
    v->w0 = (int)&DAT_00522440[0];
    mid = DAT_00522480;
    sp3C->w4 = (int)(mid - DAT_00522440);
    FUN_0032a180(sp3C, &DAT_004ffdd0[0]);
    FUN_0032a1b0(sp3C, &DAT_004ffa98[0]);
    List_InsertWords(arg1, FUN_002d6e60(arg1, &sp3C, FUN_0032a260), 1, &sp3C);
    v = FUN_0032a1e0(0xA8);
    if (v != 0) {
        v = FUN_0032a100(v);
    }
    sp3C = v;
    v->w0 = (int)mid;
    sp3C->w4 = (int)(DAT_00546fb0 - mid);
    FUN_0032a180(sp3C, &DAT_004ffdf0[0]);
    FUN_0032a1b0(sp3C, &DAT_004ffa98[0]);
    List_InsertWords(arg1, FUN_002d6e60(arg1, &sp3C, FUN_0032a260), 1, &sp3C);
    v = FUN_0032a1e0(0xA8);
    if (v != 0) {
        v = FUN_0032a100(v);
    }
    sp3C = v;
    v->w0 = (int)&DAT_00554974[0];
    sp3C->w4 = (int)&DAT_0000050d[0];
    FUN_0032a180(sp3C, &DAT_004ffe00[0]);
    FUN_0032a1b0(sp3C, &DAT_004ffa98[0]);
    List_InsertWords(arg1, FUN_002d6e60(arg1, &sp3C, FUN_0032a260), 1, &sp3C);
}
