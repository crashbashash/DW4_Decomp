igMetaObject *g_beMessengerGroup_metaObject;
igMetaField *g_beMessengerGroup_infoNameListMetaField;
igMetaField *g_beMessengerGroup_ramNoListMetaField;
igMetaField *g_beMessengerGroup_ramListMetaField;

beMessengerGroup *beMessengerGroup_Create(int allocator) {
    beMessengerGroup_EnsureRegistered();
    return (beMessengerGroup *)igMetaObject_CreateInstance(g_beMessengerGroup_metaObject, (igMemoryPoolView *)allocator);
}

void *beMessengerGroup_GetMetaObject(void) {
    igMetaObject *g = g_beMessengerGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessengerGroup_EnsureRegistered();
    }
    return g_beMessengerGroup_metaObject;
}

int beMessengerGroup_GetVTable(void) {
    beMessengerGroup obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beMessengerGroup_vtable[0];
    obj._infoNameList = 0;
    obj._ramNoList = 0;
    obj._ramList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMessengerGroup_vtable[0];
    igSmartPointer_beBaseInfoRamList_Destruct((igSmartPointer<igObject> *)&obj._ramList, (short)(-1));
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._ramNoList, -1);
    igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&obj._infoNameList, -1);
    igNamedObject_Destroy((igNamedObject *)&obj, 0);
    return vtable;
}

void beMessengerGroup_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerGroup_Register);}

static igMetaObjectCallback g_beMessengerGroup_callbackList[] = { igStringRefList_EnsureRegistered, Gap::Core::igIntList::arkRegister, beBaseInfoRamList_EnsureRegistered, 0 };

CallbackArray *beMessengerGroup_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerGroup_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMessengerGroup_GetMetaObjectFunction,
        "beMessengerGroup",
        0x18, /* instance size */
        beMessengerGroup_GetVTable,
        beMessengerGroup_InitFields,
        0, /* extra callback item */
        g_beMessengerGroup_callbackList /* callback list */
    );
}

void beMessengerGroup_GetMetaObjectFunction(void)
{
    beMessengerGroup_GetMetaObject();
}

static FieldFactory g_beMessengerGroup_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMessengerGroup_fieldTable[] = {
    "_infoNameList",
    "_ramNoList",
    "_ramList",
};
static igMetaField **g_beMessengerGroup_fieldHandles[] = {
    &g_beMessengerGroup_infoNameListMetaField,
    &g_beMessengerGroup_ramNoListMetaField,
    &g_beMessengerGroup_ramListMetaField,
};
static int g_beMessengerGroup_fieldOffsets[] = {
    12,
    16,
    20,
};

void beMessengerGroup_InitFields(void) {
    int base;
    void *ramList;
    void *ramNoList;
    void *infoNameList;
    igMetaObject *meta;

    meta = g_beMessengerGroup_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMessengerGroup_ctorTable, 3);
    infoNameList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)infoNameList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)infoNameList)->_construct = 1;
    ramNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)ramNoList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)ramNoList)->_construct = 1;
    ramList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)ramList)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)ramList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMessengerGroup_fieldTable, g_beMessengerGroup_fieldHandles, g_beMessengerGroup_fieldOffsets, base);
}

