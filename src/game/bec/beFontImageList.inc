igMetaObject *g_beFontImageList_metaObject;

igMetaObject *beFontImageList_GetOrCreateMetaObject(void) {
    if (g_beFontImageList_metaObject == 0) {
        g_beFontImageList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beFontImageList_metaObject;
}

igMetaObject *beFontImageList_GetMetaObject(void) {
    igMetaObject *g = g_beFontImageList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beFontImageList_EnsureRegistered();
done:
    return g_beFontImageList_metaObject;
}

int beFontImageList_GetVTable(void) {
    beFontImageList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beFontImageList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beFontImageList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beFontImageList_Register);
}

static igMetaObjectCallback g_beFontImageList_callbackList[] = { beFontImage_EnsureRegistered, 0 };

CallbackArray *beFontImageList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beFontImageList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beFontImageList_GetMetaObjectFunction,
        "beFontImageList",
        0x14, /* instance size */
        beFontImageList_GetVTable,
        0,
        0, /* extra callback item */
        g_beFontImageList_callbackList /* callback list */
    );
}

void beFontImageList_GetMetaObjectFunction(void)
{
    beFontImageList_GetMetaObject();
}

