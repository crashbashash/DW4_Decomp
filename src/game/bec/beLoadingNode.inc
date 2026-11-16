igMetaObject *g_beLoadingNode_metaObject;
igMetaField *g_beLoadingNode_lockTimeMetaField;
igMetaField *g_beLoadingNode_playLimitTimeMetaField;

void *beLoadingNode_ResolveMetaObject(void) {
    igMetaObject *g = g_beLoadingNode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLoadingNode_EnsureRegistered();
    }
    return g_beLoadingNode_metaObject;
}

int beLoadingNode_GetVTable(void) {
    beLoadingNode obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._bound = 0;
    obj._parentList = 0;
    obj._childList = 0;
    obj._vtable = (int)&g_beLoadingNode_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beLoadingNode_vtable[0];
    beNodeAnim_Destroy((int **)&obj, (long long)0);
    return vtable;
}

int **beNodeAnim_Destroy(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &g_beNodeAnim_vtable[0];
        if (arg0 != 0) {
            *arg0 = &g_igGroup_vtable[0];
            igSmartPointer_igNodeList_Destruct((char *)arg0 + 0x1C, -1);
            igNode_Destroy(arg0, 0);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void beLoadingNode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLoadingNode_Register);
}

void *beLoadingNode_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLoadingNode_metaObject,
        beNodeAnim_Register,
        beNodeAnim_GetPublishedMetaObject,
        beLoadingNode_GetMetaObject,
        "beLoadingNode",
        0x80, /* instance size */
        beLoadingNode_GetVTable,
        beLoadingNode_InitFields,
        beLoadingNode_StaticInitCallback, /* extra callback item */
        0 /* callback list */
    );
}

void beLoadingNode_GetMetaObject(void)
{
    beLoadingNode_ResolveMetaObject();
}

igMetaObject *beNodeAnim_GetPublishedMetaObject(void) {
    return g_beNodeAnim_metaObject;
}

static FieldFactory g_beLoadingNode_ctorTable[] = {
    igLongMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_beLoadingNode_fieldTable[] = {
    "_lockTime",
    "_playLimitTime",
};
static igMetaField **g_beLoadingNode_fieldHandles[] = {
    &g_beLoadingNode_lockTimeMetaField,
    &g_beLoadingNode_playLimitTimeMetaField,
};
static int g_beLoadingNode_fieldOffsets[] = {
    112,
    120,
};

void beLoadingNode_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beLoadingNode_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLoadingNode_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beLoadingNode_fieldTable, g_beLoadingNode_fieldHandles, g_beLoadingNode_fieldOffsets, base);
}

void beLoadingNode_StaticInitCallback(void)
{
    beLoadingNode_RegisterTraversalFunction();
}

