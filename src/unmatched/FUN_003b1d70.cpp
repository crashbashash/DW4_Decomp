extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c9410[4];
extern int DAT_004c9440[4];
extern int DAT_00510ab0[4];
extern int DAT_0058a9b0[4];
int FUN_003b1d70(void);
}
int FUN_003b1d70(void) {
    if (DAT_0058a9b0[0] == 0) {
        DAT_0058a9b0[0] = igMetaEnum_Create(&DAT_00510ab0[0], &DAT_004c9410[0], &DAT_004c9440[0], 0xB);
    }
    return DAT_0058a9b0[0];
}
