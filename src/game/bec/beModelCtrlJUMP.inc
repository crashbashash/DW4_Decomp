igMetaObject *g_beModelCtrlJUMP_metaObject;

void *beModelCtrlJUMP_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlJUMP_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlJUMP_EnsureRegistered();
    }
    return g_beModelCtrlJUMP_metaObject;
}

int beModelCtrlJUMP_GetVTable(void) {
    beModelCtrlJUMP obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlJUMP_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlJUMP_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlJUMP_Register);
}

CallbackArray *beModelCtrlJUMP_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlJUMP_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlJUMP_GetMetaObjectFunction,
        "beModelCtrlJUMP",
        0xc, /* instance size */
        beModelCtrlJUMP_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlJUMP_GetMetaObjectFunction(void)
{
    beModelCtrlJUMP_GetMetaObject();
}

