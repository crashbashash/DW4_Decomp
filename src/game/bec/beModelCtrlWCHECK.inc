igMetaObject *g_beModelCtrlWCHECK_metaObject;

igMetaObject *beModelCtrlWCHECK_GetMetaObject(void) {
    if (g_beModelCtrlWCHECK_metaObject == 0 || !isValid(g_beModelCtrlWCHECK_metaObject)) beModelCtrlWCHECK_EnsureRegistered();
    return g_beModelCtrlWCHECK_metaObject;
}

int beModelCtrlWCHECK_GetVTable(void) {
    beModelCtrlWCHECK obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlWCHECK_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlWCHECK_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlWCHECK_Register);
}

CallbackArray *beModelCtrlWCHECK_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlWCHECK_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlWCHECK_GetMetaObjectFunction,
        "beModelCtrlWCHECK",
        0xc, /* instance size */
        beModelCtrlWCHECK_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlWCHECK_GetMetaObjectFunction(void)
{
    beModelCtrlWCHECK_GetMetaObject();
}

