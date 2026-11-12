int FUN_00361360(void) {
    if (((int *)DAT_00589638)[0] == 0) {
        ((int *)DAT_00589638)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589638)[0];
}

igMetaObject *FUN_003613b0(void)
{
    igMetaObject *g = DAT_00589638[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00361440();
    return DAT_00589638[0];
}

int beUnicodeObjList_GetVTable(void) {
    struct Obj_361400 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535b00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00361440(void)
{
    igMetaObject_RunStaticInit(beUnicodeObjList_Register);
}

void *beUnicodeObjList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beUnicodeObjList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beUnicodeObjList_GetMetaObject,
        beUnicodeObjList_className,
        0x14, /* instance size */
        beUnicodeObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_beUnicodeObjList_callbackList /* callback list */
    );
}

void beUnicodeObjList_GetMetaObject(void)
{
    FUN_003613b0();
}

