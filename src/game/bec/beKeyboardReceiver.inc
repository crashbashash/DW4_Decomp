igMetaObject *g_beKeyboardReceiver_metaObject;
igMetaField *g_beKeyboardReceiver_keyboardMetaField;

igMetaObject *beKeyboardReceiver_GetOrCreateMetaObject(void) {
    if (g_beKeyboardReceiver_metaObject == 0) {
        g_beKeyboardReceiver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    beKeyboardReceiver obj;
    int vtable;
    igObject **keyboardSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beKeyboardReceiver_vtable[0];
    keyboardSlot = (igObject **)&obj._keyboard;
    *keyboardSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beKeyboardReceiver_vtable[0];
    igObjectRef_Release(keyboardSlot);
    return vtable;
}

void beKeyboardReceiver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beKeyboardReceiver_Register);
}

static igMetaObjectCallback g_beKeyboardReceiver_callbackList[] = { Gap::Core::igBoolList::arkRegister, 0 };

CallbackArray *beKeyboardReceiver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beKeyboardReceiver_metaObject,
        Gap::Gui::igEventReceiver::arkRegisterInternal,
        Gap::Gui::igEventReceiver::getClassMeta,
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
    igMetaObject *meta;

    meta = g_beKeyboardReceiver_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beKeyboardReceiver_ctorTable, 1);
    keyboard = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)keyboard)->_metaObject = (int)Gap::Core::igBoolList::getClassTypeLazy();
    ((igRefMetaField *)keyboard)->_construct = 1;
    igMetaObject_NameFields(meta, g_beKeyboardReceiver_fieldTable, g_beKeyboardReceiver_fieldHandles, g_beKeyboardReceiver_fieldOffsets, base);
}

