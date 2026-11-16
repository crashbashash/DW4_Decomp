igMetaObject *g_igViewerLoadingFileMessage_metaObject;
igMetaField *g_igViewerLoadingFileMessage_currentMetaField;
igMetaField *g_igViewerLoadingFileMessage_filenameMetaField;

void igViewerLoadingFileMessage_Create(int arg0) {
    igViewerLoadingFileMessage_EnsureRegistered();
    igMetaObject_CreateInstance(g_igViewerLoadingFileMessage_metaObject, arg0);
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
    igObject_InitHeader(&obj);
    obj.vt = &g_igViewerLoadingFileMessage_vtable[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &g_igViewerLoadingFileMessage_vtable[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void igViewerLoadingFileMessage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewerLoadingFileMessage_Register);
}

void igViewerLoadingFileMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerLoadingFileMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerLoadingFileMessage_GetMetaObject,
        "igViewerLoadingFileMessage",
        0x10, /* instance size */
        igViewerLoadingFileMessage_GetVTable,
        &igViewerLoadingFileMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewerLoadingFileMessage_GetMetaObject(void) {
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
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igViewerLoadingFileMessage_ctorTable, 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), "");
    igMetaObject_NameFields(temp_s0, g_igViewerLoadingFileMessage_fieldTable, g_igViewerLoadingFileMessage_fieldHandles, g_igViewerLoadingFileMessage_fieldOffsets, temp_s1);
}

