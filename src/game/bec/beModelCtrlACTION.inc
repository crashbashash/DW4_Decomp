igMetaObject *g_beModelCtrlACTION_metaObject;

void *beModelCtrlACTION_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlACTION_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlACTION_EnsureRegistered();
    }
    return g_beModelCtrlACTION_metaObject;
}

int beModelCtrlACTION_GetVTable(void) {
    beModelCtrlACTION obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlACTION_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlACTION_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlACTION_Register);
}

CallbackArray *beModelCtrlACTION_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlACTION_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlACTION_GetMetaObjectFunction,
        "beModelCtrlACTION",
        0xc, /* instance size */
        beModelCtrlACTION_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlACTION_GetMetaObjectFunction(void)
{
    beModelCtrlACTION_GetMetaObject();
}

