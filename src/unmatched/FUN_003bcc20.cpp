/* 0x003bcc20 - FUN_003bcc20. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004ca300[4];
extern int DAT_004ca320[4];
extern int DAT_00510d58[4];
extern int DAT_0058b158[4];
int FUN_003bcc20(void);
}
int FUN_003bcc20(void) {
    if (DAT_0058b158[0] == 0) {
        DAT_0058b158[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca300[0], &DAT_004ca320[0], 7);
    }
    return DAT_0058b158[0];
}
