S_352b90 *FUN_00352b90(void) {
    S_352b90 *g = DAT_00588b98[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_00352c20();
done:
    return DAT_00588b98[0];
}

int beModelCtrlInfoList_GetVTable(void) {
    struct Obj_352be0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00537c80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00352c20(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoList_Register);
}

void *beModelCtrlInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beModelCtrlInfoList_GetMetaObject,
        beModelCtrlInfoList_className,
        0x14, /* instance size */
        beModelCtrlInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beModelCtrlInfoList_callbackList /* callback list */
    );
}

void beModelCtrlInfoList_GetMetaObject(void)
{
    FUN_00352b90();
}

