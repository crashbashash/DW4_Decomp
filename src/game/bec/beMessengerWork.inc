igMetaObject *g_beMessengerWork_metaObject;
igMetaField *g_beMessengerWork_groupNameMetaField;
igMetaField *g_beMessengerWork_infoNameMetaField;
igMetaField *g_beMessengerWork_ramNoMetaField;
igMetaField *g_beMessengerWork_messageMetaField;
igMetaField *g_beMessengerWork_findRamNoListMetaField;
igMetaField *g_beMessengerWork_findRamListMetaField;

beMessengerWork *beMessengerWork_Create(int allocator) {
    beMessengerWork_EnsureRegistered();
    return (beMessengerWork *)igMetaObject_CreateInstance(g_beMessengerWork_metaObject, (igMemoryPoolView *)allocator);
}

void *beMessengerWork_GetMetaObject(void) {
    igMetaObject *g = g_beMessengerWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessengerWork_EnsureRegistered();
    }
    return g_beMessengerWork_metaObject;
}

int beMessengerWork_GetVTable(void) {
    beMessengerWork obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMessengerWork_vtable[0];
    obj._groupName = 0;
    obj._infoName = 0;
    obj._message = 0;
    obj._findRamNoList = 0;
    obj._findRamList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMessengerWork_vtable[0];
    igSmartPointer_beBaseInfoRamList_Destruct((igSmartPointer<igObject> *)&obj._findRamList, (short)(-1));
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._findRamNoList, -1);
    igStringRef_Destruct((igStringRef *)&obj._message, -1);
    igStringRef_Destruct((igStringRef *)&obj._infoName, -1);
    igStringRef_Destruct((igStringRef *)&obj._groupName, -1);
    return vtable;
}

void beMessengerWork_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerWork_Register);}

static igMetaObjectCallback g_beMessengerWork_callbackList[] = { igIntList_EnsureRegistered, beBaseInfoRamList_EnsureRegistered, 0 };

CallbackArray *beMessengerWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerWork_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerWork_GetMetaObjectFunction,
        "beMessengerWork",
        0x20, /* instance size */
        beMessengerWork_GetVTable,
        beMessengerWork_InitFields,
        0, /* extra callback item */
        g_beMessengerWork_callbackList /* callback list */
    );
}

void beMessengerWork_GetMetaObjectFunction(void)
{
    beMessengerWork_GetMetaObject();
}

static FieldFactory g_beMessengerWork_ctorTable[] = {
    igStringMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMessengerWork_fieldTable[] = {
    "_groupName",
    "_infoName",
    "_ramNo",
    "_message",
    "_findRamNoList",
    "_findRamList",
};
static igMetaField **g_beMessengerWork_fieldHandles[] = {
    &g_beMessengerWork_groupNameMetaField,
    &g_beMessengerWork_infoNameMetaField,
    &g_beMessengerWork_ramNoMetaField,
    &g_beMessengerWork_messageMetaField,
    &g_beMessengerWork_findRamNoListMetaField,
    &g_beMessengerWork_findRamListMetaField,
};
static int g_beMessengerWork_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void beMessengerWork_InitFields(void) {
    int base;
    void *findRamList;
    void *findRamNoList;
    igMetaObject *meta;

    meta = g_beMessengerWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMessengerWork_ctorTable, 6);
    findRamNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)findRamNoList)->_metaObject = (int)igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)findRamNoList)->_construct = 1;
    findRamList = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)findRamList)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)findRamList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMessengerWork_fieldTable, g_beMessengerWork_fieldHandles, g_beMessengerWork_fieldOffsets, base);
}

