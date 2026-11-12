igMetaObject *FUN_0036c9c0(void) {
    igMetaObject *g = g_beAction2InfoList_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0036ca50();
done:
    return g_beAction2InfoList_metaObject[0];
}

int beAction2InfoList_GetVTable(void) {
    struct Obj_36ca10 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005342e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0036ca50(void)
{
    igMetaObject_RunStaticInit(beAction2InfoList_Register);
}

void *beAction2InfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2InfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beAction2InfoList_GetMetaObject,
        beAction2InfoList_className,
        0x14, /* instance size */
        beAction2InfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beAction2InfoList_callbackList /* callback list */
    );
}

void beAction2InfoList_GetMetaObject(void)
{
    FUN_0036c9c0();
}

