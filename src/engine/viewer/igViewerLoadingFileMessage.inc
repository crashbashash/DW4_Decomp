igMetaObject *g_igViewerLoadingFileMessage_metaObject;
igMetaField *g_igViewerLoadingFileMessage_currentMetaField;
igMetaField *g_igViewerLoadingFileMessage_filenameMetaField;

igViewerLoadingFileMessage *igViewerLoadingFileMessage_Create(int allocator) {
    igViewerLoadingFileMessage_EnsureRegistered();
    return (igViewerLoadingFileMessage *)igMetaObject_CreateInstance(g_igViewerLoadingFileMessage_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igViewerLoadingFileMessage_GetMetaObject(void) {
    igMetaObject *g = g_igViewerLoadingFileMessage_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        igViewerLoadingFileMessage_EnsureRegistered();
    return g_igViewerLoadingFileMessage_metaObject;
}

int igViewerLoadingFileMessage_GetVTable(void) {
    struct Obj_45a680 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igViewerLoadingFileMessage_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igViewerLoadingFileMessage_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    return t;
}

void igViewerLoadingFileMessage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewerLoadingFileMessage_Register);
}

CallbackArray *igViewerLoadingFileMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerLoadingFileMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        igViewerLoadingFileMessage_GetMetaObjectFunction,
        "igViewerLoadingFileMessage",
        0x10, /* instance size */
        igViewerLoadingFileMessage_GetVTable,
        &igViewerLoadingFileMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igViewerLoadingFileMessage_GetMetaObjectFunction(void) {
    igViewerLoadingFileMessage_GetMetaObject();
}

static FieldFactory g_igViewerLoadingFileMessage_ctorTable[] = {
    igBoolMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_igViewerLoadingFileMessage_fieldTable[] = {
    "_current",
    "_filename",
};
static igMetaField **g_igViewerLoadingFileMessage_fieldHandles[] = {
    &g_igViewerLoadingFileMessage_currentMetaField,
    &g_igViewerLoadingFileMessage_filenameMetaField,
};
static int g_igViewerLoadingFileMessage_fieldOffsets[] = {
    8,
    12,
};

void igViewerLoadingFileMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = g_igViewerLoadingFileMessage_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewerLoadingFileMessage_ctorTable, 2);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)))->setDefault("");
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewerLoadingFileMessage_fieldTable, g_igViewerLoadingFileMessage_fieldHandles, g_igViewerLoadingFileMessage_fieldOffsets, temp_s1);
}

