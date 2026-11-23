igMetaObject *g_igTransformRecorder_metaObject;
igMetaField *g_igTransformRecorder_mMetaField;
igMetaField *g_igTransformRecorder_mvmMetaField;

igMetaObject *igTransformRecorder_GetOrCreateMetaObject(void) {
    if (g_igTransformRecorder_metaObject == 0) {
        g_igTransformRecorder_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTransformRecorder_metaObject;
}

igMetaObject *igTransformRecorder_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformRecorder_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransformRecorder_EnsureRegistered();
    return g_igTransformRecorder_metaObject;
}

int igTransformRecorder_GetVTable(void) { struct Obj_195860 o; int *p = (int *)&o; int t;
 igObject_InitHeader((igObject *)(struct Obj_195860 *)p); o.vt = &g_igTransformRecorder_vtable[0]; o.f8 = 0; o.f12 = 0; o.f16 = 0; o.f28 = 0;
 igMatrix44f_SetIdentity((float *)o.sub1); igMatrix44f_SetIdentity((float *)(p + 24));
 t = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
 o.vt = &g_igTransformRecorder_vtable[0]; igGroup_Destroy((igGroup *)((struct Obj_195860 *)p), 0); return t; }

void igTransformRecorder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransformRecorder_Register);
}

CallbackArray *igTransformRecorder_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransformRecorder_metaObject,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        igTransformRecorder_GetMetaObjectFunction,
        "igTransformRecorder",
        0xA0, /* instance size */
        igTransformRecorder_GetVTable,
        &igTransformRecorder_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTransformRecorder_GetMetaObjectFunction(void) {
    igTransformRecorder_GetMetaObject();
}

static FieldFactory g_igTransformRecorder_ctorTable[] = {
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
};
static const char *g_igTransformRecorder_fieldTable[] = {
    "_m",
    "_mvm",
};
static igMetaField **g_igTransformRecorder_fieldHandles[] = {
    &g_igTransformRecorder_mMetaField,
    &g_igTransformRecorder_mvmMetaField,
};
static int g_igTransformRecorder_fieldOffsets[] = {
    32,
    96,
};

void igTransformRecorder_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_igTransformRecorder_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igTransformRecorder_ctorTable, 2);
    igMetaObject_NameFields((igMetaObject *)meta, g_igTransformRecorder_fieldTable, g_igTransformRecorder_fieldHandles, g_igTransformRecorder_fieldOffsets, base);
}

