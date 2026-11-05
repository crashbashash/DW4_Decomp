extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c8390[4];
extern int DAT_004c83a0[4];
extern int DAT_005065b0[4];
extern int DAT_0058a0d0[4];
int FUN_0036e940(void);
}

int FUN_0036e940(void) {
    if (DAT_0058a0d0[0] == 0) {
        DAT_0058a0d0[0] = igMetaEnum_Create(&DAT_005065b0[0], &DAT_004c8390[0], &DAT_004c83a0[0], 3);
    }
    return DAT_0058a0d0[0];
}
