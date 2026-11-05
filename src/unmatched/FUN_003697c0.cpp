extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c79d0[4];
extern int DAT_004c7a10[4];
extern int DAT_005016f0[4];
extern int DAT_00589c88[4];
int FUN_003697c0(void);
}

int FUN_003697c0(void) {
    if (DAT_00589c88[0] == 0) {
        DAT_00589c88[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c79d0[0], &DAT_004c7a10[0], 0xF);
    }
    return DAT_00589c88[0];
}
