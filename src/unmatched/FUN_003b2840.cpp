extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c9710[4];
extern int DAT_004c9718[4];
extern int DAT_00510d58[4];
extern int DAT_0058ab08[4];
int FUN_003b2840(void);
}
int FUN_003b2840(void) {
    if (DAT_0058ab08[0] == 0) {
        DAT_0058ab08[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004c9710[0], &DAT_004c9718[0], 2);
    }
    return DAT_0058ab08[0];
}
