igMetaObject *g_igItemDataBaseList_metaObject;

igMetaObject *FUN_002280b0(void) {
    if (g_igItemDataBaseList_metaObject == 0) {
        g_igItemDataBaseList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igItemDataBaseList_metaObject;
}

igMetaObject *igItemDataBaseList_GetMetaObject(void)
{
    igMetaObject *g = g_igItemDataBaseList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228190();
    return g_igItemDataBaseList_metaObject;
}

int igItemDataBaseList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igItemDataBaseList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_00228190(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igItemDataBaseList_Register);
}

CallbackArray *igItemDataBaseList_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igItemDataBaseList_metaObject,
        (igMetaObjectRegisterFunction)igCompoundList_Register,
        (igMetaObjectGetFunction)igCompoundList_GetPublishedMetaObject,
        thunk_igItemDataBaseList_GetMetaObject,
        "igItemDataBaseList",
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
    return g_igCompoundList_metaObject;
}

void igItemDataBaseList_InitFields(void) {
    static int externalEnumStorage;
    int temp_s2;
    igMetaObject *temp_s1;
    void **temp_v0;
    S_obj *temp_s0;

    temp_s1 = g_igItemDataBaseList_metaObject;
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_data"));
    temp_s2 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_s0 = (S_obj *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    temp_s0->f60 = FUN_00228570();
    temp_s0->f56 = 0;
    temp_s0->f28 = (int)(&externalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, (igMetaField *)temp_s0);
    temp_s0->f4 = temp_s0->f4 - 1;
    if (((unsigned long long) ((long long) temp_s0->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
}

