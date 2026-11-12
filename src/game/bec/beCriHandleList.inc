int FUN_00366780(void) {
    if (((int *)DAT_005899c0)[0] == 0) {
        ((int *)DAT_005899c0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005899c0)[0];
}

void *FUN_003667d0(void) {
    struct G *g = DAT_005899c0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00366860();
    }
    return DAT_005899c0[0];
}

int beCriHandleList_GetVTable(void) {
    struct Obj_366820 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00534fc0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00366860(void)
{
    igMetaObject_RunStaticInit(beCriHandleList_Register);
}

void *beCriHandleList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriHandleList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beCriHandleList_GetMetaObject,
        beCriHandleList_className,
        0x14, /* instance size */
        beCriHandleList_GetVTable,
        0,
        0, /* extra callback item */
        g_beCriHandleList_callbackList /* callback list */
    );
}

void beCriHandleList_GetMetaObject(void)
{
    FUN_003667d0();
}

