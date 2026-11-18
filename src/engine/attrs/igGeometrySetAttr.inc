igMetaEnum *g_igGeometrySetAttr_attrFlagsMetaEnum;
igMetaObject *g_igGeometrySetAttr_metaObject;
igMetaField *g_igGeometrySetAttr_vcMetaField;
igMetaField *g_igGeometrySetAttr_renderListHandleMetaField;
igMetaField *g_igGeometrySetAttr_geometryAttrListMetaField;
igMetaField *g_igGeometrySetAttr_renderListStateMetaField;
igMetaField *g_igGeometrySetAttr_drawStateMetaField;

static const char *g_igGeometrySetAttr_attrFlagsNames[] = {
    "IMMEDIATE",
    "USE_RENDER_LIST",
    "USE_RENDER_LIST_DELETE_ORIGINAL",
};
static int g_igGeometrySetAttr_attrFlagsValues[] = {
    0,
    1,
    2,
};

igMetaEnum *igGeometrySetAttr_GetAttrFlagsMetaEnum(void) {
    if (g_igGeometrySetAttr_attrFlagsMetaEnum == 0) {
        g_igGeometrySetAttr_attrFlagsMetaEnum = igMetaEnum_Create("ATTR_FLAGS", g_igGeometrySetAttr_attrFlagsNames, g_igGeometrySetAttr_attrFlagsValues, 3);
    }
    return g_igGeometrySetAttr_attrFlagsMetaEnum;
}

igMetaObject *igGeometrySetAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometrySetAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometrySetAttr_EnsureRegistered();
    return g_igGeometrySetAttr_metaObject;
}

int igGeometrySetAttr_GetVTable(void) {
    union U_136d30 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igGeometrySetAttr_vtable[0];
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igGeometrySetAttr_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
            }
        }
    }
    return temp_s0;
}

void **FUN_00136e10(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igGeometrySetAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometrySetAttr_Register);
}

static igMetaObjectCallback g_igGeometrySetAttr_callbackList[] = { igVisualContext_EnsureRegistered, igGeometryAttrList_EnsureRegistered, 0 };

CallbackArray *igGeometrySetAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGeometrySetAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igGeometrySetAttr_GetMetaObjectFunction,
        "igGeometrySetAttr",
        0x20, /* instance size */
        igGeometrySetAttr_GetVTable,
        &igGeometrySetAttr_InitFields,
        0, /* extra callback item */
        g_igGeometrySetAttr_callbackList /* callback list */
    );
}

void igGeometrySetAttr_GetMetaObjectFunction(void) {
    igGeometrySetAttr_GetMetaObject();
}

static FieldFactory g_igGeometrySetAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igGeometrySetAttr_fieldTable[] = {
    "_vc",
    "_renderListHandle",
    "_geometryAttrList",
    "_renderListState",
    "_drawState",
};
static igMetaField **g_igGeometrySetAttr_fieldHandles[] = {
    &g_igGeometrySetAttr_vcMetaField,
    &g_igGeometrySetAttr_renderListHandleMetaField,
    &g_igGeometrySetAttr_geometryAttrListMetaField,
    &g_igGeometrySetAttr_renderListStateMetaField,
    &g_igGeometrySetAttr_drawStateMetaField,
};
static int g_igGeometrySetAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
};

void igGeometrySetAttr_InitFields(void) {
    int base;
    struct F_136f30 *field;
    struct F_136f30 *field2;
    struct F_136f30 *field3;
    struct F_136f30 *field4;
    igMetaObject *meta;

    meta = g_igGeometrySetAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igGeometrySetAttr_ctorTable, 5);
    field = (struct F_136f30 *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    ((igMetaField *)field)->_persistent = 0;
    ((igMetaField *)field)->_deepCopyMethod = 1;
    ((igMetaField *)field)->_shallowCopyMethod = 1;
    ((igMetaField *)field)->_isAlikeShallowMethod = 3;
    field3 = (struct F_136f30 *)(igMetaObject_GetFieldAt(meta, base + 1));
    igIntMetaField_SetDefault((igMetaField *)field3, -1);
    ((igMetaField *)field3)->_persistent = 0;
    ((igMetaField *)field3)->_deepCopyMethod = 4;
    ((igMetaField *)field3)->_shallowCopyMethod = 4;
    ((igMetaField *)field3)->_isAlikeShallowMethod = 3;
    field2 = (struct F_136f30 *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igGeometryAttrList_GetOrCreateMetaObject();
    field4 = (struct F_136f30 *)(igMetaObject_GetFieldAt(meta, base + 3));
    igEnumMetaField_SetDefaultValue((igMetaField *)field4, 0);
    ((igMetaField *)field4)->_persistent = 0;
    ((igEnumMetaField *)field4)->_getMetaEnumFunction = (int)&igGeometrySetAttr_GetAttrFlagsMetaEnum;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 4), 1);
    igMetaObject_NameFields(meta, g_igGeometrySetAttr_fieldTable, g_igGeometrySetAttr_fieldHandles, g_igGeometrySetAttr_fieldOffsets, base);
}

