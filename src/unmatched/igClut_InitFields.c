/* The thunk address is spelled as a function declaration so it is addressed absolutely (lui/addiu)
 * rather than gp-relative. */
int FUN_002d3890();
int FUN_002dc7a0();
int FUN_002ea4b0();
int igMetaObject_CreateFields();
void *igMetaObject_GetFieldAt();
int igMetaObject_GetFieldCount();
int igMetaObject_NameFields();
int igUnsignedCharMetaField_GetDefaultDescriptor();
extern int DAT_00489090[4];
extern int DAT_004890b0[4];
extern int DAT_004890d0[4];
extern int DAT_004890f0[4];
extern int DAT_00489110[4];
extern void * DAT_0055feb8[4];
int FUN_002d1870();
int thunk_igPsx2Clut_GetMetaObject();

void igClut_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(DAT_0055feb8[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00489090[0], 7);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00489110[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&FUN_002d1870);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), -1);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    FUN_002d3890(temp_v0_2, 1);
    *(char *)((char *)(temp_v0_2) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004890b0[0], &DAT_004890d0[0], &DAT_004890f0[0], temp_s2);
    *(int *)((char *)(DAT_0055feb8[0]) + 60) = (int)(&thunk_igPsx2Clut_GetMetaObject);
}
