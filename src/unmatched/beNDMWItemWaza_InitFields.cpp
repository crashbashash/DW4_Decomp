extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc088[4];
extern int DAT_004cc090[4];
extern int DAT_004cc098[4];
extern int DAT_004cc0a0[4];
extern int DAT_0058bf10[4];
void beNDMWItemWaza_InitFields(void);
}
void beNDMWItemWaza_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bf10[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc088[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc090[0], &DAT_004cc098[0], &DAT_004cc0a0[0], temp_s1);
}
