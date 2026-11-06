extern "C" {
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004cbb60[4];
extern int DAT_004cbb68[4];
extern int DAT_004cbb70[4];
extern int DAT_004cbb78[4];
extern int DAT_0058bc98[4];
void beNDMWMcSlotXbox_InitFields(void);
}
void beNDMWMcSlotXbox_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058bc98[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cbb60[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cbb68[0], &DAT_004cbb70[0], &DAT_004cbb78[0], temp_s1);
}
