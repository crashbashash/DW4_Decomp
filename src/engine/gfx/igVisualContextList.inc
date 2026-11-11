int FUN_00149ea0(int arg0) {
    FUN_00149f70();
    return igMetaObject_CreateInstance(*(int *)0x55F8E0, arg0);
}

igMetaObject *igVisualContextList_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualContextList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00149f70();
    return g_igVisualContextList_metaObject[0];
}

int igVisualContextList_GetVTable(void) {
    Obj_149f30 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00527170[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00149f70(void)
{
    igMetaObject_RunStaticInit(igVisualContextList_Register);
}

void igVisualContextList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVisualContextList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igVisualContextList_GetMetaObject,
        igVisualContextList_className,
        0x14, /* instance size */
        igVisualContextList_GetVTable,
        0,
        0, /* extra callback item */
        g_igVisualContextList_callbackList /* callback list */
    );
}

void thunk_igVisualContextList_GetMetaObject(void) {
    igVisualContextList_GetMetaObject();
}

