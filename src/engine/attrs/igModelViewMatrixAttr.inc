igMetaObject *g_igModelViewMatrixAttr_metaObject;
igMetaField *g_igModelViewMatrixAttr_mMetaField;

igModelViewMatrixAttr *igModelViewMatrixAttr_CreateInstance(int allocator) {
    igModelViewMatrixAttr_EnsureRegistered();
    return (igModelViewMatrixAttr *)igMetaObject_CreateInstance(g_igModelViewMatrixAttr_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igModelViewMatrixAttr_GetOrCreateMetaObject(void) {
    if (g_igModelViewMatrixAttr_metaObject == 0) {
        g_igModelViewMatrixAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igModelViewMatrixAttr_metaObject;
}

igMetaObject *igModelViewMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igModelViewMatrixAttr_EnsureRegistered();
    return g_igModelViewMatrixAttr_metaObject;
}

int igModelViewMatrixAttr_GetVTable(void) {
    struct Obj_135790 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igModelViewMatrixAttr_vtable[0];
    igMatrix44f_SetIdentity((float *)&obj.pad[8]);
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igModelViewMatrixAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixAttr_Register);
}

CallbackArray *igModelViewMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();  /* Set-once latch run before every registration of this family. */
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igModelViewMatrixAttr_GetMetaObjectFunction,
        "igModelViewMatrixAttr",
        0x4C,                                              /* instance size (the reflected struct is shorter: igMatrix44f is reflected as one int) */
        igModelViewMatrixAttr_GetVTable,
        &igModelViewMatrixAttr_InitFields,
        FUN_00135980,                                      /* static-initializer callback item (appended on fresh configuration) */
        0                                                  /* 0-terminated dependency-callback list */
    );
}

void igModelViewMatrixAttr_GetMetaObjectFunction(void) {
    igModelViewMatrixAttr_GetMetaObject();
}

static FieldFactory g_igModelViewMatrixAttr_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
};
static const char *g_igModelViewMatrixAttr_fieldTable[] = {
    "_m",
};
static igMetaField **g_igModelViewMatrixAttr_fieldHandles[] = {
    &g_igModelViewMatrixAttr_mMetaField,
};
static int g_igModelViewMatrixAttr_fieldOffsets[] = {
    12,
};

void igModelViewMatrixAttr_InitFields(void) {
    int base;
    int field;
    igMetaObject *meta;
    struct M o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    meta = g_igModelViewMatrixAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igModelViewMatrixAttr_ctorTable, 1);
    field = (int)igMetaObject_GetFieldAt(meta, base);
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    igMatrix44f_FromRows((float *)&o1, (igVec4f *)&o2, (igVec4f *)&o3, (igVec4f *)&o4, (igVec4f *)&o5);
    FUN_0018c640(field, &o1);
    igMetaObject_NameFields(meta, g_igModelViewMatrixAttr_fieldTable, g_igModelViewMatrixAttr_fieldHandles, g_igModelViewMatrixAttr_fieldOffsets, base);
    igMetaObject_AddExitCallback((int)&thunk_igModelViewMatrixAttr_UserUnregister);
}

void FUN_00135980(void) {
    FUN_0013f670();
}

void thunk_igModelViewMatrixAttr_UserUnregister(void) {
    igModelViewMatrixAttr_UserUnregister();
}

