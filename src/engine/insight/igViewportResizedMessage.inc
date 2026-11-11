int FUN_002332b0(int arg0) {
    FUN_00233380();
    return igMetaObject_CreateInstance(*(int *)0x56DC10, arg0);
}

igMetaObject *igViewportResizedMessage_GetMetaObject(void)
{
    igMetaObject *g = g_igViewportResizedMessage_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233380();
    return g_igViewportResizedMessage_metaObject[0];
}

int igViewportResizedMessage_GetVTable(void) {
    struct Obj_233340 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052cc80[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00233380(void)
{
    igMetaObject_RunStaticInit(igViewportResizedMessage_Register);
}

void igViewportResizedMessage_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewportResizedMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewportResizedMessage_GetMetaObject,
        igViewportResizedMessage_className,
        0x18, /* instance size */
        igViewportResizedMessage_GetVTable,
        &igViewportResizedMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewportResizedMessage_GetMetaObject(void) {
    igViewportResizedMessage_GetMetaObject();
}

void igViewportResizedMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dc10[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498218[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_00498220[0], &DAT_00498228[0], &DAT_00498230[0], temp_s1);
}

