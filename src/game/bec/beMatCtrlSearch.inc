igMetaObject *g_beMatCtrlSearch_metaObject;
igMetaField *g_beMatCtrlSearch_minXMetaField;
igMetaField *g_beMatCtrlSearch_maxXMetaField;
igMetaField *g_beMatCtrlSearch_matNOMetaField;
igMetaField *g_beMatCtrlSearch_parentMetaField;
igMetaField *g_beMatCtrlSearch_memberListMetaField;

igMetaObject *beMatCtrlSearch_GetOrCreateMetaObject(void) {
    if (g_beMatCtrlSearch_metaObject == 0) {
        g_beMatCtrlSearch_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMatCtrlSearch_metaObject;
}

void *beMatCtrlSearch_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrlSearch_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrlSearch_EnsureRegistered();
    }
    return g_beMatCtrlSearch_metaObject;
}

int beMatCtrlSearch_GetVTable(void) {
    beMatCtrlSearch obj;
    int vtable;
    igObject **memberListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMatCtrlSearch_vtable[0];
    memberListSlot = (igObject **)&obj._memberList;
    *memberListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMatCtrlSearch_vtable[0];
    igObjectRef_Release(memberListSlot);
    return vtable;
}

void beMatCtrlSearch_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlSearch_Register);
}

static igMetaObjectCallback g_beMatCtrlSearch_callbackList[] = { beMatCtrlSearchList_EnsureRegistered, 0 };

CallbackArray *beMatCtrlSearch_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlSearch_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beMatCtrlSearch_GetMetaObjectFunction,
        "beMatCtrlSearch",
        0x1c, /* instance size */
        beMatCtrlSearch_GetVTable,
        beMatCtrlSearch_InitFields,
        0, /* extra callback item */
        g_beMatCtrlSearch_callbackList /* callback list */
    );
}

void beMatCtrlSearch_GetMetaObjectFunction(void)
{
    beMatCtrlSearch_GetMetaObject();
}

static FieldFactory g_beMatCtrlSearch_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlSearch_fieldTable[] = {
    "_minX",
    "_maxX",
    "_matNO",
    "_parent",
    "_memberList",
};
static igMetaField **g_beMatCtrlSearch_fieldHandles[] = {
    &g_beMatCtrlSearch_minXMetaField,
    &g_beMatCtrlSearch_maxXMetaField,
    &g_beMatCtrlSearch_matNOMetaField,
    &g_beMatCtrlSearch_parentMetaField,
    &g_beMatCtrlSearch_memberListMetaField,
};
static int g_beMatCtrlSearch_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void beMatCtrlSearch_InitFields(void) {
    int base;
    void *memberList;
    void *parent;
    igMetaObject *meta;

    meta = g_beMatCtrlSearch_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMatCtrlSearch_ctorTable, 5);
    parent = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)parent)->_metaObject = (int)beMatCtrlSearch_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)parent)->_refCounted = 0;
    ((igMetaField *)parent)->_persistent = 0;
    memberList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)memberList)->_metaObject = (int)beMatCtrlSearchList_GetOrCreateMetaObject();
    ((igRefMetaField *)memberList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMatCtrlSearch_fieldTable, g_beMatCtrlSearch_fieldHandles, g_beMatCtrlSearch_fieldOffsets, base);
}

