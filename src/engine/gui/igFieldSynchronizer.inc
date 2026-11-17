igMetaObject *g_igFieldSynchronizer_metaObject;
igMetaField *g_igFieldSynchronizer_viewsMetaField;

void FUN_004509c0(int arg0) {
    igFieldSynchronizer_EnsureRegistered();
    igMetaObject_CreateInstance(g_igFieldSynchronizer_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_00450a00(void) {
    if (g_igFieldSynchronizer_metaObject == 0) {
        g_igFieldSynchronizer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFieldSynchronizer_metaObject;
}

igMetaObject *igFieldSynchronizer_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldSynchronizer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldSynchronizer_EnsureRegistered();
    return g_igFieldSynchronizer_metaObject;
}

int igFieldSynchronizer_GetVTable(void) {
    struct Obj_450aa0 o;
    struct R *t;
    int r;
    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igFieldSynchronizer_vtable[0];
    o.p = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem) + 916));
    o.vt = &g_igFieldSynchronizer_vtable[0];
    if (&o.p != 0) {
        t = o.p;
        if (t != 0) {
            t->rc = t->rc - 1;
            if ((t->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
    }
    return r;
}

void igFieldSynchronizer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldSynchronizer_Register);
}

static igMetaObjectCallback g_igFieldSynchronizer_callbackList[] = { igFieldChangeViewList_EnsureRegistered, 0 };

CallbackArray *igFieldSynchronizer_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFieldSynchronizer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFieldSynchronizer_GetMetaObject,
        "igFieldSynchronizer",
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

static FieldFactory g_igFieldSynchronizer_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igFieldSynchronizer_fieldTable[] = {
    "_views",
};
static igMetaField **g_igFieldSynchronizer_fieldHandles[] = {
    &g_igFieldSynchronizer_viewsMetaField,
};
static int g_igFieldSynchronizer_fieldOffsets[] = {
    8,
};

void igFieldSynchronizer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igFieldSynchronizer_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igFieldSynchronizer_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00450c70();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igFieldSynchronizer_fieldTable, g_igFieldSynchronizer_fieldHandles, g_igFieldSynchronizer_fieldOffsets, temp_s2);
}

