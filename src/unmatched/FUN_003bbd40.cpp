extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004ca118[4];
extern int DAT_004ca128[4];
extern int DAT_00510d58[4];
extern int DAT_0058b058[4];
int FUN_003bbd40(void);
}
int FUN_003bbd40(void) {
    if (DAT_0058b058[0] == 0) {
        DAT_0058b058[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca118[0], &DAT_004ca128[0], 3);
    }
    return DAT_0058b058[0];
}
