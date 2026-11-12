void *FUN_003657a0(void) {
    igMetaObject *g = g_beDataBaseList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00365830();
    }
    return g_beDataBaseList_metaObject[0];
}

int beDataBaseList_GetVTable(void) {
    struct Obj_3657f0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005351c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00365830(void)
{
    igMetaObject_RunStaticInit(beDataBaseList_Register);
}

void *beDataBaseList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDataBaseList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDataBaseList_GetMetaObject,
        beDataBaseList_className,
        0x14, /* instance size */
        beDataBaseList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDataBaseList_callbackList /* callback list */
    );
}

void beDataBaseList_GetMetaObject(void)
{
    FUN_003657a0();
}

