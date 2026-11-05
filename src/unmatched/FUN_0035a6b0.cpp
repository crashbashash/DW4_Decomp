extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c6130[4];
extern int DAT_004c6150[4];
extern int DAT_00501a58[4];
extern int DAT_00589158[4];
int FUN_0035a6b0(void);
}

int FUN_0035a6b0(void) {
    if (DAT_00589158[0] == 0) {
        DAT_00589158[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c6130[0], &DAT_004c6150[0], 6);
    }
    return DAT_00589158[0];
}
