igMetaObject *g_beSvEndApi_metaObject;
int g_beSvEndApi_orderTypeStorage;

beSvEndApi *beSvEndApi_Create(int allocator) {
    beSvEndApi_EnsureRegistered();
    return (beSvEndApi *)igMetaObject_CreateInstance(g_beSvEndApi_metaObject, (igMemoryPoolView *)allocator);
}

void *beSvEndApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvEndApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvEndApi_EnsureRegistered();
    }
    return g_beSvEndApi_metaObject;
}

int beSvEndApi_GetVTable(void) {
    beSvEndApi obj;
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
    obj._vtable = (int)&g_beSvEndApi_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    igObjectRef_Release(iconWorkSlot);
    igObjectRef_Release(mountWorkSlot);
    igObjectRef_Release(imageWorkSlot);
    return vtable;
}

void beSvEndApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvEndApi_Register);
}

CallbackArray *beSvEndApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvEndApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvEndApi_GetMetaObjectFunction,
        "beSvEndApi",
        0x40, /* instance size */
        beSvEndApi_GetVTable,
        beSvEndApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvEndApi_GetMetaObjectFunction(void)
{
    beSvEndApi_GetMetaObject();
}

void beSvEndApi_InitFields(void) {
    int index;
    void **found;
    igMetaObject *meta;
    igIntMetaField *clone;

    meta = g_beSvEndApi_metaObject;
    found = (void **)(igMetaObject_FindFieldByName(meta, "_orderType"));
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)(((igMetaObject *)meta)->_metaFields), (int)found);
    clone = (igIntMetaField *)(((igObjectDispatchView *)found)->CloneViaMetadata(1));
    ((Gap::Core::igIntMetaField *)clone)->setDefault(0xB);
    clone->_externalEnumStorage = (int)(&g_beSvEndApi_orderTypeStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
}

