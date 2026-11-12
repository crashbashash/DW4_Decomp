int FUN_00362360(void) {
    if (((int *)DAT_005896d0)[0] == 0) {
        ((int *)DAT_005896d0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005896d0)[0];
}

void *FUN_003623b0(void) {
    struct G *g = DAT_005896d0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00362440();
    }
    return DAT_005896d0[0];
}

int beFontGeomAttrPairList_GetVTable(void) {
    struct Obj_362400 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535940[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00362440(void)
{
    igMetaObject_RunStaticInit(beFontGeomAttrPairList_Register);
}

void *beFontGeomAttrPairList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontGeomAttrPairList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beFontGeomAttrPairList_GetMetaObject,
        beFontGeomAttrPairList_className,
        0x14, /* instance size */
        beFontGeomAttrPairList_GetVTable,
        0,
        0, /* extra callback item */
        g_beFontGeomAttrPairList_callbackList /* callback list */
    );
}

void beFontGeomAttrPairList_GetMetaObject(void)
{
    FUN_003623b0();
}

