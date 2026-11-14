igMetaObject *igNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedObjectList_EnsureRegistered();
    return g_igNonRefCountedObjectList_metaObject[0];
}

int igNonRefCountedObjectList_GetVTable(void) {
    igNonRefCountedObjectList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00524500[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igNonRefCountedObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNonRefCountedObjectList_Register);
}

void igNonRefCountedObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNonRefCountedObjectList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        igNonRefCountedObjectList_GetMetaObjectFunction,
        igNonRefCountedObjectList_className,
        0x14, /* instance size */
        igNonRefCountedObjectList_GetVTable,
        &igNonRefCountedObjectList_InitFields_002bddc0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igNonRefCountedObjectList_GetMetaObjectFunction(void) {
    igNonRefCountedObjectList_GetMetaObject();
}

void igNonRefCountedObjectList_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igNonRefCountedObjectList_metaObject[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
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

