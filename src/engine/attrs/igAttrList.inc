void FUN_0013aec0(int arg0) {
    FUN_0013afe0();
    igMetaObject_CreateInstance(*(int *)0x55F460, arg0);
}

int FUN_0013af00(void) {
    if (DAT_0055f460[0] == 0) {
        DAT_0055f460[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f460[0];
}

igMetaObject *igAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013afe0();
    return g_igAttrList_metaObject[0];
}

int igAttrList_GetVTable(void) {
    struct Obj_13afa0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524420[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0013afe0(void)
{
    igMetaObject_RunStaticInit(igAttrList_Register);
}

void igAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrList_GetMetaObject,
        igAttrList_className,
        0x14, /* instance size */
        igAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrList_callbackList /* callback list */
    );
}

void thunk_igAttrList_GetMetaObject(void) {
    igAttrList_GetMetaObject();
}

