extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c6cc0[4];
extern int DAT_004c6cd0[4];
extern int DAT_00504990[4];
extern int DAT_00589668[4];
int FUN_00361d90(void);
}

int FUN_00361d90(void) {
    if (DAT_00589668[0] == 0) {
        DAT_00589668[0] = igMetaEnum_Create(&DAT_00504990[0], &DAT_004c6cc0[0], &DAT_004c6cd0[0], 4);
    }
    return DAT_00589668[0];
}
