extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c8380[4];
extern int DAT_004c8388[4];
extern int DAT_00506530[4];
extern int DAT_0058a0c8[4];
int FUN_0036e8e0(void);
}

int FUN_0036e8e0(void) {
    if (DAT_0058a0c8[0] == 0) {
        DAT_0058a0c8[0] = igMetaEnum_Create(&DAT_00506530[0], &DAT_004c8380[0], &DAT_004c8388[0], 2);
    }
    return DAT_0058a0c8[0];
}
