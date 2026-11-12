igMetaObject *FUN_0036a790(void)
{
    igMetaObject *g = DAT_00589db0[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0036a820();
    return DAT_00589db0[0];
}

int beBaseInfoManagerList_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_005347c0[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_0036a820(void)
{
    igMetaObject_RunStaticInit(beBaseInfoManagerList_Register);
}

void *beBaseInfoManagerList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoManagerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoManagerList_GetMetaObject,
        beBaseInfoManagerList_className,
        0x14, /* instance size */
        beBaseInfoManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoManagerList_callbackList /* callback list */
    );
}

void beBaseInfoManagerList_GetMetaObject(void)
{
    FUN_0036a790();
}

