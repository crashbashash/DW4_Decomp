extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c4a30[4];
extern int DAT_004c4a40[4];
extern int DAT_00501a58[4];
extern int DAT_005886d8[4];
int FUN_0034e300(void);
}

int FUN_0034e300(void) {
    if (DAT_005886d8[0] == 0) {
        DAT_005886d8[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c4a30[0], &DAT_004c4a40[0], 4);
    }
    return DAT_005886d8[0];
}
