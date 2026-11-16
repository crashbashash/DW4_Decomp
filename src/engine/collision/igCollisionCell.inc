igMetaObject *g_igCollisionCell_metaObject;
igMetaField *g_igCollisionCell_objectsMetaField;
igMetaField *g_igCollisionCell_gridMetaField;
igMetaField *g_igCollisionCell_boxMetaField;
igMetaField *g_igCollisionCell_staticCountMetaField;
igMetaField *g_igCollisionCell_priorityMetaField;
igMetaField *g_igCollisionCell_activeMetaField;

igCollisionCell *FUN_0023a6e0(int arg0) {
    FUN_0023a850();
    return (igCollisionCell *)igMetaObject_CreateInstance(g_igCollisionCell_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igCollisionCell_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCell_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a850();
    return g_igCollisionCell_metaObject;
}

int igCollisionCell_GetVTable(void) {
    Obj_23a770 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCollisionCell_vtable[0];
    obj.r1 = 0;
    obj.r3 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    obj.vt = &g_igCollisionCell_vtable[0];
    obj.rel3();
    obj.rel1();
    return r;
}

void FUN_0023a850(void)
{
    igMetaObject_RunStaticInit(igCollisionCell_Register);
}

static igMetaObjectCallback g_igCollisionCell_callbackList[] = { FUN_00239b20, FUN_0023a340, igAABox_EnsureRegistered, 0 };

CallbackArray *igCollisionCell_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionCell_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCollisionCell_GetMetaObject,
        "igCollisionCell",
        0x20, /* instance size */
        igCollisionCell_GetVTable,
        &igCollisionCell_InitFields,
        0, /* extra callback item */
        g_igCollisionCell_callbackList /* callback list */
    );
}

void thunk_igCollisionCell_GetMetaObject(void) {
    igCollisionCell_GetMetaObject();
}

static FieldFactory g_igCollisionCell_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igCollisionCell_fieldTable[] = {
    "_objects",
    "_grid",
    "_box",
    "_staticCount",
    "_priority",
    "_active",
};
static igMetaField **g_igCollisionCell_fieldHandles[] = {
    &g_igCollisionCell_objectsMetaField,
    &g_igCollisionCell_gridMetaField,
    &g_igCollisionCell_boxMetaField,
    &g_igCollisionCell_staticCountMetaField,
    &g_igCollisionCell_priorityMetaField,
    &g_igCollisionCell_activeMetaField,
};
static int g_igCollisionCell_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void igCollisionCell_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igCollisionCell_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCollisionCell_ctorTable, 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00239a40();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0023a080();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igAABox_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCollisionCell_fieldTable, g_igCollisionCell_fieldHandles, g_igCollisionCell_fieldOffsets, temp_s2);
}

