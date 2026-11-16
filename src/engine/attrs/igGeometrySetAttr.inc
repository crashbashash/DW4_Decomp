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

igMetaEnum *FUN_00136c80(void) {
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

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igGeometrySetAttr_vtable[0];
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[20];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igGeometrySetAttr_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
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
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void igGeometrySetAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometrySetAttr_Register);
}

static igMetaObjectCallback g_igGeometrySetAttr_callbackList[] = { igVisualContext_EnsureRegistered, igGeometryAttrList_EnsureRegistered, 0 };

void igGeometrySetAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGeometrySetAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometrySetAttr_GetMetaObject,
        "igGeometrySetAttr",
        0x20, /* instance size */
        igGeometrySetAttr_GetVTable,
        &igGeometrySetAttr_InitFields,
        0, /* extra callback item */
        g_igGeometrySetAttr_callbackList /* callback list */
    );
}

void thunk_igGeometrySetAttr_GetMetaObject(void) {
    igGeometrySetAttr_GetMetaObject();
}

static FieldFactory g_igGeometrySetAttr_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igBoolMetaField_Create,
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
    int temp_s0;
    struct F_136f30 *temp_s2;
    struct F_136f30 *temp_s2_2;
    struct F_136f30 *temp_v0;
    struct F_136f30 *temp_v0_2;
    igMetaObject *temp_s1;

    temp_s1 = g_igGeometrySetAttr_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igGeometrySetAttr_ctorTable, 5);
    temp_s2 = (struct F_136f30 *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    temp_s2->f56 = igVisualContext_GetOrCreateMetaObject();
    temp_s2->f38 = 0;
    temp_s2->f40 = 1;
    temp_s2->f39 = 1;
    temp_s2->f44 = 3;
    temp_v0 = (struct F_136f30 *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    igIntMetaField_SetDefault(temp_v0, -1);
    temp_v0->f38 = 0;
    temp_v0->f40 = 4;
    temp_v0->f39 = 4;
    temp_v0->f44 = 3;
    temp_s2_2 = (struct F_136f30 *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    temp_s2_2->f56 = (int)igGeometryAttrList_GetOrCreateMetaObject();
    temp_v0_2 = (struct F_136f30 *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    igEnumMetaField_SetDefaultValue(temp_v0_2, 0);
    temp_v0_2->f38 = 0;
    temp_v0_2->f52 = (int)(&FUN_00136c80);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1);
    igMetaObject_NameFields(temp_s1, g_igGeometrySetAttr_fieldTable, g_igGeometrySetAttr_fieldHandles, g_igGeometrySetAttr_fieldOffsets, temp_s0);
}

