extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c8360[4];
extern int DAT_004c8370[4];
extern int DAT_005064d0[4];
extern int DAT_0058a0c0[4];
int FUN_0036e880(void);
}

int FUN_0036e880(void) {
    if (DAT_0058a0c0[0] == 0) {
        DAT_0058a0c0[0] = igMetaEnum_Create(&DAT_005064d0[0], &DAT_004c8360[0], &DAT_004c8370[0], 3);
    }
    return DAT_0058a0c0[0];
}
