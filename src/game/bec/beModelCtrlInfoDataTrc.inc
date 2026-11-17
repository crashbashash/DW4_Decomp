igMetaObject *g_beModelCtrlInfoDataTrc_metaObject;
int g_beModelCtrlInfoDataTrc_nameStorage;
igMetaField *g_beModelCtrlInfoDataTrc_recorderNodeMetaField;

igMetaObject *beModelCtrlInfoDataTrc_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoDataTrc_metaObject == 0) {
        g_beModelCtrlInfoDataTrc_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beModelCtrlInfoDataTrc_metaObject;
}

void *beModelCtrlInfoDataTrc_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoDataTrc_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoDataTrc_EnsureRegistered();
    }
    return g_beModelCtrlInfoDataTrc_metaObject;
}

int beModelCtrlInfoDataTrc_GetVTable(void) {
    beModelCtrlInfoDataTrc obj;
    int vtable;
    igObject **recorderNodeSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beModelCtrlInfoDataTrc_vtable[0];
    recorderNodeSlot = (igObject **)&obj._recorderNode;
    *recorderNodeSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beModelCtrlInfoDataTrc_vtable[0];
    igObjectRef_Release(recorderNodeSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlInfoDataTrc_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataTrc_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoDataTrc_callbackList[] = { igTransformRecorder_EnsureRegistered, 0 };

CallbackArray *beModelCtrlInfoDataTrc_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataTrc_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataTrc_GetMetaObjectFunction,
        "beModelCtrlInfoDataTrc",
        0x14, /* instance size */
        beModelCtrlInfoDataTrc_GetVTable,
        beModelCtrlInfoDataTrc_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataTrc_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataTrc_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataTrc_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataTrc_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoDataTrc_fieldTable[] = {
    "_recorderNode",
};
static igMetaField **g_beModelCtrlInfoDataTrc_fieldHandles[] = {
    &g_beModelCtrlInfoDataTrc_recorderNodeMetaField,
};
static int g_beModelCtrlInfoDataTrc_fieldOffsets[] = {
    16,
};

void beModelCtrlInfoDataTrc_InitFields(void) {
    int base;
    int index;
    void **found;
    void *recorderNode;
    igMetaObject *meta;
    igStringMetaField *clone;

    meta = (igMetaObject *)(((void * *)&g_beModelCtrlInfoDataTrc_metaObject)[0]);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoDataTrc_ctorTable, 1);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igStringMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    igStringMetaField_SetDefaultText((igMetaField *)clone, "TRC");
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoDataTrc_nameStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    recorderNode = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)recorderNode)->_metaObject = (int)igTransformRecorder_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beModelCtrlInfoDataTrc_fieldTable, g_beModelCtrlInfoDataTrc_fieldHandles, g_beModelCtrlInfoDataTrc_fieldOffsets, base);
}

