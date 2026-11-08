typedef struct { int a; int flag; int pad[2]; } E;
extern int DAT_00481f08;
extern E DAT_00558f80[32];
void FUN_0010e9d0(void);
int FUN_0010af20(int);
int FUN_0010af00(int);
E *FUN_0010ea30(void) {
    E *e;
    FUN_0010e9d0();
    FUN_0010af20(DAT_00481f08);
    for (e = DAT_00558f80; e < DAT_00558f80 + 32; e++) {
        if (e->flag == 0) {
            e->flag = 0x10000000;
            FUN_0010af00(DAT_00481f08);
            return e;
        }
    }
    FUN_0010af00(DAT_00481f08);
    return 0;
}
