igMetaObject *g_beSvStartApi_metaObject;
int g_beSvStartApi_orderTypeStorage;

beSvStartApi *beSvStartApi_Create(int allocator) {
    beSvStartApi_EnsureRegistered();
    return (beSvStartApi *)igMetaObject_CreateInstance(g_beSvStartApi_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beSvStartApi_GetMetaObject(void)
{
    igMetaObject *g = g_beSvStartApi_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beSvStartApi_EnsureRegistered();
    return g_beSvStartApi_metaObject;
}

int beSvStartApi_GetVTable(void) {
    beSvStartApi obj;
    int vtable;
    igObject **iconWorkSlot;
    igObject **mountWorkSlot;
    igObject **imageWorkSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    imageWorkSlot = (igObject **)&obj._imageWork;
    *imageWorkSlot = 0;
    mountWorkSlot = (igObject **)&obj._mountWork;
    *mountWorkSlot = 0;
    iconWorkSlot = (igObject **)&obj._iconWork;
    *iconWorkSlot = 0;
    obj._vtable = (int)&g_beSvStartApi_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    igObjectRef_Release(iconWorkSlot);
    igObjectRef_Release(mountWorkSlot);
    igObjectRef_Release(imageWorkSlot);
    return vtable;
}

void beSvStartApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvStartApi_Register);
}

CallbackArray *beSvStartApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvStartApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvStartApi_GetMetaObjectFunction,
        "beSvStartApi",
        0x40, /* instance size */
        beSvStartApi_GetVTable,
        beSvStartApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvStartApi_GetMetaObjectFunction(void)
{
    beSvStartApi_GetMetaObject();
}

void beSvStartApi_InitFields(void) {
    int index;
    igMetaObject *meta;
    void **found;
    igIntMetaField *clone;

    meta = g_beSvStartApi_metaObject;
    found = (void **)(igMetaObject_FindFieldByName(meta, "_orderType"));
    index = ((Gap::Core::__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields))->find((Gap::Core::igObject *)found);
    clone = (igIntMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    ((Gap::Core::igIntMetaField *)clone)->setDefault(0xA);
    clone->_externalEnumStorage = (int)(&g_beSvStartApi_orderTypeStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
}

