extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004c6b50[4];
extern int DAT_004c6b70[4];
extern int DAT_005016f0[4];
extern int DAT_005895c8[4];
int FUN_00360b10(void);
}

int FUN_00360b10(void) {
    if (DAT_005895c8[0] == 0) {
        DAT_005895c8[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c6b50[0], &DAT_004c6b70[0], 8);
    }
    return DAT_005895c8[0];
}
