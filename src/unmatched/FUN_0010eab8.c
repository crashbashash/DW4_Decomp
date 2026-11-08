typedef struct { int pad[4]; } E;
extern int DAT_00481f08;
extern E DAT_00558f80[];
void FUN_0010e9d0(void);
int FUN_0010af20(int);
int FUN_0010af00(int);
E *FUN_0010eab8(unsigned int i) {
    E *e;
    FUN_0010e9d0();
    FUN_0010af20(DAT_00481f08);
    if (i >= 32) {
        FUN_0010af00(DAT_00481f08);
        return 0;
    }
    e = &DAT_00558f80[i];
    FUN_0010af00(DAT_00481f08);
    return e;
}
