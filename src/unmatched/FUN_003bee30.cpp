extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004ca730[4];
extern int DAT_004ca760[4];
extern int DAT_00510d58[4];
extern int DAT_0058b350[4];
int FUN_003bee30(void);
}
int FUN_003bee30(void) {
    if (DAT_0058b350[0] == 0) {
        DAT_0058b350[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca730[0], &DAT_004ca760[0], 0xB);
    }
    return DAT_0058b350[0];
}
