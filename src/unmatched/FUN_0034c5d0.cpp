extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c4670[4];
extern int DAT_004c4690[4];
extern int DAT_00501a58[4];
extern int DAT_00588508[4];
int FUN_0034c5d0(void);
}

int FUN_0034c5d0(void) {
    if (DAT_00588508[0] == 0) {
        DAT_00588508[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c4670[0], &DAT_004c4690[0], 8);
    }
    return DAT_00588508[0];
}
