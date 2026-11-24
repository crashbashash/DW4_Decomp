igMetaObject *g_beModelCtrlSCSound_metaObject;
igMetaField *g_beModelCtrlSCSound_sndNameMetaField;
igMetaField *g_beModelCtrlSCSound_sndHandleMetaField;

beModelCtrlSCSound *beModelCtrlSCSound_Create(int allocator) {
    beModelCtrlSCSound_EnsureRegistered();
    return (beModelCtrlSCSound *)igMetaObject_CreateInstance(g_beModelCtrlSCSound_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beModelCtrlSCSound_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlSCSound_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beModelCtrlSCSound_EnsureRegistered();
done:
    return g_beModelCtrlSCSound_metaObject;
}

int beModelCtrlSCSound_GetVTable(void) {
    beModelCtrlSCSound obj;
    int vtable;
    char **sndNameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlSCSound_vtable[0];
    sndNameSlot = (char **)&obj._sndName;
    *sndNameSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlSCSound_vtable[0];
    igStringRef_Release(sndNameSlot);
    return vtable;
}

void beModelCtrlSCSound_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCSound_Register);
}

CallbackArray *beModelCtrlSCSound_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlSCSound_metaObject,
        Gap::Bec::beModelCtrlSubComBase::arkRegisterInternal,
        Gap::Bec::beModelCtrlSubComBase::getClassMeta,
        beModelCtrlSCSound_GetMetaObjectFunction,
        "beModelCtrlSCSound",
        0x20, /* instance size */
        beModelCtrlSCSound_GetVTable,
        beModelCtrlSCSound_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCSound_GetMetaObjectFunction(void)
{
    beModelCtrlSCSound_GetMetaObject();
}

static FieldFactory g_beModelCtrlSCSound_ctorTable[] = {
    igStringMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_beModelCtrlSCSound_fieldTable[] = {
    "_sndName",
    "_sndHandle",
};
static igMetaField **g_beModelCtrlSCSound_fieldHandles[] = {
    &g_beModelCtrlSCSound_sndNameMetaField,
    &g_beModelCtrlSCSound_sndHandleMetaField,
};
static int g_beModelCtrlSCSound_fieldOffsets[] = {
    20,
    24,
};

void beModelCtrlSCSound_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlSCSound_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlSCSound_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beModelCtrlSCSound_fieldTable, g_beModelCtrlSCSound_fieldHandles, g_beModelCtrlSCSound_fieldOffsets, base);
}

