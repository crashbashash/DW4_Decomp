igMetaObject *g_beFileListInfo_metaObject;
igMetaField *g_beFileListInfo_sectionMetaField;
igMetaField *g_beFileListInfo_fnamesMetaField;

void *beFileListInfo_GetMetaObject(void) {
    unsigned char b;
    if (g_beFileListInfo_metaObject != 0) {
        b = (g_beFileListInfo_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beFileListInfo_EnsureRegistered();
done:
    return g_beFileListInfo_metaObject;
}

int beFileListInfo_GetVTable(void) {
    beFileListInfo obj;
    int vtable;
    char *sectionSlot;
    char *fnamesSlot;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beFileListInfo_vtable[0];
    sectionSlot = (char *)&obj._section;
    *(int *)sectionSlot = 0;
    fnamesSlot = (char *)&obj._fnames;
    *(int *)fnamesSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beFileListInfo_vtable[0];
    igSmartPointer_igNamedObjectList_Destruct(fnamesSlot, -1);
    igStringRef_Destruct(sectionSlot, -1);
    igInfo_Destroy(&obj, 0);
    return vtable;
}

void beFileListInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFileListInfo_Register);
}

static igMetaObjectCallback g_beFileListInfo_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void *beFileListInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFileListInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beFileListInfo_GetMetaObjectFunction,
        "beFileListInfo",
        0x1c, /* instance size */
        beFileListInfo_GetVTable,
        beFileListInfo_InitFields,
        0, /* extra callback item */
        g_beFileListInfo_callbackList /* callback list */
    );
}

void beFileListInfo_GetMetaObjectFunction(void)
{
    beFileListInfo_GetMetaObject();
}

static FieldFactory g_beFileListInfo_ctorTable[] = {
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beFileListInfo_fieldTable[] = {
    "_section",
    "_fnames",
};
static igMetaField **g_beFileListInfo_fieldHandles[] = {
    &g_beFileListInfo_sectionMetaField,
    &g_beFileListInfo_fnamesMetaField,
};
static int g_beFileListInfo_fieldOffsets[] = {
    20,
    24,
};

void beFileListInfo_InitFields(void) {
    int base;
    void *fnames;
    void *meta;

    meta = (void *)g_beFileListInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beFileListInfo_ctorTable, 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), 0);
    fnames = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)fnames)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beFileListInfo_fieldTable, g_beFileListInfo_fieldHandles, g_beFileListInfo_fieldOffsets, base);
}

