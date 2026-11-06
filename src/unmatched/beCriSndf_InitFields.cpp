extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c7600[4];
extern int DAT_004c7610[4];
extern int DAT_004c7620[4];
extern int DAT_004c7630[4];
extern int DAT_00589ab0[4];
void beCriSndf_InitFields(void);
}
void beCriSndf_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00589ab0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7600[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c7610[0], &DAT_004c7620[0], &DAT_004c7630[0], temp_s1);
}
