extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c58f0[4];
extern int DAT_004c5980[4];
extern int DAT_005016f0[4];
extern int DAT_00588e50[4];
int FUN_00356ab0(void);
}

int FUN_00356ab0(void) {
    if (DAT_00588e50[0] == 0) {
        DAT_00588e50[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c58f0[0], &DAT_004c5980[0], 0x21);
    }
    return DAT_00588e50[0];
}
