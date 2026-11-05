extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c63b0[4];
extern int DAT_004c63d0[4];
extern int DAT_00504990[4];
extern int DAT_00589288[4];
int FUN_0035c9e0(void);
}

int FUN_0035c9e0(void) {
    if (DAT_00589288[0] == 0) {
        DAT_00589288[0] = igMetaEnum_Create(&DAT_00504990[0], &DAT_004c63b0[0], &DAT_004c63d0[0], 5);
    }
    return DAT_00589288[0];
}
