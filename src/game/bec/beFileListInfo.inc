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
    union U_362c50 u;
    int temp_s1;
    char *p2;
    char *p1;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&g_beFileListInfo_vtable[0];
    p2 = &u.b[20];
    *(int *)p2 = 0;
    p1 = &u.b[24];
    *(int *)p1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beFileListInfo_vtable[0];
    FUN_00199450(p1, -1);
    igStringRef_Destruct(p2, -1);
    igInfo_Destroy(u.b, 0);
    return temp_s1;
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

