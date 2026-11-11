int FUN_00231400(void) {
    if (DAT_0056dac8[0] == 0) {
        DAT_0056dac8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dac8[0];
}

igMetaObject *igMessenger_GetMetaObject(void)
{
    igMetaObject *g = g_igMessenger_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231530();
    return g_igMessenger_metaObject[0];
}

int igMessenger_GetVTable(void) {
    struct W o;
    int r;
    struct Ref *p;
    igObject_InitHeader(&o);
    o.vt = DAT_0052cf20;
    o.ref = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0052cf20;
    if (&o.ref != 0) {
        p = o.ref;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
    }
    return r;
}

void FUN_00231530(void)
{
    igMetaObject_RunStaticInit(igMessenger_Register);
}

void igMessenger_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessenger_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessenger_GetMetaObject,
        igMessenger_className,
        0xC, /* instance size */
        igMessenger_GetVTable,
        &igMessenger_InitFields,
        0, /* extra callback item */
        g_igMessenger_callbackList /* callback list */
    );
}

void thunk_igMessenger_GetMetaObject(void) {
    igMessenger_GetMetaObject();
}

void igMessenger_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dac8[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497fb8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002320b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00497fc0[0], &DAT_00497fc8[0], &DAT_00497fd0[0], temp_s2);
}

