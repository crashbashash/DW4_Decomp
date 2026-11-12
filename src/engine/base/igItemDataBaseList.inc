igMetaObject *FUN_002280b0(void) {
    if (g_igItemDataBaseList_metaObject[0] == 0) {
        g_igItemDataBaseList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igItemDataBaseList_metaObject[0];
}

igMetaObject *igItemDataBaseList_GetMetaObject(void)
{
    igMetaObject *g = g_igItemDataBaseList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228190();
    return g_igItemDataBaseList_metaObject[0];
}

int igItemDataBaseList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c340[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00228190(void)
{
    igMetaObject_RunStaticInit(igItemDataBaseList_Register);
}

void igItemDataBaseList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igItemDataBaseList_metaObject,
        igCompoundList_Register,
        igCompoundList_GetPublishedMetaObject,
        thunk_igItemDataBaseList_GetMetaObject,
        igItemDataBaseList_className,
        0x14, /* instance size */
        igItemDataBaseList_GetVTable,
        &igItemDataBaseList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igItemDataBaseList_GetMetaObject(void) {
    igItemDataBaseList_GetMetaObject();
}

igMetaObject *FUN_00228220(void) {
    return g_igCompoundList_metaObject[0];
}

void igItemDataBaseList_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void **temp_v0;
    S_obj *temp_s0;

    temp_s1 = (void *)(g_igItemDataBaseList_metaObject[0]);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_004e79a8[0]));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (S_obj *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    temp_s0->f60 = FUN_00228570();
    temp_s0->f56 = 0;
    temp_s0->f28 = (int)(&DAT_0056d9d0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    temp_s0->f4 = temp_s0->f4 - 1;
    if (((unsigned long long) ((long long) temp_s0->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

