igMetaObject *g_beMovie_metaObject;
igMetaField *g_beMovie_movieMetaField;
igMetaField *g_beMovie_playingNameMetaField;

void beMovie_CreateInstance(int allocator) {
    beMovie_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588788, allocator);
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
    beMovie obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beMovie_vtable[0];
    obj._movie = 0;
    obj._playingName = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beMovie_vtable[0];
    igStringRef_Destruct(&obj._playingName, -1);
    igSmartPointer_igMovieManager_Destruct(&obj._movie, -1);
    beBaseInfoManager_Destroy((O_33f5e0 *)&obj, (short)0);
    return vtable;
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
    int base;
    void *movie;
    void *meta;

    meta = (void *)g_beMovie_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMovie_ctorTable, 2);
    movie = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)movie)->_metaObject = igMovieManager_GetOrCreateMetaObject();
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 1), 0);
    igMetaObject_NameFields(meta, g_beMovie_fieldTable, g_beMovie_fieldHandles, g_beMovie_fieldOffsets, base);
}

