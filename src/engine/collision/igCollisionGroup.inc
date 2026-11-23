igMetaObject *g_igCollisionGroup_metaObject;
igMetaField *g_igCollisionGroup_transformMetaField;
igMetaField *g_igCollisionGroup_positionMetaField;
igMetaField *g_igCollisionGroup_lastPositionMetaField;
igMetaField *g_igCollisionGroup_collisionPositionMetaField;
igMetaField *g_igCollisionGroup_directionMetaField;
igMetaField *g_igCollisionGroup_radiusMetaField;
igMetaField *g_igCollisionGroup_timeMetaField;
igMetaField *g_igCollisionGroup_collisionCellsMetaField;

igMetaObject *igCollisionGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroup_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCollisionGroup_EnsureRegistered();
    return g_igCollisionGroup_metaObject;
}

int igCollisionGroup_GetVTable(void) {
    union U_239c00 u;
    int temp_s0;
    int *p;

    igObject_InitHeader((igObject *)u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[28] = 0;
    u.vt = (int)&g_igCollisionGroup_vtable[0];
    p = (int *)&u.b[32];
    *p = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igCollisionGroup_vtable[0];
    igSmartPointer_igTransform_Destruct((igSmartPointer<igObject> *)p, -1);
    igGroup_Destroy((igGroup *)u.b, 0);
    return temp_s0;
}

void igCollisionGroup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCollisionGroup_Register);
}

static igMetaObjectCallback g_igCollisionGroup_callbackList[] = { igTransform_EnsureRegistered, 0 };

CallbackArray *igCollisionGroup_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionGroup_metaObject,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        igCollisionGroup_GetMetaObjectFunction,
        "igCollisionGroup",
        0x60, /* instance size */
        igCollisionGroup_GetVTable,
        &igCollisionGroup_InitFields,
        0, /* extra callback item */
        g_igCollisionGroup_callbackList /* callback list */
    );
}

void igCollisionGroup_GetMetaObjectFunction(void) {
    igCollisionGroup_GetMetaObject();
}

static FieldFactory g_igCollisionGroup_ctorTable[] = {
    igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igCollisionGroup_fieldTable[] = {
    "_transform",
    "_position",
    "_lastPosition",
    "_collisionPosition",
    "_direction",
    "_radius",
    "_time",
    "_collisionCells",
};
static igMetaField **g_igCollisionGroup_fieldHandles[] = {
    &g_igCollisionGroup_transformMetaField,
    &g_igCollisionGroup_positionMetaField,
    &g_igCollisionGroup_lastPositionMetaField,
    &g_igCollisionGroup_collisionPositionMetaField,
    &g_igCollisionGroup_directionMetaField,
    &g_igCollisionGroup_radiusMetaField,
    &g_igCollisionGroup_timeMetaField,
    &g_igCollisionGroup_collisionCellsMetaField,
};
static int g_igCollisionGroup_fieldOffsets[] = {
    32,
    36,
    48,
    60,
    72,
    84,
    88,
    92,
};

void igCollisionGroup_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igCollisionGroup_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igCollisionGroup_ctorTable, 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)(igTransform_GetOrCreateMetaObject());
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igCollisionGroup_fieldTable, g_igCollisionGroup_fieldHandles, g_igCollisionGroup_fieldOffsets, temp_s2);
}

