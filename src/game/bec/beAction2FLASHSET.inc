igMetaObject *g_beAction2FLASHSET_metaObject;

void *beAction2FLASHSET_GetMetaObject(void) {
    igMetaObject *g = g_beAction2FLASHSET_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAction2FLASHSET_EnsureRegistered();
    }
    return g_beAction2FLASHSET_metaObject;
}

int beAction2FLASHSET_GetVTable(void) {
    beAction2FLASHSET obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beAction2FLASHSET_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beAction2FLASHSET_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2FLASHSET_Register);
}

CallbackArray *beAction2FLASHSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2FLASHSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2FLASHSET_GetMetaObjectFunction,
        "beAction2FLASHSET",
        0xc, /* instance size */
        beAction2FLASHSET_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2FLASHSET_GetMetaObjectFunction(void)
{
    beAction2FLASHSET_GetMetaObject();
}

