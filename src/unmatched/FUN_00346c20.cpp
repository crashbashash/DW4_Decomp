extern "C" {
/* 0x00346c20 - FUN_00346c20. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c3c50[4];
extern int DAT_004c3ca0[4];
extern int DAT_00501a58[4];
extern int DAT_00588018[4];
int FUN_00346c20(void) {
    if (DAT_00588018[0] == 0) {
        DAT_00588018[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c3c50[0], &DAT_004c3ca0[0], 0x12);
    }
    return DAT_00588018[0];
}
}
