extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c4550[4];
extern int DAT_004c4570[4];
extern int DAT_005016f0[4];
extern int DAT_00588490[4];
int FUN_0034b980(void);
}

int FUN_0034b980(void) {
    if (DAT_00588490[0] == 0) {
        DAT_00588490[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c4550[0], &DAT_004c4570[0], 7);
    }
    return DAT_00588490[0];
}
