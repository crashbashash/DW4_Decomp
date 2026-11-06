extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c4028[4];
extern int DAT_004c4038[4];
extern int DAT_004c4048[4];
extern int DAT_004c4058[4];
extern int DAT_00588200[4];
void beSvGetFreeSizeApi_InitFields(void);
}
void beSvGetFreeSizeApi_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_00588200[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4028[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c4038[0], &DAT_004c4048[0], &DAT_004c4058[0], temp_s1);
}
