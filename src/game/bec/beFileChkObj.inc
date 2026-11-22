igMetaObject *g_beFileChkObj_metaObject;
igMetaField *g_beFileChkObj_fdMetaField;

beFileChkObj *beFileChkObj_Create(int allocator) {
    beFileChkObj_EnsureRegistered();
    return (beFileChkObj *)igMetaObject_CreateInstance(g_beFileChkObj_metaObject, (igMemoryPoolView *)allocator);
}

void *beFileChkObj_GetMetaObject(void) {
    igMetaObject *g = g_beFileChkObj_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beFileChkObj_EnsureRegistered();
    }
    return g_beFileChkObj_metaObject;
}

int beFileChkObj_GetVTable(void) {
    beFileChkObj obj;
    int vtable;
    igObject **fdSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beFileChkObj_vtable[0];
    fdSlot = (igObject **)&obj._fd;
    *fdSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beFileChkObj_vtable[0];
    igObjectRef_Release(fdSlot);
    return vtable;
}

void beFileChkObj_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFileChkObj_Register);
}

static igMetaObjectCallback g_beFileChkObj_callbackList[] = { Gap::Core::igFile::arkRegister, 0 };

CallbackArray *beFileChkObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFileChkObj_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beFileChkObj_GetMetaObjectFunction,
        "beFileChkObj",
        0xc, /* instance size */
        beFileChkObj_GetVTable,
        beFileChkObj_InitFields,
        0, /* extra callback item */
        g_beFileChkObj_callbackList /* callback list */
    );
}

void beFileChkObj_GetMetaObjectFunction(void)
{
    beFileChkObj_GetMetaObject();
}

static FieldFactory g_beFileChkObj_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beFileChkObj_fieldTable[] = {
    "_fd",
};
static igMetaField **g_beFileChkObj_fieldHandles[] = {
    &g_beFileChkObj_fdMetaField,
};
static int g_beFileChkObj_fieldOffsets[] = {
    8,
};

void beFileChkObj_InitFields(void) {
    int base;
    void *fd;
    igMetaObject *meta;

    meta = g_beFileChkObj_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beFileChkObj_ctorTable, 1);
    fd = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)fd)->_metaObject = (int)Gap::Core::igFile::getClassTypeLazy();
    ((igRefMetaField *)fd)->_construct = 1;
    igMetaObject_NameFields(meta, g_beFileChkObj_fieldTable, g_beFileChkObj_fieldHandles, g_beFileChkObj_fieldOffsets, base);
}

