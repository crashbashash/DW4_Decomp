int FUN_002bd8f0(int arg0) {
    FUN_002bda10();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585B70), (igMemoryPoolView *)arg0);
}

igMetaObject *igObjectDirEntry_GetMetaObject(void)
{
    igMetaObject *g = g_igObjectDirEntry_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bda10();
    return g_igObjectDirEntry_metaObject[0];
}

int igObjectDirEntry_GetVTable(void) {
    igObjectDirEntry o;
    int r;

    igObject_InitHeader((igObject *)&o);
    o._name = 0;
    o._vtable = (int)&DAT_0052f040[0];
    o._typeMeta = 0;
    o._typeMetaName = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o._vtable = (int)&DAT_0052f040[0];
    StringRef_Destruct_00130720(&o._typeMetaName, -1);
    FUN_0019c840(&o._typeMeta, -1);
    FUN_0014f4e0(&o, 0);
    return r;
}

void FUN_002bda10(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igObjectDirEntry_Register);
}

void igObjectDirEntry_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igObjectDirEntry_metaObject),
        igDirEntry_Register,
        igDirEntry_GetPublishedMetaObject,
        thunk_igObjectDirEntry_GetMetaObject,
        igObjectDirEntry_className,
        0x34, /* instance size */
        igObjectDirEntry_GetVTable,
        &igObjectDirEntry_InitFields,
        0, /* extra callback item */
        g_igObjectDirEntry_callbackList /* callback list */
    );
}

void thunk_igObjectDirEntry_GetMetaObject(void) {
    igObjectDirEntry_GetMetaObject();
}

igMetaObject *FUN_002bdab0(void) {
    return g_igDirEntry_metaObject[0];
}

void igObjectDirEntry_InitFields(void) {
    igMetaObject *meta = g_igObjectDirEntry_metaObject[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    igStringMetaField *text;
    igObjectRefMetaField *ref;
    int fields;
    int index;
    igMetaObject_CreateFields(meta, (FieldFactory *)g_igObjectDirEntry_ctorTable, 6);
    ref = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base);
    ref->_metaObject = (int)FUN_002be610();
    ((igMetaField *)ref)->_persistent = 0;
    text = (igStringMetaField *)igMetaObject_GetFieldAt(meta, base + 1);
    igStringMetaField_SetDefaultText((int *)text, (int)text_NoMeta);
    text->_destruct = 1;
    ((igMetaField *)text)->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 2))->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt(meta, base + 3))->_persistent = 0;
    fields = meta->_metaFields;
    index = ObjectPointerList_FindIndex((char *)fields, (int)igMetaObject_FindFieldByName(meta, (const char *)text_ref));
    field = (igMetaField *)igObjectRefMetaField_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    igMetaField_Configure(field, (const char *)text_ref, DAT_00585b98, 0x18, meta);
    ((igObjectRefMetaField *)field)->_metaObject = (int)g_igObject_metaObject[0];
    FUN_00303460((igObjectRefMetaField *)field, 0);
    field->_persistent = 0;
    field->_externalEnumStorage = (int)DAT_00585b98;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    FUN_002ea4b0((void **)igMetaObject_GetFieldAt(meta, base + 4), -1);
    FUN_002ea4b0((void **)igMetaObject_GetFieldAt(meta, base + 5), -1);
    igMetaObject_NameFields(meta, (const char **)g_igObjectDirEntry_fieldTable, (igMetaField ***)DAT_004bfb70, DAT_004bfb90, base);
}

