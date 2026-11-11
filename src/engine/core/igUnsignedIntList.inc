void FUN_002ca410(int arg0) {
    FUN_002ca530();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586858), (MemoryPool *)arg0);
}

int FUN_002ca450(void) {
    if (DAT_00586858[0] == 0) {
        DAT_00586858[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00586858[0];
}

igMetaObject *igUnsignedIntList_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ca530();
    return g_igUnsignedIntList_metaObject[0];
}

int igUnsignedIntList_GetVTable(void) {
    struct Obj_2ca4f0 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_0052a3a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002ca530(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igUnsignedIntList_Register);
}

void igUnsignedIntList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igUnsignedIntList_metaObject),
        igDataList_Register,                       /* base class registrar (igDataList) */
        igDataList_GetPublishedMetaObject,
        thunk_igUnsignedIntList_GetMetaObject,
        igUnsignedIntList_className,
        0x14, /* instance size */
        igUnsignedIntList_GetVTable,
        &igUnsignedIntList_InitFields_002ca5c0[0], /* field adder (class InitFields) */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igUnsignedIntList_GetMetaObject(void) {
    igUnsignedIntList_GetMetaObject();
}

void FUN_002ca5c0(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)DAT_00586858)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, (const char *)&DAT_004f5eb0[0])));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = igUnsignedIntMetaField_GetDefaultDescriptor();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_00586860[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

