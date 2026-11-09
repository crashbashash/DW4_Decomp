struct O { int w0; int w4; };
int FUN_002d6e60();
struct O *FUN_0032a100();
int FUN_0032a180();
int FUN_0032a1b0();
struct O *FUN_0032a1e0();
int FUN_0032a5f0();
int List_InsertWords();
void FUN_0032a260(void);
extern int DAT_004ffd98[4];
extern int DAT_004ffda8[4];
extern int DAT_004ffdb8[4];
extern char DAT_70000000[];
extern char DAT_00004000[];
void FUN_0032f4b0(int arg0, int arg1) {
    struct O * sp2C;
    struct O *v;

    FUN_0032a5f0(arg0);
    v = FUN_0032a1e0(0xA8);
    if (v != 0) {
        v = FUN_0032a100(v);
    }
    sp2C = v;
    v->w0 = 0;
    sp2C->w4 = 0x02000000;
    FUN_0032a180(sp2C, &DAT_004ffd98[0]);
    FUN_0032a1b0(sp2C, &DAT_004ffda8[0]);
    List_InsertWords(arg1, FUN_002d6e60(arg1, &sp2C, FUN_0032a260), 1, &sp2C);
    v = FUN_0032a1e0(0xA8);
    if (v != 0) {
        v = FUN_0032a100(v);
    }
    sp2C = v;
    v->w0 = (int)&DAT_70000000[0];
    sp2C->w4 = (int)&DAT_00004000[0];
    FUN_0032a180(sp2C, &DAT_004ffdb8[0]);
    FUN_0032a1b0(sp2C, &DAT_004ffda8[0]);
    List_InsertWords(arg1, FUN_002d6e60(arg1, &sp2C, FUN_0032a260), 1, &sp2C);
}
