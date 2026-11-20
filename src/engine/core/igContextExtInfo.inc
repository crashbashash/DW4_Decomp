igMetaObject *g_igContextExtInfo_metaObject;
igMetaField *g_igContextExtInfo_pMetaMetaField;
igMetaField *g_igContextExtInfo_pNameMetaField;
igMetaField *g_igContextExtInfo_pVendorNameMetaField;

void * igContextExtInfo_Create(int allocator) {
    igContextExtInfo_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igContextExtInfo_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igContextExtInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextExtInfo_EnsureRegistered();
    return g_igContextExtInfo_metaObject;
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
    vtable = *(int *)((char *)&info + g_objectSystem->vtableProbeOffset);
    info._vtable = (int)&g_igContextExtInfo_vtable[0];
    if (nameSlot != 0) {
        text = *(int **)nameSlot;
        if (text != 0) {
            header = text - 2;
            count = text[-1] - 1;
            text[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
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
    igMetaObject_RunStaticInit(igContextExtInfo_Register);
}

static igMetaObjectCallback g_igContextExtInfo_callbackList[] = { igMetaObject_EnsureRegistered, 0 };

CallbackArray *igContextExtInfo_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igContextExtInfo_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igContextExtInfo_GetMetaObjectFunction,
        "igContextExtInfo",
        0x14,
        igContextExtInfo_GetVTable,
        igContextExtInfo_InitFields,
        0,
        g_igContextExtInfo_callbackList
    );
}

void igContextExtInfo_GetMetaObjectFunction(void) {
    igContextExtInfo_GetMetaObject();
}

static FieldFactory g_igContextExtInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
};
static const char *g_igContextExtInfo_fieldTable[] = {
    "_pMeta",
    "_pName",
    "_pVendorName",
};
static igMetaField **g_igContextExtInfo_fieldDescriptors[] = {
    &g_igContextExtInfo_pMetaMetaField,
    &g_igContextExtInfo_pNameMetaField,
    &g_igContextExtInfo_pVendorNameMetaField,
};
static int g_igContextExtInfo_fieldOffsets[] = {
    8,
    12,
    16,
};

void igContextExtInfo_InitFields(void) {
    int base;
    void *nameField;
    void *vendorNameField;
    void *metaField;
    void *meta;

    meta = (void *)g_igContextExtInfo_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igContextExtInfo_ctorTable, 3);
    metaField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)metaField)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    nameField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    igStringMetaField_SetDefaultText((igMetaField *)nameField, 0);
    ((igStringMetaField *)nameField)->_destruct = 1;
    vendorNameField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igMemoryRefMetaField *)vendorNameField)->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    igMetaObject_NameFields((igMetaObject *)meta, g_igContextExtInfo_fieldTable, g_igContextExtInfo_fieldDescriptors, g_igContextExtInfo_fieldOffsets, base);
}

