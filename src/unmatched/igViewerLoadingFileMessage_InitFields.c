/* 0x0045a830 — igViewerLoadingFileMessage_InitFields. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igStringMetaField_SetDefaultText(int, int *);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);
extern int DAT_004d0e38[4];
extern int DAT_004d0e40[4];
extern int DAT_004d0e48[4];
extern int DAT_004d0e50[4];
extern int DAT_0051eef0[4];
extern int DAT_0058c910[4];
void igViewerLoadingFileMessage_InitFields(void);
void igViewerLoadingFileMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c910[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e38[0], 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), &DAT_0051eef0[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004d0e40[0], &DAT_004d0e48[0], &DAT_004d0e50[0], temp_s1);
}
