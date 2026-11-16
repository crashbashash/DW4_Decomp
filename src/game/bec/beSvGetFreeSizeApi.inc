igMetaObject *g_beSvGetFreeSizeApi_metaObject;
igMetaField *g_beSvGetFreeSizeApi_memNeedMetaField;
igMetaField *g_beSvGetFreeSizeApi_memCapaMetaField;
igMetaField *g_beSvGetFreeSizeApi_fileCapaMetaField;

void beSvGetFreeSizeApi_Create(int allocator) {
    beSvGetFreeSizeApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588200, allocator);
}

igMetaObject *beSvGetFreeSizeApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvGetFreeSizeApi_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beSvGetFreeSizeApi_EnsureRegistered();
    return g_beSvGetFreeSizeApi_metaObject;
}

int beSvGetFreeSizeApi_GetVTable(void) {
    beSvGetFreeSizeApi obj;
    int vtable;
    igObject **iconWorkSlot;
    igObject **mountWorkSlot;
    igObject **imageWorkSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    imageWorkSlot = (igObject **)&obj._imageWork;
    *imageWorkSlot = 0;
    mountWorkSlot = (igObject **)&obj._mountWork;
    *mountWorkSlot = 0;
    iconWorkSlot = (igObject **)&obj._iconWork;
    *iconWorkSlot = 0;
    obj._vtable = (int)&g_beSvGetFreeSizeApi_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beSaveApi_vtable[0];
    igObjectRef_Release(iconWorkSlot);
    igObjectRef_Release(mountWorkSlot);
    igObjectRef_Release(imageWorkSlot);
    return vtable;
}

void beSvGetFreeSizeApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvGetFreeSizeApi_Register);
}

void *beSvGetFreeSizeApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvGetFreeSizeApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvGetFreeSizeApi_GetMetaObjectFunction,
        "beSvGetFreeSizeApi",
        0x58, /* instance size */
        beSvGetFreeSizeApi_GetVTable,
        beSvGetFreeSizeApi_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvGetFreeSizeApi_GetMetaObjectFunction(void)
{
    beSvGetFreeSizeApi_GetMetaObject();
}

static FieldFactory g_beSvGetFreeSizeApi_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beSvGetFreeSizeApi_fieldTable[] = {
    "_memNeed",
    "_memCapa",
    "_fileCapa",
};
static igMetaField **g_beSvGetFreeSizeApi_fieldHandles[] = {
    &g_beSvGetFreeSizeApi_memNeedMetaField,
    &g_beSvGetFreeSizeApi_memCapaMetaField,
    &g_beSvGetFreeSizeApi_fileCapaMetaField,
};
static int g_beSvGetFreeSizeApi_fieldOffsets[] = {
    64,
    68,
    72,
};

void beSvGetFreeSizeApi_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beSvGetFreeSizeApi_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvGetFreeSizeApi_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beSvGetFreeSizeApi_fieldTable, g_beSvGetFreeSizeApi_fieldHandles, g_beSvGetFreeSizeApi_fieldOffsets, base);
}

