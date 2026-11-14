igMetaObject *igExternalDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igExternalDirEntry_EnsureRegistered();
    return g_igExternalDirEntry_metaObject[0];
}

int igExternalDirEntry_GetVTable(void) {
    igExternalDirEntry entry;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    igObject_InitHeader((igObject *)&entry);
    entry._name = 0;
    entry._vtable = (int)&DAT_00530360[0];
    entry._directoryName = 0;
    entry._entryName = 0;
    entry._externalFilePath = 0;
    t = *(int *)((char *)&entry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    entry._vtable = (int)&DAT_00530360[0];
    StringRef_Destruct_00130720(&entry._externalFilePath, -1);
    StringRef_Destruct_00130720(&entry._entryName, -1);
    StringRef_Destruct_00130720(&entry._directoryName, -1);
    FUN_0014f4e0(&entry, 0);
    return t;
}

void igExternalDirEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igExternalDirEntry_Register);
}

void igExternalDirEntry_Register(void) {
    CoreLibrary_MarkRegistered();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igExternalDirEntry_metaObject),
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igExternalDirEntry_GetMetaObjectFunction,
        igExternalDirEntry_className,
        0x2C, /* instance size */
        igExternalDirEntry_GetVTable,
        igExternalDirEntry_InitFields,
        0,                                          /* static-initializer callback item (appended on fresh configuration) */
        g_igExternalDirEntry_callbackList  /* 0-terminated dependency-callback list */
    );
}

void igExternalDirEntry_GetMetaObjectFunction(void) {
    igExternalDirEntry_GetMetaObject();
}

void igExternalDirEntry_InitFields(void) {
    igMetaObject *meta = g_igExternalDirEntry_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    int index;
    int fields;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igExternalDirEntry_ctorTable, 4);
    fields = meta->_metaFields;
    index = ObjectPointerList_FindIndex((char *)fields, (int)igMetaObject_FindFieldByName(meta, (const char *)text_ref));
    field = (igMetaField *)igObjectRefMetaField_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    igMetaField_Configure(field, (const char *)text_ref, DAT_00586458, 0x18, meta);
    ((igObjectRefMetaField *)field)->_metaObject = (int)g_igObject_metaObject[0];
    field->_persistent = 0;
    field->_externalEnumStorage = (int)DAT_00586458;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    igStringMetaField_SetDefaultText((int *)igMetaObject_GetFieldAt(meta, base), (int)text_Intrinsic);
    igStringMetaField_SetDefaultText((int *)igMetaObject_GetFieldAt(meta, base + 1), (int)text_default_2);
    field = (igMetaField *)igMetaObject_GetFieldAt(meta, base + 3);
    igStringMetaField_SetDefaultText((int *)field, (int)DAT_004f7910);
    field->_persistent = 0;
    igMetaObject_NameFields(meta, (const char **)g_igExternalDirEntry_fieldTable, (igMetaField ***)DAT_004c0cf0, DAT_004c0d00, base);
}

