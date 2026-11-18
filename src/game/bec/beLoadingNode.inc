igMetaObject *g_beLoadingNode_metaObject;
igMetaField *g_beLoadingNode_lockTimeMetaField;
igMetaField *g_beLoadingNode_playLimitTimeMetaField;

igMetaObject *beLoadingNode_ResolveMetaObject(void) {
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
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beLoadingNode_vtable[0];
    beNodeAnim_Destroy((beNodeAnim *)&obj, (long long)0);
    return vtable;
}

beNodeAnim *beNodeAnim_Destroy(beNodeAnim *self, long long delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_beNodeAnim_vtable[0];
        /* ~igGroup is inlined here with its own null check on `this` */
        if (self != 0) {
            self->_vtable = (int)&g_igGroup_vtable[0];
            igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)&self->_childList, -1);
            igNode_Destroy((igNode *)self, 0);
        }
        if ((short)delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beLoadingNode_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLoadingNode_Register);
}

CallbackArray *beLoadingNode_Register(void) {
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
    igMetaObject *meta;

    meta = g_beLoadingNode_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLoadingNode_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beLoadingNode_fieldTable, g_beLoadingNode_fieldHandles, g_beLoadingNode_fieldOffsets, base);
}

void beLoadingNode_StaticInitCallback(void)
{
    beLoadingNode_RegisterTraversalFunction();
}

