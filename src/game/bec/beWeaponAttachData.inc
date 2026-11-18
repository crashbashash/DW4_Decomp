igMetaObject *g_beWeaponAttachData_metaObject;
igMetaField *g_beWeaponAttachData_boneSelectListMetaField;
igMetaField *g_beWeaponAttachData_appearanceListListMetaField;

beWeaponAttachData *beWeaponAttachData_Create(int allocator) {
    beWeaponAttachData_EnsureRegistered();
    return (beWeaponAttachData *)igMetaObject_CreateInstance(g_beWeaponAttachData_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beWeaponAttachData_GetMetaObject(void) {
    igMetaObject *g = g_beWeaponAttachData_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beWeaponAttachData_EnsureRegistered();
    return g_beWeaponAttachData_metaObject;
}

int beWeaponAttachData_GetVTable(void) {
    beWeaponAttachData obj;
    int vtable;
    igObject **appearanceListListSlot;
    igObject **boneSelectListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beWeaponAttachData_vtable[0];
    boneSelectListSlot = (igObject **)&obj._boneSelectList;
    *boneSelectListSlot = 0;
    appearanceListListSlot = (igObject **)&obj._appearanceListList;
    *appearanceListListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beWeaponAttachData_vtable[0];
    igObjectRef_Release(appearanceListListSlot);
    igObjectRef_Release(boneSelectListSlot);
    return vtable;
}

void beWeaponAttachData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeaponAttachData_Register);
}

static igMetaObjectCallback g_beWeaponAttachData_callbackList[] = { igModelViewMatrixBoneSelectListBec_EnsureRegistered, igAppearanceListList_EnsureRegistered, 0 };

CallbackArray *beWeaponAttachData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeaponAttachData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWeaponAttachData_GetMetaObjectFunction,
        "beWeaponAttachData",
        0x10, /* instance size */
        beWeaponAttachData_GetVTable,
        beWeaponAttachData_InitFields,
        0, /* extra callback item */
        g_beWeaponAttachData_callbackList /* callback list */
    );
}

void beWeaponAttachData_GetMetaObjectFunction(void)
{
    beWeaponAttachData_GetMetaObject();
}

static FieldFactory g_beWeaponAttachData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beWeaponAttachData_fieldTable[] = {
    "_boneSelectList",
    "_appearanceListList",
};
static igMetaField **g_beWeaponAttachData_fieldHandles[] = {
    &g_beWeaponAttachData_boneSelectListMetaField,
    &g_beWeaponAttachData_appearanceListListMetaField,
};
static int g_beWeaponAttachData_fieldOffsets[] = {
    8,
    12,
};

void beWeaponAttachData_InitFields(void) {
    int base;
    void *appearanceListList;
    void *boneSelectList;
    igMetaObject *meta;

    meta = g_beWeaponAttachData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWeaponAttachData_ctorTable, 2);
    boneSelectList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)boneSelectList)->_metaObject = (int)igModelViewMatrixBoneSelectListBec_GetOrCreateMetaObject();
    ((igRefMetaField *)boneSelectList)->_construct = 1;
    appearanceListList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)appearanceListList)->_metaObject = (int)igAppearanceListList_GetOrCreateMetaObject();
    ((igRefMetaField *)appearanceListList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beWeaponAttachData_fieldTable, g_beWeaponAttachData_fieldHandles, g_beWeaponAttachData_fieldOffsets, base);
}

