extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c6370[4];
extern int DAT_005016f0[4];
extern int DAT_00589248[4];
extern int DAT_00589250[4];
int FUN_0035bfb0(void);
}

int FUN_0035bfb0(void) {
    if (DAT_00589248[0] == 0) {
        DAT_00589248[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c6370[0], &DAT_00589250[0], 1);
    }
    return DAT_00589248[0];
}
