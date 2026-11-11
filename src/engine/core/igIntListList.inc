int FUN_002c8980(void) {
    if (DAT_005867b8[0] == 0) {
        DAT_005867b8[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_005867b8[0];
}

igMetaObject *igIntListList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8a60();
    return g_igIntListList_metaObject[0];
}

int igIntListList_GetVTable(void) {
    struct Obj_2c8a20 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00532110[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002c8a60(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igIntListList_Register);
}

void igIntListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igIntListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igIntListList_GetMetaObject,
        igIntListList_className,
        0x14, /* instance size */
        igIntListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igIntListList_callbackList /* callback list */
    );
}

void thunk_igIntListList_GetMetaObject(void) {
    igIntListList_GetMetaObject();
}

