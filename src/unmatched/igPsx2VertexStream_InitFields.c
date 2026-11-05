/* 0x001520f0 - igPsx2VertexStream_InitFields. char stores at +38, local for a call result before a constant store, declaration order. Verified byte-identical by tools/verify.py. */
int FUN_002d3890();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
int igUnsignedCharMetaField_GetDefaultDescriptor();
extern int DAT_00489c60[4];
extern int DAT_00489c90[4];
extern int DAT_00489cc0[4];
extern int DAT_00489cf0[4];
extern int DAT_00560420[4];
void igPsx2VertexStream_InitFields(void) {
    void *temp_s0;
    void *temp_s1;
    int temp_s2;
    void *f;
    void *temp_s1_2;

    temp_s0 = (void *)DAT_00560420[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489c60[0], 0xA);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2), 1);
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)) + 38) = 0;
    f = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2);
    *(int *)((char *)f + 52) = 0x10;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7)) + 38) = 0;
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    *(int *)((char *)(temp_s1_2) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, &DAT_00489c90[0], &DAT_00489cc0[0], &DAT_00489cf0[0], temp_s2);
}
