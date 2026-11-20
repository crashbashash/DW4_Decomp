igMetaObject *g_beSvPlatDataXbox_metaObject;
int g_beSvPlatDataXbox_connectMaxStorage;
igMetaField *g_beSvPlatDataXbox_imageSizeMetaField;
igMetaField *g_beSvPlatDataXbox_imageMetaField;
igMetaField *g_beSvPlatDataXbox_saveDataSizeMetaField;
igMetaField *g_beSvPlatDataXbox_dataOffSetMetaField;

void *beSvPlatDataXbox_GetMetaObject(void) {
    igMetaObject *g = g_beSvPlatDataXbox_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvPlatDataXbox_EnsureRegistered();
    }
    return g_beSvPlatDataXbox_metaObject;
}

int beSvPlatDataXbox_GetVTable(void) {
    beSvPlatDataXbox obj;
    int vtable;
    igObject **imageSlot;
    igObject **slotListSlot;

    igObject_InitHeader(&obj);
    slotListSlot = (igObject **)&obj._slotList;
    *slotListSlot = 0;
    obj._vtable = (int)&g_beSvPlatDataXbox_vtable[0];
    imageSlot = (igObject **)&obj._image;
    *imageSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSvPlatDataXbox_vtable[0];
    igObjectRef_Release(imageSlot);
    obj._vtable = (int)&g_beSvPlatBaseData_vtable[0];
    igObjectRef_Release(slotListSlot);
    return vtable;
}

void beSvPlatDataXbox_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataXbox_Register);
}

static igMetaObjectCallback g_beSvPlatDataXbox_callbackList[] = { beXboxImage24k_EnsureRegistered, 0 };

CallbackArray *beSvPlatDataXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataXbox_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataXbox_GetMetaObjectFunction,
        "beSvPlatDataXbox",
        0x2c, /* instance size */
        beSvPlatDataXbox_GetVTable,
        beSvPlatDataXbox_InitFields,
        0, /* extra callback item */
        g_beSvPlatDataXbox_callbackList /* callback list */
    );
}

void beSvPlatDataXbox_GetMetaObjectFunction(void)
{
    beSvPlatDataXbox_GetMetaObject();
}

static FieldFactory g_beSvPlatDataXbox_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igIntArrayMetaField_Create,
};
static const char *g_beSvPlatDataXbox_fieldTable[] = {
    "_imageSize",
    "_image",
    "_saveDataSize",
    "_dataOffSet",
};
static igMetaField **g_beSvPlatDataXbox_fieldHandles[] = {
    &g_beSvPlatDataXbox_imageSizeMetaField,
    &g_beSvPlatDataXbox_imageMetaField,
    &g_beSvPlatDataXbox_saveDataSizeMetaField,
    &g_beSvPlatDataXbox_dataOffSetMetaField,
};
static int g_beSvPlatDataXbox_fieldOffsets[] = {
    32,
    36,
    40,
    24,
};

void beSvPlatDataXbox_InitFields(void) {
    int base;
    int index;
    void **found;
    void *image;
    void *dataOffSet;
    void *meta;
    igIntMetaField *clone;

    meta = (void *)g_beSvPlatDataXbox_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beSvPlatDataXbox_ctorTable, 4);
    found = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_connectMax"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igIntMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    ((Gap::Core::igIntMetaField *)clone)->setDefault(9);
    clone->_externalEnumStorage = (int)(&g_beSvPlatDataXbox_connectMaxStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    image = (igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)image)->_metaObject = (int)beXboxImage24k_GetOrCreateMetaObject();
    ((igRefMetaField *)image)->_construct = 1;
    dataOffSet = igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3);
    ((igIntArrayMetaField *)dataOffSet)->_num = 2;
    igMetaObject_NameFields((igMetaObject *)meta, g_beSvPlatDataXbox_fieldTable, g_beSvPlatDataXbox_fieldHandles, g_beSvPlatDataXbox_fieldOffsets, base);
}

