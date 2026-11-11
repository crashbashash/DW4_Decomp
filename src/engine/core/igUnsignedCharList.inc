void FUN_002c99b0(int arg0) {
    FUN_002c9a80();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586818), (MemoryPool *)arg0);
}

igMetaObject *igUnsignedCharList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedCharList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c9a80();
    return g_igUnsignedCharList_metaObject[0];
}

int igUnsignedCharList_GetVTable(void) {
    Obj_2c9a40 o;

    igObject_InitHeader((ObjectHeader *)&o);
    o.vt = &DAT_00531dc0[0];
    return *(int *)((char *)&o + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002c9a80(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedCharList_Register);
}

void igUnsignedCharList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedCharList_metaObject),
        igDataList_Register,                        /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igUnsignedCharList_GetMetaObject,
        igUnsignedCharList_className,
        0x14, /* instance size */
        igUnsignedCharList_GetVTable,
        &igUnsignedCharList_InitFields_002c9b10[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igUnsignedCharList_GetMetaObject(void) {
    igUnsignedCharList_GetMetaObject();
}

void FUN_002c9b10(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(DAT_00586818[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)&DAT_004f5eb0[0])));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586820[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

