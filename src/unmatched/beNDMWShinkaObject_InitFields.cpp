extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cc210[4];
extern int DAT_004cc260[4];
extern int DAT_004cc2b0[4];
extern int DAT_004cc300[4];
extern int DAT_0058bff0[4];
void beNDMWShinkaObject_InitFields(void);
}
void beNDMWShinkaObject_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bff0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc210[0], 0x13);
    igMetaObject_NameFields(temp_s0, &DAT_004cc260[0], &DAT_004cc2b0[0], &DAT_004cc300[0], temp_s1);
}
