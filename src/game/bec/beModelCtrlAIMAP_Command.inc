igMetaObject *g_beModelCtrlAIMAP_metaObject;

igMetaObject *beModelCtrlAIMAP_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlAIMAP_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beModelCtrlAIMAP_EnsureRegistered();
done:
    return g_beModelCtrlAIMAP_metaObject;
}

int beModelCtrlAIMAP_GetVTable(void) {
    beModelCtrlAIMAP obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlAIMAP_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlAIMAP_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMAP_Register);
}

CallbackArray *beModelCtrlAIMAP_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlAIMAP_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlAIMAP_GetMetaObjectFunction,
        "beModelCtrlAIMAP",
        0xc, /* instance size */
        beModelCtrlAIMAP_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlAIMAP_GetMetaObjectFunction(void)
{
    beModelCtrlAIMAP_GetMetaObject();
}

