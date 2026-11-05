/* Byte store through a named field pointer and the thunk typed as a function; verified by tools/verify.py. */
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
int igUnsignedCharMetaField_GetDefaultDescriptor();
extern int DAT_004c1e10[4];
extern int DAT_004c1e30[4];
extern int DAT_004c1e50[4];
extern int DAT_004c1e70[4];
extern void * DAT_00586d70[4];
int thunk_igFile_GetMetaObject();

void igPsx2File_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;
    void *temp_a0;

    temp_s0 = (void *)(DAT_00586d70[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c1e10[0], 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_a0 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7);
    *(char *)((char *)temp_a0 + 36) = 3;
    igMetaObject_NameFields(temp_s0, &DAT_004c1e30[0], &DAT_004c1e50[0], &DAT_004c1e70[0], temp_s2);
    *(int *)((char *)(DAT_00586d70[0]) + 64) = (int)(&thunk_igFile_GetMetaObject);
}
