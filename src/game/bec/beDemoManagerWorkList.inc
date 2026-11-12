igMetaObject *FUN_00363630(void) {
    if (g_beDemoManagerWorkList_metaObject[0] == 0) {
        g_beDemoManagerWorkList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beDemoManagerWorkList_metaObject[0];
}

void *FUN_00363680(void) {
    igMetaObject *g = g_beDemoManagerWorkList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00363710();
    }
    return g_beDemoManagerWorkList_metaObject[0];
}

int beDemoManagerWorkList_GetVTable(void) {
    struct Obj_3636d0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535740[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00363710(void)
{
    igMetaObject_RunStaticInit(beDemoManagerWorkList_Register);
}

void *beDemoManagerWorkList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beDemoManagerWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beDemoManagerWorkList_GetMetaObject,
        beDemoManagerWorkList_className,
        0x14, /* instance size */
        beDemoManagerWorkList_GetVTable,
        0,
        0, /* extra callback item */
        text_096 /* callback list */
    );
}

void beDemoManagerWorkList_GetMetaObject(void)
{
    FUN_00363680();
}

