extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c81f0[4];
extern int DAT_004c8210[4];
extern int DAT_005016f0[4];
extern int DAT_0058a020[4];
int FUN_0036dcd0(void);
}

int FUN_0036dcd0(void) {
    if (DAT_0058a020[0] == 0) {
        DAT_0058a020[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c81f0[0], &DAT_004c8210[0], 7);
    }
    return DAT_0058a020[0];
}
