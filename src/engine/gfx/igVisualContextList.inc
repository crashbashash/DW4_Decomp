igMetaObject *g_igVisualContextList_metaObject;

int igVisualContextList_Create(int arg0) {
    igVisualContextList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igVisualContextList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVisualContextList_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVisualContextList_EnsureRegistered();
    return g_igVisualContextList_metaObject;
}

int igVisualContextList_GetVTable(void) {
    Obj_149f30 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igVisualContextList_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igVisualContextList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVisualContextList_Register);
}

static igMetaObjectCallback g_igVisualContextList_callbackList[] = { Gap::Gfx::igVisualContext::arkRegister, 0 };

CallbackArray *igVisualContextList_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVisualContextList_metaObject,
        Gap::Core::igNonRefCountedObjectList::arkRegisterInternal,
        Gap::Core::igNonRefCountedObjectList::getClassMeta,
        igVisualContextList_GetMetaObjectFunction,
        "igVisualContextList",
        0x14, /* instance size */
        igVisualContextList_GetVTable,
        0,
        0, /* extra callback item */
        g_igVisualContextList_callbackList /* callback list */
    );
}

void igVisualContextList_GetMetaObjectFunction(void) {
    igVisualContextList_GetMetaObject();
}

