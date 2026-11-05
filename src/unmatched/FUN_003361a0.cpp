extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c2980[4];
extern int DAT_004c2990[4];
extern int DAT_00500508[4];
extern int DAT_005877a8[4];
int FUN_003361a0(void) {
    if (DAT_005877a8[0] == 0) {
        DAT_005877a8[0] = igMetaEnum_Create(&DAT_00500508[0], &DAT_004c2980[0], &DAT_004c2990[0], 4);
    }
    return DAT_005877a8[0];
}
}
