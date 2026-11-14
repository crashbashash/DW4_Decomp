void * igContextExtInfo_Create(int allocator) {
    igContextExtInfo_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5868C8), (igMemoryPoolView *)allocator));
}

igMetaObject *igContextExtInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextExtInfo_EnsureRegistered();
    return g_igContextExtInfo_metaObject[0];
}

int igContextExtInfo_GetVTable(void) {
    igContextExtInfo info;
    int vtable;
    int *nameSlot;
    igObject *metaSlot;
    int *text;
    int *header;
    int count;

    igObject_InitHeader((igObject *)&info);
    info._vtable = (int)&g_igContextExtInfo_vtable[0];
    metaSlot = (igObject *)&info._pMeta;
    *(int *)metaSlot = 0;
    nameSlot = &info._pName;
    *(int *)nameSlot = 0;
    vtable = *(int *)((char *)&info + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    info._vtable = (int)&g_igContextExtInfo_vtable[0];
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            count = text[-1] - 1;
            text[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    if (metaSlot != 0) {
        metaSlot = *(igObject **)metaSlot;
        if (metaSlot != 0) {
            metaSlot->_refCount = (int)((int) (metaSlot->_refCount - 1));
            if (((unsigned long long) ((long long)(int) metaSlot->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(metaSlot);
            }
        }
    }
    return vtable;
}

void igContextExtInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExtInfo_Register);
}

void igContextExtInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igContextExtInfo_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igContextExtInfo_GetMetaObjectFunction,
        igContextExtInfo_className,
        0x14,
        igContextExtInfo_GetVTable,
        igContextExtInfo_InitFields,
        0,
        (igMetaObjectCallback *)g_igContextExtInfo_callbackList
    );
}

void igContextExtInfo_GetMetaObjectFunction(void) {
    igContextExtInfo_GetMetaObject();
}

void igContextExtInfo_InitFields(void) {
    int base;
    void *nameField;
    void *vendorNameField;
    void *metaField;
    void *meta;

    meta = (void *)g_igContextExtInfo_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igContextExtInfo_ctorTable[0], 3);
    metaField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)metaField)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    nameField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    igStringMetaField_SetDefaultText((int *)nameField, 0);
    ((igStringMetaField *)nameField)->_destruct = 1;
    vendorNameField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igMemoryRefMetaField *)vendorNameField)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igContextExtInfo_fieldTable[0], (igMetaField ***)&g_igContextExtInfo_fieldDescriptors[0], &g_igContextExtInfo_fieldOffsets[0], base);
}

