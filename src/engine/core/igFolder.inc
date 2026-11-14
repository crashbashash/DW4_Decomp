void * igFolder_Create(int pool) {
    igFolder_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586368), (igMemoryPoolView *)pool));
}

igMetaObject *igFolder_GetMetaObject(void)
{
    igMetaObject *g = g_igFolder_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFolder_EnsureRegistered();
    return g_igFolder_metaObject[0];
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
    vtable = *(int *)((char *)&folder + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    folder._vtable = (int)(&g_igFolder_vtable[0]);
    if (nameSlot != 0) {
        text = *nameSlot;
        if (text != 0) {
            header = (int *)((char *)text - 8);
            refCount = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igFolder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFolder_Register);
}

void igFolder_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igFolder_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igFolder_GetMetaObjectFunction,
        igFolder_className,
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

void igFolder_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)(((void * *)g_igFolder_metaObject)[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igFolder_ctorTable[0], 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igFolder_fieldTable[0], (igMetaField ***)&g_igFolder_fieldDescriptors[0], &g_igFolder_fieldOffsets[0], base);
    *(int *)((char *)(((void * *)g_igFolder_metaObject)[0]) + 60) = (int)(&igPsx2Folder_GetMetaObjectFunction);
}

