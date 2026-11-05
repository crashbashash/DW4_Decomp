extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c5be0[4];
extern int DAT_004c5c00[4];
extern int DAT_005016f0[4];
extern int DAT_00588f28[4];
int FUN_00357600(void);
}

int FUN_00357600(void) {
    if (DAT_00588f28[0] == 0) {
        DAT_00588f28[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c5be0[0], &DAT_004c5c00[0], 8);
    }
    return DAT_00588f28[0];
}
