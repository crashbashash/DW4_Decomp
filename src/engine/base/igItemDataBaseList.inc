igMetaObject *g_igItemDataBaseList_metaObject;

igMetaObject *igItemDataBaseList_GetOrCreateMetaObject(void) {
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
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
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
        igItemDataBaseList_GetMetaObjectFunction,
        "igItemDataBaseList",
        0x14, /* instance size */
        igItemDataBaseList_GetVTable,
        &igItemDataBaseList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igItemDataBaseList_GetMetaObjectFunction(void) {
    igItemDataBaseList_GetMetaObject();
}

igMetaObject *igCompoundList_GetPublishedMetaObject(void) {
    return g_igCompoundList_metaObject;
}

void igItemDataBaseList_InitFields(void) {
    static int externalEnumStorage;
    int field;
    igMetaObject *meta;
    void **field2;
    S_obj *field3;

    meta = g_igItemDataBaseList_metaObject;
    field2 = (void **)(igMetaObject_FindFieldByName(meta, "_data"));
    field = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(*(int *)((char *)(meta) + 40)), (int)field2);
    field3 = (S_obj *)(((DW4VC_84_1 *)(field2))->vX((int)(1)));
    field3->f60 = FUN_00228570();
    field3->f56 = 0;
    field3->f28 = (int)(&externalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, field, (igMetaField *)field3);
    field3->f4 = field3->f4 - 1;
    if (((unsigned long long) ((long long) field3->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)field3);
    }
}

