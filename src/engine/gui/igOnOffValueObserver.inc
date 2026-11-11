igMetaObject *igOnOffValueObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffValueObserver_EnsureRegistered();
    return g_igOnOffValueObserver_metaObject[0];
}

int igOnOffValueObserver_GetVTable(void) {
    struct Obj_44ca40 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540cf0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igOnOffValueObserver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOnOffValueObserver_Register);
}

void igOnOffValueObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffValueObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igOnOffValueObserver_GetMetaObject,
        igOnOffValueObserver_className,
        0x10, /* instance size */
        igOnOffValueObserver_GetVTable,
        &igOnOffValueObserver_InitFields,
        0, /* extra callback item */
        g_igOnOffValueObserver_callbackList /* callback list */
    );
}

void thunk_igOnOffValueObserver_GetMetaObject(void) {
    igOnOffValueObserver_GetMetaObject();
}

int FUN_0044cb20(void) {
    return DAT_0058c1c0[0];
}

void igOnOffValueObserver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c220[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cffc8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044cdf0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cffd0[0], &DAT_004cffd8[0], &DAT_004cffe0[0], temp_s2);
}

