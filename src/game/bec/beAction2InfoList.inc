igMetaObject *g_beAction2InfoList_metaObject;

igMetaObject *beAction2InfoList_GetMetaObject(void) {
    igMetaObject *g = g_beAction2InfoList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beAction2InfoList_EnsureRegistered();
done:
    return g_beAction2InfoList_metaObject;
}

int beAction2InfoList_GetVTable(void) {
    beAction2InfoList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beAction2InfoList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beAction2InfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2InfoList_Register);
}

static igMetaObjectCallback g_beAction2InfoList_callbackList[] = { beAction2Info_EnsureRegistered, 0 };

CallbackArray *beAction2InfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2InfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beAction2InfoList_GetMetaObjectFunction,
        "beAction2InfoList",
        0x14, /* instance size */
        beAction2InfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beAction2InfoList_callbackList /* callback list */
    );
}

void beAction2InfoList_GetMetaObjectFunction(void)
{
    beAction2InfoList_GetMetaObject();
}

