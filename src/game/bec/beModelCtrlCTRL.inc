igMetaObject *g_beModelCtrlCTRL_metaObject;

void *beModelCtrlCTRL_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlCTRL_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlCTRL_EnsureRegistered();
    }
    return g_beModelCtrlCTRL_metaObject;
}

int beModelCtrlCTRL_GetVTable(void) {
    beModelCtrlCTRL obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlCTRL_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlCTRL_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlCTRL_Register);
}

void *beModelCtrlCTRL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlCTRL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlCTRL_GetMetaObjectFunction,
        "beModelCtrlCTRL",
        0xc, /* instance size */
        beModelCtrlCTRL_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlCTRL_GetMetaObjectFunction(void)
{
    beModelCtrlCTRL_GetMetaObject();
}

