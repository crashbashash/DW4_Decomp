int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c0fb8[4];
extern int DAT_004c0fc0[4];
extern int DAT_004f7f00[4];
extern int DAT_005865c8[4];
int FUN_002c66f0(void) {
    if (DAT_005865c8[0] == 0) {
        DAT_005865c8[0] = igMetaEnum_Create(&DAT_004f7f00[0], &DAT_004c0fb8[0], &DAT_004c0fc0[0], 2);
    }
    return DAT_005865c8[0];
}
