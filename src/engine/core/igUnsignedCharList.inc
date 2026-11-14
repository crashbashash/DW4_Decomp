void igUnsignedCharList_Create(int arg0) {
    igUnsignedCharList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586818), (igMemoryPoolView *)arg0);
}

igMetaObject *igUnsignedCharList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedCharList_EnsureRegistered();
    return g_igUnsignedCharList_metaObject[0];
}

int igUnsignedCharList_GetVTable(void) {
    igUnsignedCharList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531dc0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igUnsignedCharList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedCharList_Register);
}

void igUnsignedCharList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedCharList_metaObject),
        igDataList_Register,                        /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        igUnsignedCharList_GetMetaObjectFunction,
        igUnsignedCharList_className,
        0x14, /* instance size */
        igUnsignedCharList_GetVTable,
        &igUnsignedCharList_InitFields_002c9b10[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igUnsignedCharList_GetMetaObjectFunction(void) {
    igUnsignedCharList_GetMetaObject();
}

void igUnsignedCharList_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(g_igUnsignedCharList_metaObject[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((igObjectDispatchView *)(temp_v0))->cloneViaMetadata((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586820[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

