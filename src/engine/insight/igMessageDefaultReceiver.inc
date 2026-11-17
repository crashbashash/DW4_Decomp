igMetaObject *g_igMessageDefaultReceiver_metaObject;
igMetaField *g_igMessageDefaultReceiver_msgHandlerMetaField;
igMetaField *g_igMessageDefaultReceiver_msgHandlerFuncMetaField;

igMessageDefaultReceiver *igMessageDefaultReceiver_CreateInstance(int allocator) {
    FUN_00232320();
    return (igMessageDefaultReceiver *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x56DB30), (igMemoryPoolView *)allocator);
}

igMetaObject *igMessageDefaultReceiver_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMessageDefaultReceiver_metaObject != 0) {
        ready = (g_igMessageDefaultReceiver_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00232320();
done:
    return g_igMessageDefaultReceiver_metaObject;
}

int igMessageDefaultReceiver_GetVTable(void) {
    union U_232290 u;
    int temp_s0;
    char *ps;
    int *p;
    int v;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igMessageDefaultReceiver_vtable[0];
    ps = &u.b[8];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.vt = (int)&g_igMessageDefaultReceiver_vtable[0];
    if (ps != 0) {
        p = *(int **)ps;
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    return temp_s0;
}

void FUN_00232320(void)
{
    igMetaObject_RunStaticInit(igMessageDefaultReceiver_Register);
}

static igMetaObjectCallback g_igMessageDefaultReceiver_callbackList[] = { igObject_EnsureRegistered, 0 };

CallbackArray *igMessageDefaultReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageDefaultReceiver_metaObject,
        igMessageReceiver_Register,
        igMessageReceiver_GetPublishedMetaObject,
        thunk_igMessageDefaultReceiver_GetMetaObject,
        "igMessageDefaultReceiver",
        0x18, /* instance size */
        igMessageDefaultReceiver_GetVTable,
        &igMessageDefaultReceiver_InitFields,
        0, /* extra callback item */
        g_igMessageDefaultReceiver_callbackList /* callback list */
    );
}

void thunk_igMessageDefaultReceiver_GetMetaObject(void) {
    igMessageDefaultReceiver_GetMetaObject();
}

igMetaObject *FUN_002323c0(void) {
    return g_igMessageReceiver_metaObject;
}

static FieldFactory g_igMessageDefaultReceiver_ctorTable[] = {
    igObjectRefMetaField_Create,
    igStructMetaField_Create,
};
static const char *g_igMessageDefaultReceiver_fieldTable[] = {
    "_msgHandler",
    "_msgHandlerFunc",
};
static igMetaField **g_igMessageDefaultReceiver_fieldHandles[] = {
    &g_igMessageDefaultReceiver_msgHandlerMetaField,
    &g_igMessageDefaultReceiver_msgHandlerFuncMetaField,
};
static int g_igMessageDefaultReceiver_fieldOffsets[] = {
    8,
    12,
};

void igMessageDefaultReceiver_InitFields(void) {
    igMetaObject *temp_s0;
    int temp_s1;
    char *p;

    temp_s0 = g_igMessageDefaultReceiver_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igMessageDefaultReceiver_ctorTable, 2);
    p = (char *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1);
    *(int *)(p + 56) = (int)g_igObject_metaObject[0];
    p = (char *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1);
    *(short *)(p + 20) = 0xC;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igMessageDefaultReceiver_fieldTable, g_igMessageDefaultReceiver_fieldHandles, g_igMessageDefaultReceiver_fieldOffsets, temp_s1);
}

