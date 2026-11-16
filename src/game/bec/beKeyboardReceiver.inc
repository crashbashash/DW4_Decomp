igMetaObject *g_beKeyboardReceiver_metaObject;
igMetaField *g_beKeyboardReceiver_keyboardMetaField;

igMetaObject *beKeyboardReceiver_GetOrCreateMetaObject(void) {
    if (g_beKeyboardReceiver_metaObject == 0) {
        g_beKeyboardReceiver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beKeyboardReceiver_metaObject;
}

igMetaObject *beKeyboardReceiver_GetMetaObject(void) {
    igMetaObject *g = g_beKeyboardReceiver_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beKeyboardReceiver_EnsureRegistered();
    return g_beKeyboardReceiver_metaObject;
}

int beKeyboardReceiver_GetVTable(void) {
    struct W_35d110 o;
    int r;
    igObject *p;

    igObject_InitHeader(&o);
    o.vt = g_beKeyboardReceiver_vtable;
    *(int *)((char *)&o + 8) = 0;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beKeyboardReceiver_vtable;
    if (&*(int *)((char *)&o + 8) != 0) { p = *(igObject **)((char *)&o + 8); if (p != 0) { p->_refCount = (int)p->_refCount - 1; if (((unsigned long long) ((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(p); } }
    return r;
}

void beKeyboardReceiver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beKeyboardReceiver_Register);
}

static igMetaObjectCallback g_beKeyboardReceiver_callbackList[] = { igBoolList_EnsureRegistered, 0 };

void *beKeyboardReceiver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beKeyboardReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        beKeyboardReceiver_GetMetaObjectFunction,
        "beKeyboardReceiver",
        0xc, /* instance size */
        beKeyboardReceiver_GetVTable,
        beKeyboardReceiver_InitFields,
        0, /* extra callback item */
        g_beKeyboardReceiver_callbackList /* callback list */
    );
}

void beKeyboardReceiver_GetMetaObjectFunction(void)
{
    beKeyboardReceiver_GetMetaObject();
}

static FieldFactory g_beKeyboardReceiver_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beKeyboardReceiver_fieldTable[] = {
    "_keyboard",
};
static igMetaField **g_beKeyboardReceiver_fieldHandles[] = {
    &g_beKeyboardReceiver_keyboardMetaField,
};
static int g_beKeyboardReceiver_fieldOffsets[] = {
    8,
};

void beKeyboardReceiver_InitFields(void) {
    int base;
    void *keyboard;
    void *meta;

    meta = (void *)g_beKeyboardReceiver_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beKeyboardReceiver_ctorTable, 1);
    keyboard = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)keyboard)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)keyboard)->_construct = 1;
    igMetaObject_NameFields(meta, g_beKeyboardReceiver_fieldTable, g_beKeyboardReceiver_fieldHandles, g_beKeyboardReceiver_fieldOffsets, base);
}

