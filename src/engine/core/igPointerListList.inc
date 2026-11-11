int FUN_002c8fc0(void) {
    if (DAT_005867d8[0] == 0) {
        DAT_005867d8[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_005867d8[0];
}

igMetaObject *igPointerListList_GetMetaObject(void)
{
    igMetaObject *g = g_igPointerListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c90a0();
    return g_igPointerListList_metaObject[0];
}

int igPointerListList_GetVTable(void) {
    struct Obj_2c9060 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00531f50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002c90a0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPointerListList_Register);
}

void igPointerListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPointerListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igPointerListList_GetMetaObject,
        igPointerListList_className,
        0x14, /* instance size */
        igPointerListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igPointerListList_callbackList /* callback list */
    );
}

void thunk_igPointerListList_GetMetaObject(void) {
    igPointerListList_GetMetaObject();
}

