extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c83b0[4];
extern int DAT_004c83d0[4];
extern int DAT_00506670[4];
extern int DAT_0058a0d8[4];
int FUN_0036e9a0(void);
}

int FUN_0036e9a0(void) {
    if (DAT_0058a0d8[0] == 0) {
        DAT_0058a0d8[0] = igMetaEnum_Create(&DAT_00506670[0], &DAT_004c83b0[0], &DAT_004c83d0[0], 5);
    }
    return DAT_0058a0d8[0];
}
