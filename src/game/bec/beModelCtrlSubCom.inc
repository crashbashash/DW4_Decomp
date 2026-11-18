igMetaObject *g_beModelCtrlSubCom_metaObject;
igMetaField *g_beModelCtrlSubCom_comListMetaField;

igMetaObject *beModelCtrlSubCom_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlSubCom_metaObject == 0) {
        g_beModelCtrlSubCom_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beModelCtrlSubCom_metaObject;
}

igMetaObject *beModelCtrlSubCom_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlSubCom_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beModelCtrlSubCom_EnsureRegistered();
    return g_beModelCtrlSubCom_metaObject;
}

int beModelCtrlSubCom_GetVTable(void) {
    beModelCtrlSubCom obj;
    int vtable;
    igObject **comListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlSubCom_vtable[0];
    comListSlot = (igObject **)&obj._comList;
    *comListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlSubCom_vtable[0];
    igObjectRef_Release(comListSlot);
    return vtable;
}

void beModelCtrlSubCom_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSubCom_Register);
}

static igMetaObjectCallback g_beModelCtrlSubCom_callbackList[] = { igObjectList_EnsureRegistered, 0 };

CallbackArray *beModelCtrlSubCom_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlSubCom_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlSubCom_GetMetaObjectFunction,
        "beModelCtrlSubCom",
        0xc, /* instance size */
        beModelCtrlSubCom_GetVTable,
        beModelCtrlSubCom_InitFields,
        0, /* extra callback item */
        g_beModelCtrlSubCom_callbackList /* callback list */
    );
}

void beModelCtrlSubCom_GetMetaObjectFunction(void)
{
    beModelCtrlSubCom_GetMetaObject();
}

static FieldFactory g_beModelCtrlSubCom_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlSubCom_fieldTable[] = {
    "_comList",
};
static igMetaField **g_beModelCtrlSubCom_fieldHandles[] = {
    &g_beModelCtrlSubCom_comListMetaField,
};
static int g_beModelCtrlSubCom_fieldOffsets[] = {
    8,
};

void beModelCtrlSubCom_InitFields(void) {
    int base;
    void *comList;
    igMetaObject *meta;

    meta = g_beModelCtrlSubCom_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlSubCom_ctorTable, 1);
    comList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)comList)->_metaObject = (int)igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)comList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beModelCtrlSubCom_fieldTable, g_beModelCtrlSubCom_fieldHandles, g_beModelCtrlSubCom_fieldOffsets, base);
}

