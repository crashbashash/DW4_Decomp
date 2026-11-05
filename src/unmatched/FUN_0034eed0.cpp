extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c4b70[4];
extern int DAT_004c4b80[4];
extern int DAT_00501a58[4];
extern int DAT_00588780[4];
int FUN_0034eed0(void);
}

int FUN_0034eed0(void) {
    if (DAT_00588780[0] == 0) {
        DAT_00588780[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c4b70[0], &DAT_004c4b80[0], 4);
    }
    return DAT_00588780[0];
}
