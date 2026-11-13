igMetaObject *FUN_0044cbd0(void) {
    if (g_igRadioGroupSelectedObserver_metaObject[0] == 0) {
        g_igRadioGroupSelectedObserver_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igRadioGroupSelectedObserver_metaObject[0];
}

igMetaObject *igRadioGroupSelectedObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroupSelectedObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroupSelectedObserver_EnsureRegistered();
    return g_igRadioGroupSelectedObserver_metaObject[0];
}

int igRadioGroupSelectedObserver_GetVTable(void) {
    struct O o;
    igObject_InitHeader(&o.vt);
    o.vt = DAT_00540d60;
    return *(int *)((char *)&o.vt + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igRadioGroupSelectedObserver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRadioGroupSelectedObserver_Register);
}

void igRadioGroupSelectedObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroupSelectedObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igRadioGroupSelectedObserver_GetMetaObject,
        igRadioGroupSelectedObserver_className,
        0x10, /* instance size */
        igRadioGroupSelectedObserver_GetVTable,
        &igRadioGroupSelectedObserver_InitFields,
        0, /* extra callback item */
        g_igRadioGroupSelectedObserver_callbackList /* callback list */
    );
}

void thunk_igRadioGroupSelectedObserver_GetMetaObject(void) {
    igRadioGroupSelectedObserver_GetMetaObject();
}

void igRadioGroupSelectedObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRadioGroupSelectedObserver_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igRadioGroupSelectedObserver_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0044cdf0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &g_igRadioGroupSelectedObserver_fieldTable[0], &DAT_004d0000[0], &DAT_004d0008[0], temp_s2);
}

