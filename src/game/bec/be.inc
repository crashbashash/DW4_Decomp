igMetaObject *g_be_metaObject;
igMetaField *g_be_stringRefListMetaField;

void be_CreateInstance(int arg0) {
    be_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58A030, arg0);
}

igMetaObject *be_GetOrCreateMetaObject(void) {
    if (g_be_metaObject == 0) {
        g_be_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_be_metaObject;
}

void *be_GetMetaObject(void) {
    igMetaObject *g = g_be_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        be_EnsureRegistered();
    }
    return g_be_metaObject;
}

int be_GetVTable(void) {
    Obj_36e080 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.s = 0;
    obj.vt = &g_be_vtable[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_be_vtable[0];
    obj.releaseRef();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.releaseStr();
    return r;
}

void be_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(be_Register);
}

static igMetaObjectCallback g_be_callbackList[] = { igStringRefList_EnsureRegistered, 0 };

void *be_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_be_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        be_GetMetaObjectFunction,
        "be",
        0x14, /* instance size */
        be_GetVTable,
        be_InitFields,
        0, /* extra callback item */
        g_be_callbackList /* callback list */
    );
}

void be_GetMetaObjectFunction(void)
{
    be_GetMetaObject();
}

static FieldFactory g_be_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_be_fieldTable[] = {
    "_stringRefList",
};
static igMetaField **g_be_fieldHandles[] = {
    &g_be_stringRefListMetaField,
};
static int g_be_fieldOffsets[] = {
    16,
};

void be_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_be_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_be_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_be_fieldTable, g_be_fieldHandles, g_be_fieldOffsets, temp_s2);
}

