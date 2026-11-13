void be_CreateInstance(int arg0) {
    be_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58A030, arg0);
}

igMetaObject *FUN_0036dfe0(void) {
    if (g_be_metaObject[0] == 0) {
        g_be_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_be_metaObject[0];
}

void *FUN_0036e030(void) {
    igMetaObject *g = g_be_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        be_EnsureRegistered();
    }
    return g_be_metaObject[0];
}

int be_GetVTable(void) {
    Obj_36e080 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.s = 0;
    obj.vt = &DAT_00539f10[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00539f10[0];
    obj.releaseRef();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.releaseStr();
    return r;
}

void be_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(be_Register);
}

void *be_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_be_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        be_GetMetaObject,
        be_className,
        0x14, /* instance size */
        be_GetVTable,
        be_InitFields,
        0, /* extra callback item */
        g_be_callbackList /* callback list */
    );
}

void be_GetMetaObject(void)
{
    FUN_0036e030();
}

void be_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_be_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_be_ctorTable[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_be_fieldTable[0], &DAT_004c8248[0], &DAT_004c8250[0], temp_s2);
}

