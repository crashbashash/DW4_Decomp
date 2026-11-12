int FUN_00363a90(void) {
    if (((int *)DAT_005897f0)[0] == 0) {
        ((int *)DAT_005897f0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005897f0)[0];
}

igMetaObject *FUN_00363ae0(void)
{
    igMetaObject *g = DAT_005897f0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_00363b70();
    return DAT_005897f0[0];
}

int beDemoKeepMesList_GetVTable(void) {
    struct Obj_363b30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535670[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00363b70(void)
{
    igMetaObject_RunStaticInit(beDemoKeepMesList_Register);
}

void *beDemoKeepMesList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoKeepMesList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDemoKeepMesList_GetMetaObject,
        beDemoKeepMesList_className,
        0x14, /* instance size */
        beDemoKeepMesList_GetVTable,
        0,
        0, /* extra callback item */
        g_beDemoKeepMesList_callbackList /* callback list */
    );
}

void beDemoKeepMesList_GetMetaObject(void)
{
    FUN_00363ae0();
}

