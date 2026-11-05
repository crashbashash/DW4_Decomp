extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c63f0[4];
extern int DAT_004c6410[4];
extern int DAT_00501a58[4];
extern int DAT_00589290[4];
int FUN_0035ca40(void);
}

int FUN_0035ca40(void) {
    if (DAT_00589290[0] == 0) {
        DAT_00589290[0] = igMetaEnum_Create(&DAT_00501a58[0], &DAT_004c63f0[0], &DAT_004c6410[0], 6);
    }
    return DAT_00589290[0];
}
