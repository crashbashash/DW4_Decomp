void FUN_004509c0(int arg0) {
    igFieldSynchronizer_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C538, arg0);
}

igMetaObject *FUN_00450a00(void) {
    if (g_igFieldSynchronizer_metaObject[0] == 0) {
        g_igFieldSynchronizer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igFieldSynchronizer_metaObject[0];
}

igMetaObject *igFieldSynchronizer_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldSynchronizer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldSynchronizer_EnsureRegistered();
    return g_igFieldSynchronizer_metaObject[0];
}

int igFieldSynchronizer_GetVTable(void) {
    struct Obj_450aa0 o;
    struct R *t;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_00541a40[0];
    o.p = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00541a40[0];
    if (&o.p != 0) {
        t = o.p;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    return r;
}

void igFieldSynchronizer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldSynchronizer_Register);
}

void igFieldSynchronizer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldSynchronizer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFieldSynchronizer_GetMetaObject,
        igFieldSynchronizer_className,
        0xC, /* instance size */
        igFieldSynchronizer_GetVTable,
        &igFieldSynchronizer_InitFields,
        0, /* extra callback item */
        g_igFieldSynchronizer_callbackList /* callback list */
    );
}

void thunk_igFieldSynchronizer_GetMetaObject(void) {
    igFieldSynchronizer_GetMetaObject();
}

void igFieldSynchronizer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFieldSynchronizer_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d06c8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00450c70();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004d06d0[0], &DAT_004d06d8[0], &DAT_004d06e0[0], temp_s2);
}

