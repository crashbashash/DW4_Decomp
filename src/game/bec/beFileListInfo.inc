igMetaObject *g_beFileListInfo_metaObject;
igMetaField *g_beFileListInfo_sectionMetaField;
igMetaField *g_beFileListInfo_fnamesMetaField;

void *FUN_00362c00(void) {
    unsigned char b;
    if (g_beFileListInfo_metaObject != 0) {
        b = (*(int *)((char *)(g_beFileListInfo_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00362ce0();
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
    u.vt = (int)&DAT_00535870[0];
    p2 = &u.b[20];
    *(int *)p2 = 0;
    p1 = &u.b[24];
    *(int *)p1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00535870[0];
    FUN_00199450(p1, -1);
    igStringRef_Destruct(p2, -1);
    igInfo_Destroy(u.b, 0);
    return temp_s1;
}

void FUN_00362ce0(void)
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
        beFileListInfo_GetMetaObject,
        "beFileListInfo",
        0x1c, /* instance size */
        beFileListInfo_GetVTable,
        beFileListInfo_InitFields,
        0, /* extra callback item */
        g_beFileListInfo_callbackList /* callback list */
    );
}

void beFileListInfo_GetMetaObject(void)
{
    FUN_00362c00();
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beFileListInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beFileListInfo_ctorTable, 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2), 0);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beFileListInfo_fieldTable, g_beFileListInfo_fieldHandles, g_beFileListInfo_fieldOffsets, temp_s2);
}

