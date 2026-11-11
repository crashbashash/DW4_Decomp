igMetaObject *igNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bdd30();
    return g_igNonRefCountedObjectList_metaObject[0];
}

int igNonRefCountedObjectList_GetVTable(void) {
    struct Obj_2bdcf0 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00524500[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002bdd30(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNonRefCountedObjectList_Register);
}

void igNonRefCountedObjectList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNonRefCountedObjectList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igNonRefCountedObjectList_GetMetaObject,
        igNonRefCountedObjectList_className,
        0x14, /* instance size */
        igNonRefCountedObjectList_GetVTable,
        &igNonRefCountedObjectList_InitFields_002bddc0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igNonRefCountedObjectList_GetMetaObject(void) {
    igNonRefCountedObjectList_GetMetaObject();
}

void FUN_002bddc0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_00585bb0[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)&DAT_004f5eb0[0])));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igObjectRefMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(char *)((char *)(temp_s0) + 66) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00585bb8[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

