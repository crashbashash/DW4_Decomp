extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c6ce0[4];
extern int DAT_004c6d10[4];
extern int DAT_00501a58[4];
extern int DAT_00589670[4];
int FUN_00361df0(void);
}

int FUN_00361df0(void) {
    if (DAT_00589670[0] == 0) {
        DAT_00589670[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c6ce0[0], &DAT_004c6d10[0], 9);
    }
    return DAT_00589670[0];
}
