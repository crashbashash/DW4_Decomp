extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004c9f58[4];
extern int DAT_004c9f60[4];
extern int DAT_004c9f68[4];
extern int DAT_004c9f70[4];
extern int DAT_0058af88[4];
void beNDMWStatusCtrlEquip_InitFields(void);
}
void beNDMWStatusCtrlEquip_InitFields(void) {
    void *temp_s0;
    int temp_s1;

    temp_s0 = (void *)DAT_0058af88[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9f58[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c9f60[0], &DAT_004c9f68[0], &DAT_004c9f70[0], temp_s1);
}
