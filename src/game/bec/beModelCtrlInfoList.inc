igMetaObject *g_beModelCtrlInfoList_metaObject;

igMetaObject *beModelCtrlInfoList_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beModelCtrlInfoList_EnsureRegistered();
done:
    return g_beModelCtrlInfoList_metaObject;
}

int beModelCtrlInfoList_GetVTable(void) {
    beModelCtrlInfoList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlInfoList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoList_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoList_callbackList[] = { beModelCtrlInfo_EnsureRegistered, 0 };

CallbackArray *beModelCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beModelCtrlInfoList_GetMetaObjectFunction,
        "beModelCtrlInfoList",
        0x14, /* instance size */
        beModelCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlInfoList_callbackList /* callback list */
    );
}

void beModelCtrlInfoList_GetMetaObjectFunction(void)
{
    beModelCtrlInfoList_GetMetaObject();
}

