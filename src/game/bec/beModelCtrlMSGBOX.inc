igMetaObject *g_beModelCtrlMSGBOX_metaObject;

void *beModelCtrlMSGBOX_GetMetaObject(void) {
    unsigned char b;
    if (g_beModelCtrlMSGBOX_metaObject != 0) {
        b = (g_beModelCtrlMSGBOX_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beModelCtrlMSGBOX_EnsureRegistered();
done:
    return g_beModelCtrlMSGBOX_metaObject;
}

int beModelCtrlMSGBOX_GetVTable(void) {
    beModelCtrlMSGBOX obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlMSGBOX_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlMSGBOX_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMSGBOX_Register);
}

void *beModelCtrlMSGBOX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMSGBOX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMSGBOX_GetMetaObjectFunction,
        "beModelCtrlMSGBOX",
        0xc, /* instance size */
        beModelCtrlMSGBOX_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMSGBOX_GetMetaObjectFunction(void)
{
    beModelCtrlMSGBOX_GetMetaObject();
}

