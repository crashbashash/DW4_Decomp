void FUN_004590c0(int arg0) {
    FUN_00459190();
    igMetaObject_CreateInstance(*(int *)0x58C770, arg0);
}

void *igViewerAction_GetMetaObject(void) {
    igMetaObject *g = g_igViewerAction_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00459190();
    }
    return g_igViewerAction_metaObject[0];
}

int igViewerAction_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00542460[0];
    off = *(int *)((char *)(((int *)g_objectSystem[0])) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_00459190(void)
{
    igMetaObject_RunStaticInit(igViewerAction_Register);
}

void igViewerAction_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerAction_metaObject,
        igAction_Register,
        igAction_GetPublishedMetaObject,
        thunk_igViewerAction_GetMetaObject,
        igViewerAction_className,
        0x18, /* instance size */
        igViewerAction_GetVTable,
        &igViewerAction_InitFields,
        0, /* extra callback item */
        g_igViewerAction_callbackList /* callback list */
    );
}

void thunk_igViewerAction_GetMetaObject(void) {
    igViewerAction_GetMetaObject();
}

void igViewerAction_InitFields(void) {
    void *f2;
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igViewerAction_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igViewerAction_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_00459380();
    *(char *)((char *)(temp_s1) + 60) = 0;
    f2 = igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1);
    *(short *)((char *)f2 + 20) = 0xC;
    igMetaObject_NameFields(temp_s0, &g_igViewerAction_fieldTable[0], &DAT_004d0ad0[0], &DAT_004d0ad8[0], temp_s2);
}

