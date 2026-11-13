void igBoolList_Create(int arg0) {
    FUN_002cb1f0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x5868A8), (MemoryPool *)arg0);
}

igMetaObject *FUN_002cb110(void) {
    if (g_igBoolList_metaObject[0] == 0) {
        g_igBoolList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    }
    return g_igBoolList_metaObject[0];
}

igMetaObject *igBoolList_GetMetaObject(void)
{
    igMetaObject *g = g_igBoolList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cb1f0();
    return g_igBoolList_metaObject[0];
}

int igBoolList_GetVTable(void) {
    struct Obj_2cb1b0 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_005319f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002cb1f0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igBoolList_Register);
}

void igBoolList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBoolList_metaObject),
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igBoolList_GetMetaObject,
        igBoolList_className,
        0x14, /* instance size */
        igBoolList_GetVTable,
        FUN_002cb280,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBoolList_GetMetaObject(void) {
    igBoolList_GetMetaObject();
}

void FUN_002cb280(void) {
    int temp_s2;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;

    temp_s1 = (void *)(((void * *)g_igBoolList_metaObject)[0]);
    temp_v0 = (void **)(((void **)igMetaObject_FindFieldByName((igMetaObject *)temp_s1, data)));
    temp_s2 = ObjectPointerList_FindIndex((char *)(*(int *)((char *)(temp_s1) + 40)), (int)temp_v0);
    temp_s0 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    *(int *)((char *)(temp_s0) + 60) = FUN_002cce00();
    *(int *)((char *)(temp_s0) + 56) = 0;
    *(int *)((char *)(temp_s0) + 28) = (int)(&DAT_005868b0[0]);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)temp_s1, temp_s2, (igMetaField *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

