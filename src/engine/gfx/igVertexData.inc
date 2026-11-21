igMetaObject *g_igVertexData_metaObject;
igMetaField *g_igVertexData_dataMetaField;
igMetaField *g_igVertexData_componentTypeMetaField;
igMetaField *g_igVertexData_componentIndexMetaField;
igMetaField *g_igVertexData_componentSizeMetaField;
igMetaField *g_igVertexData_userIDMetaField;
igMetaField *g_igVertexData_componentFractionMetaField;

static const char *g_igVertexData_vertexComponentTypeNames[] = {
    "IG_VERTEX_COMPONENT_NONE", "IG_VERTEX_COMPONENT_POSITION", "IG_VERTEX_COMPONENT_COLOR", "IG_VERTEX_COMPONENT_NORMAL",
    "IG_VERTEX_COMPONENT_TEXCOORD", "IG_VERTEX_COMPONENT_WEIGHT", "IG_VERTEX_COMPONENT_INDEX", "IG_VERTEX_COMPONENT_BINORMAL",
    "IG_VERTEX_COMPONENT_TANGENT", "IG_VERTEX_COMPONENT_SIZE", "IG_VERTEX_COMPONENT_CUSTOM",
};
static int g_igVertexData_vertexComponentTypeValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xa,
};
igMetaEnum *g_igVertexData_vertexComponentTypeMetaEnum;

int IG_VERTEX_COMPONENT_TYPE_GetMetaEnum(void) {
    if (g_igVertexData_vertexComponentTypeMetaEnum == 0) {
        g_igVertexData_vertexComponentTypeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_VERTEX_COMPONENT_TYPE", g_igVertexData_vertexComponentTypeNames, g_igVertexData_vertexComponentTypeValues, 11);
    }
    return (int)g_igVertexData_vertexComponentTypeMetaEnum;
}

int igVertexData_Create(int arg0) {
    igVertexData_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igVertexData_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igVertexData_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexData_EnsureRegistered();
    return g_igVertexData_metaObject;
}

int igVertexData_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_igVertexData_vtable[0];
    q0 = (S_ref *)&u.b[12];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igVertexData_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igVertexData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexData_Register);
}

static igMetaObjectCallback g_igVertexData_callbackList[] = { Gap::Core::igDataList::arkRegister, 0 };

CallbackArray *igVertexData_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexData_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        igVertexData_GetMetaObjectFunction,
        "igVertexData",
        0x24, /* instance size */
        igVertexData_GetVTable,
        &igVertexData_InitFields,
        0, /* extra callback item */
        g_igVertexData_callbackList /* callback list */
    );
}

void igVertexData_GetMetaObjectFunction(void) {
    igVertexData_GetMetaObject();
}

static FieldFactory g_igVertexData_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igVertexData_fieldTable[] = {
    "_data",
    "_componentType",
    "_componentIndex",
    "_componentSize",
    "_userID",
    "_componentFraction",
};
static igMetaField **g_igVertexData_fieldHandles[] = {
    &g_igVertexData_dataMetaField,
    &g_igVertexData_componentTypeMetaField,
    &g_igVertexData_componentIndexMetaField,
    &g_igVertexData_componentSizeMetaField,
    &g_igVertexData_userIDMetaField,
    &g_igVertexData_componentFractionMetaField,
};
static int g_igVertexData_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
};

void igVertexData_InitFields(void) {
    int fieldStart;
    void *componentTypeField;
    void *dataField;
    igMetaObject *meta;

    meta = g_igVertexData_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexData_ctorTable, 6);
    dataField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)dataField)->_metaObject = (int)igDataList_GetOrCreateMetaObject();
    componentTypeField = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 1));
    ((Gap::Core::igEnumMetaField *)componentTypeField)->setDefault(0);
    ((igEnumMetaField *)componentTypeField)->_getMetaEnumFunction = (int)(IG_VERTEX_COMPONENT_TYPE_GetMetaEnum);
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt(meta, fieldStart + 3)))->setDefault(1);
    igMetaObject_NameFields(meta, g_igVertexData_fieldTable, g_igVertexData_fieldHandles, g_igVertexData_fieldOffsets, fieldStart);
}

