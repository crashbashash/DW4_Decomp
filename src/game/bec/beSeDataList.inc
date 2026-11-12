int FUN_00346120(void) {
    if (((int *)DAT_00587fc8)[0] == 0) {
        ((int *)DAT_00587fc8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00587fc8)[0];
}

igMetaObject *FUN_00346170(void)
{
    igMetaObject *g = DAT_00587fc8[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00346200();
    return DAT_00587fc8[0];
}

int beSeDataList_GetVTable(void) {
    struct Obj_3461c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538ed0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00346200(void)
{
    igMetaObject_RunStaticInit(beSeDataList_Register);
}

void *beSeDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSeDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSeDataList_GetMetaObject,
        beSeDataList_className,
        0x14, /* instance size */
        beSeDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSeDataList_callbackList /* callback list */
    );
}

void beSeDataList_GetMetaObject(void)
{
    FUN_00346170();
}

