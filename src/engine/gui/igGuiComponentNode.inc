igMetaObject *g_igGuiComponentNode_metaObject;
igMetaField *g_igGuiComponentNode_componentMetaField;

igMetaObject *FUN_0044f540(void) {
    if (g_igGuiComponentNode_metaObject == 0) {
        g_igGuiComponentNode_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGuiComponentNode_metaObject;
}

igMetaObject *igGuiComponentNode_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentNode_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentNode_RunStaticInit();
    return g_igGuiComponentNode_metaObject;
}

int igGuiComponentNode_GetVTable(void) {
    struct Obj_44f5e0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &g_igGuiComponentNode_vtable[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_igGuiComponentNode_vtable[0];
    igGroup_Destroy(&obj, 0);
    return t;
}

void igGuiComponentNode_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentNode_Register);
}

static igMetaObjectCallback g_igGuiComponentNode_callbackList[] = { igGuiComponent_EnsureRegistered, 0 };

void igGuiComponentNode_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiComponentNode_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igGuiComponentNode_GetMetaObject,
        "igGuiComponentNode",
        0x24, /* instance size */
        igGuiComponentNode_GetVTable,
        &igGuiComponentNode_InitFields,
        0, /* extra callback item */
        g_igGuiComponentNode_callbackList /* callback list */
    );
}

void thunk_igGuiComponentNode_GetMetaObject(void) {
    igGuiComponentNode_GetMetaObject();
}

static FieldFactory g_igGuiComponentNode_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igGuiComponentNode_fieldTable[] = {
    "_component",
};
static igMetaField **g_igGuiComponentNode_fieldHandles[] = {
    &g_igGuiComponentNode_componentMetaField,
};
static int g_igGuiComponentNode_fieldOffsets[] = {
    32,
};

void igGuiComponentNode_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiComponentNode_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igGuiComponentNode_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_igGuiComponentNode_fieldTable, g_igGuiComponentNode_fieldHandles, g_igGuiComponentNode_fieldOffsets, temp_s2);
}

