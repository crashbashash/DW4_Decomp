igMetaObject *g_igFolder_metaObject;
igMetaField *g_igFolder_folderNameMetaField;

igFolder *igFolder_Create(int allocator) {
    igFolder_EnsureRegistered();
    return (igFolder *)igMetaObject_CreateInstance(g_igFolder_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igFolder_GetMetaObject(void)
{
    igMetaObject *g = g_igFolder_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFolder_EnsureRegistered();
    return g_igFolder_metaObject;
}

int igFolder_GetVTable(void) {
    igFolder folder;
    void **nameSlot;
    int *header;
    int vtable;
    int refCount;
    void *text;

    igObject_InitHeader((igObject *)&folder);
    nameSlot = (void **)&folder._folderName;
    folder._vtable = (int)(&g_igFolder_vtable[0]);
    *nameSlot = 0;
    vtable = *(int *)((char *)&folder + g_objectSystem->vtableProbeOffset);
    folder._vtable = (int)(&g_igFolder_vtable[0]);
    if (nameSlot != 0) {
        text = *nameSlot;
        if (text != 0) {
            header = (int *)((char *)text - 8);
            refCount = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igFolder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFolder_Register);
}

CallbackArray *igFolder_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igFolder_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igFolder_GetMetaObjectFunction,
        "igFolder",
        0xC,
        igFolder_GetVTable,
        igFolder_InitFields,
        0,
        0
    );
}

void igFolder_GetMetaObjectFunction(void) {
    igFolder_GetMetaObject();
}

static FieldFactory g_igFolder_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igFolder_fieldTable[] = {
    "_folderName",
};
static igMetaField **g_igFolder_fieldDescriptors[] = {
    &g_igFolder_folderNameMetaField,
};
static int g_igFolder_fieldOffsets[] = {
    8,
};

void igFolder_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)((void *)g_igFolder_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igFolder_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igFolder_fieldTable, g_igFolder_fieldDescriptors, g_igFolder_fieldOffsets, base);
    *(int *)((char *)((void *)g_igFolder_metaObject) + 60) = (int)(&igPsx2Folder_GetMetaObjectFunction);
}

