igMetaObject *g_igMessageInterface_metaObject;
igMetaField *g_igMessageInterface_messagesMetaField;

igMetaObject *igMessageInterface_GetOrCreateMetaObject(void) {
    if (g_igMessageInterface_metaObject == 0) {
        g_igMessageInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMessageInterface_metaObject;
}

igMetaObject *igMessageInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226200();
    return g_igMessageInterface_metaObject;
}

int igMessageInterface_GetVTable(void) {
    struct W o;
    int r;
    struct Ref *p;
    igObject_InitHeader((igObject *)&o);
    o.vt = g_igMessageInterface_vtable;
    *(int *)((char *)&o + 32) = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = g_igMessageInterface_vtable;
    if (&*(int *)((char *)&o + 32) != 0) { p = *(struct Ref **)((char *)&o + 32); if (p != 0) { p->u.w = p->u.w - 1; if (p->u.b.cnt == 0) igObject_Destroy((igObject *)p); } }
    return r;
}

void FUN_00226200(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igMessageInterface_Register);
}

static igMetaObjectCallback g_igMessageInterface_callbackList[] = { FUN_00226420, 0 };

CallbackArray *igMessageInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageInterface_metaObject,
        (igMetaObjectRegisterFunction)igInterface_Register,
        (igMetaObjectGetFunction)igInterface_GetPublishedMetaObject,
        igMessageInterface_GetMetaObjectFunction,
        "igMessageInterface",
        0x24, /* instance size */
        igMessageInterface_GetVTable,
        &igMessageInterface_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igMessageInterface_callbackList /* callback list */
    );
}

void igMessageInterface_GetMetaObjectFunction(void) {
    igMessageInterface_GetMetaObject();
}

static FieldFactory g_igMessageInterface_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igMessageInterface_fieldTable[] = {
    "_messages",
};
static igMetaField **g_igMessageInterface_fieldHandles[] = {
    &g_igMessageInterface_messagesMetaField,
};
static int g_igMessageInterface_fieldOffsets[] = {
    32,
};

void igMessageInterface_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igMessageInterface_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMessageInterface_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igMessageList_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields(meta, g_igMessageInterface_fieldTable, g_igMessageInterface_fieldHandles, g_igMessageInterface_fieldOffsets, base);
}

