igMetaObject *g_beMovie_metaObject;
igMetaField *g_beMovie_movieMetaField;
igMetaField *g_beMovie_playingNameMetaField;

void beMovie_CreateInstance(int arg0) {
    beMovie_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588788, arg0);
}

igMetaObject *beMovie_GetOrCreateMetaObject(void) {
    if (g_beMovie_metaObject == 0) {
        g_beMovie_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMovie_metaObject;
}

igMetaObject *beMovie_GetMetaObject(void)
{
    igMetaObject *g = g_beMovie_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beMovie_EnsureRegistered();
    return g_beMovie_metaObject;
}

int beMovie_GetVTable(void) {
    struct Obj_34f010 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &g_beMovie_vtable[0];
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beMovie_vtable[0];
    igStringRef_Destruct(&obj.w9, -1);
    FUN_003369f0(&obj.w8, -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return t;
}

void beMovie_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMovie_Register);
}

static igMetaObjectCallback g_beMovie_callbackList[] = { igMovieManager_EnsureRegistered, 0 };

void *beMovie_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMovie_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMovie_GetMetaObjectFunction,
        "beMovie",
        0x28, /* instance size */
        beMovie_GetVTable,
        beMovie_InitFields,
        0, /* extra callback item */
        g_beMovie_callbackList /* callback list */
    );
}

void beMovie_GetMetaObjectFunction(void)
{
    beMovie_GetMetaObject();
}

static FieldFactory g_beMovie_ctorTable[] = {
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beMovie_fieldTable[] = {
    "_movie",
    "_playingName",
};
static igMetaField **g_beMovie_fieldHandles[] = {
    &g_beMovie_movieMetaField,
    &g_beMovie_playingNameMetaField,
};
static int g_beMovie_fieldOffsets[] = {
    32,
    36,
};

void beMovie_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMovie_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beMovie_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igMovieManager_GetOrCreateMetaObject();
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 0);
    igMetaObject_NameFields(temp_s0, g_beMovie_fieldTable, g_beMovie_fieldHandles, g_beMovie_fieldOffsets, temp_s2);
}

