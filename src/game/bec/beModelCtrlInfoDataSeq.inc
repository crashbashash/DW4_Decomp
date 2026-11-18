igMetaObject *g_beModelCtrlInfoDataSeq_metaObject;
int g_beModelCtrlInfoDataSeq_nameStorage;
igMetaField *g_beModelCtrlInfoDataSeq_dataListMetaField;

void *beModelCtrlInfoDataSeq_GetMetaObject(void) {
    bool ok;
    if (g_beModelCtrlInfoDataSeq_metaObject == 0) goto make;
    ok = !!(g_beModelCtrlInfoDataSeq_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beModelCtrlInfoDataSeq_EnsureRegistered();
done:;
    return g_beModelCtrlInfoDataSeq_metaObject;
}

int beModelCtrlInfoDataSeq_GetVTable(void) {
    beModelCtrlInfoDataSeq obj;
    int vtable;
    igObject **dataListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beModelCtrlInfoDataSeq_vtable[0];
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlInfoDataSeq_vtable[0];
    igObjectRef_Release(dataListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlInfoDataSeq_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataSeq_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoDataSeq_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

CallbackArray *beModelCtrlInfoDataSeq_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataSeq_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataSeq_GetMetaObjectFunction,
        "beModelCtrlInfoDataSeq",
        0x14, /* instance size */
        beModelCtrlInfoDataSeq_GetVTable,
        beModelCtrlInfoDataSeq_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataSeq_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataSeq_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataSeq_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataSeq_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoDataSeq_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beModelCtrlInfoDataSeq_fieldHandles[] = {
    &g_beModelCtrlInfoDataSeq_dataListMetaField,
};
static int g_beModelCtrlInfoDataSeq_fieldOffsets[] = {
    16,
};

void beModelCtrlInfoDataSeq_InitFields(void) {
    int base;
    int index;
    void **found;
    void *dataList;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beModelCtrlInfoDataSeq_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beModelCtrlInfoDataSeq_ctorTable, 1);
    found = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igStringMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    igStringMetaField_SetDefaultText((igMetaField *)clone, "SEQ");
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoDataSeq_nameStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    dataList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beModelCtrlInfoDataSeq_fieldTable, g_beModelCtrlInfoDataSeq_fieldHandles, g_beModelCtrlInfoDataSeq_fieldOffsets, base);
}

