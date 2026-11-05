/* 0x00361d30 - FUN_00361d30. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c6ca0[4];
extern int DAT_004c6cb0[4];
extern int DAT_00505188[4];
extern int DAT_00589660[4];
int FUN_00361d30(void);
}

int FUN_00361d30(void) {
    if (DAT_00589660[0] == 0) {
        DAT_00589660[0] = igMetaEnum_Create(&DAT_00505188[0], &DAT_004c6ca0[0], &DAT_004c6cb0[0], 3);
    }
    return DAT_00589660[0];
}
