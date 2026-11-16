igMetaObject *g_igViewerModeChangeMessage_metaObject;
igMetaField *g_igViewerModeChangeMessage_stateMetaField;
igMetaField *g_igViewerModeChangeMessage_modeMetaField;

igMetaObject *FUN_0045a450(void) {
    if (g_igViewerModeChangeMessage_metaObject == 0) {
        g_igViewerModeChangeMessage_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewerModeChangeMessage_metaObject;
}

igMetaObject *igViewerModeChangeMessage_GetMetaObject(void) {
    igMetaObject *g = g_igViewerModeChangeMessage_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0045a580();
done:
    return g_igViewerModeChangeMessage_metaObject;
}

int igViewerModeChangeMessage_GetVTable(void) {
    Obj_45a450 o;
    int r;
    char *p;
    int *hdr;
    int c;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igViewerModeChangeMessage_vtable[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void *)g_objectSystem)) + 916));
    o.vt = &g_igViewerModeChangeMessage_vtable[0];
    if (&o.s != 0) {
        p = (char *)o.s;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (StringTokenHeader *)hdr);
            }
        }
    }
    return r;
}

void FUN_0045a580(void)
{
    igMetaObject_RunStaticInit(igViewerModeChangeMessage_Register);
}

CallbackArray *igViewerModeChangeMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewerModeChangeMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerModeChangeMessage_GetMetaObject,
        "igViewerModeChangeMessage",
        0x10, /* instance size */
        igViewerModeChangeMessage_GetVTable,
        &igViewerModeChangeMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewerModeChangeMessage_GetMetaObject(void) {
    igViewerModeChangeMessage_GetMetaObject();
}

static FieldFactory g_igViewerModeChangeMessage_ctorTable[] = {
    igBoolMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_igViewerModeChangeMessage_fieldTable[] = {
    "_state",
    "_mode",
};
static igMetaField **g_igViewerModeChangeMessage_fieldHandles[] = {
    &g_igViewerModeChangeMessage_stateMetaField,
    &g_igViewerModeChangeMessage_modeMetaField,
};
static int g_igViewerModeChangeMessage_fieldOffsets[] = {
    8,
    12,
};

void igViewerModeChangeMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = g_igViewerModeChangeMessage_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igViewerModeChangeMessage_ctorTable, 2);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igViewerModeChangeMessage_fieldTable, g_igViewerModeChangeMessage_fieldHandles, g_igViewerModeChangeMessage_fieldOffsets, temp_s1);
}

