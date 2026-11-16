igMetaObject *g_beModelCtrlLABEL_metaObject;

void *beModelCtrlLABEL_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlLABEL_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlLABEL_EnsureRegistered();
    }
    return g_beModelCtrlLABEL_metaObject;
}

int beModelCtrlLABEL_GetVTable(void) {
    beModelCtrlLABEL obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlLABEL_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlLABEL_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLABEL_Register);
}

CallbackArray *beModelCtrlLABEL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlLABEL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLABEL_GetMetaObjectFunction,
        "beModelCtrlLABEL",
        0xc, /* instance size */
        beModelCtrlLABEL_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlLABEL_GetMetaObjectFunction(void)
{
    beModelCtrlLABEL_GetMetaObject();
}

