extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c7348[4];
extern int DAT_005016f0[4];
extern int DAT_00589948[4];
extern int DAT_00589950[4];
int FUN_00366070(void);
}

int FUN_00366070(void) {
    if (DAT_00589948[0] == 0) {
        DAT_00589948[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c7348[0], &DAT_00589950[0], 1);
    }
    return DAT_00589948[0];
}
