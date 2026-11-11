int FUN_002b8390(void) {
    if (DAT_00585828[0] == 0) {
        DAT_00585828[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00585828[0];
}

igMetaObject *igThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b8470();
    return g_igThreadList_metaObject[0];
}

int igThreadList_GetVTable(void) {
    struct Obj_2b8430 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00533350[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916));
}

void FUN_002b8470(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igThreadList_Register);
}

void igThreadList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igThreadList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igThreadList_GetMetaObject,
        igThreadList_className,
        0x14, /* instance size */
        igThreadList_GetVTable,
        0,
        0, /* extra callback item */
        g_igThreadList_callbackList /* callback list */
    );
}

void thunk_igThreadList_GetMetaObject(void) {
    igThreadList_GetMetaObject();
}

