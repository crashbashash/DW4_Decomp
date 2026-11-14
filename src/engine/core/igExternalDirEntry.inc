igMetaObject *igExternalDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igExternalDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igExternalDirEntry_EnsureRegistered();
    return g_igExternalDirEntry_metaObject[0];
}

int igExternalDirEntry_GetVTable(void) {
    igExternalDirEntry entry;
    int vtable;
    char *o;
    int *text;
    int *header;
    int references;
    igObject_InitHeader((igObject *)&entry);
    entry._name = 0;
    entry._vtable = (int)&g_igExternalDirEntry_vtable[0];
    entry._directoryName = 0;
    entry._entryName = 0;
    entry._externalFilePath = 0;
    vtable = *(int *)((char *)&entry + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    entry._vtable = (int)&g_igExternalDirEntry_vtable[0];
    StringRef_Destruct_00130720(&entry._externalFilePath, -1);
    StringRef_Destruct_00130720(&entry._entryName, -1);
    StringRef_Destruct_00130720(&entry._directoryName, -1);
    FUN_0014f4e0(&entry, 0);
    return vtable;
}

void igExternalDirEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igExternalDirEntry_Register);
}

void igExternalDirEntry_Register(void) {
    CoreLibrary_MarkRegistered();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0,
        g_igExternalDirEntry_metaObject,
        (igMetaObjectRegisterFunction)igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        igExternalDirEntry_GetMetaObjectFunction,
        igExternalDirEntry_className,
        0x2C,
        igExternalDirEntry_GetVTable,
        igExternalDirEntry_InitFields,
        0,
        (igMetaObjectCallback *)g_igExternalDirEntry_callbackList
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
    igMetaField_Configure(field, (const char *)text_ref, g_igExternalDirEntry_refDescriptorCell, 0x18, meta);
    ((igObjectRefMetaField *)field)->_metaObject = (int)g_igObject_metaObject[0];
    field->_persistent = 0;
    field->_externalEnumStorage = (int)g_igExternalDirEntry_refDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    igStringMetaField_SetDefaultText((int *)igMetaObject_GetFieldAt(meta, base), (int)text_Intrinsic);
    igStringMetaField_SetDefaultText((int *)igMetaObject_GetFieldAt(meta, base + 1), (int)text_default_2);
    field = (igMetaField *)igMetaObject_GetFieldAt(meta, base + 3);
    igStringMetaField_SetDefaultText((int *)field, (int)emptyString_4);
    field->_persistent = 0;
    igMetaObject_NameFields(meta, (const char **)g_igExternalDirEntry_fieldTable, (igMetaField ***)g_igExternalDirEntry_fieldDescriptors, g_igExternalDirEntry_fieldOffsets, base);
}

