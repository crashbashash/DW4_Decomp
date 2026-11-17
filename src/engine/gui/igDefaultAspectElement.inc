static const char *g_igDefaultAspectElement_fitModeNames[] = {
    "LEFT_ALIGN", "CENTER", "RIGHT_ALIGN", "FIT_TO_PARENT",
};
static int g_igDefaultAspectElement_fitModeValues[] = {
    0, 1, 2, 3,
};
igMetaEnum *g_igDefaultAspectElement_fitModeMetaEnum;
igMetaObject *g_igDefaultAspectElement_metaObject;
igMetaField *g_igDefaultAspectElement_geometryElementMetaField;
igMetaField *g_igDefaultAspectElement_colorChangerMetaField;
igMetaField *g_igDefaultAspectElement_transformMetaField;
igMetaField *g_igDefaultAspectElement_fitModeMetaField;
igMetaField *g_igDefaultAspectElement_hMarginMetaField;
igMetaField *g_igDefaultAspectElement_vMarginMetaField;

igMetaEnum *FUN_00451ac0(void) {
    if (g_igDefaultAspectElement_fitModeMetaEnum == 0) {
        g_igDefaultAspectElement_fitModeMetaEnum = igMetaEnum_Create("FIT_MODE", g_igDefaultAspectElement_fitModeNames, g_igDefaultAspectElement_fitModeValues, 4);
    }
    return g_igDefaultAspectElement_fitModeMetaEnum;
}

igMetaObject *igDefaultAspectElement_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspectElement_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspectElement_EnsureRegistered();
    return g_igDefaultAspectElement_metaObject;
}

int igDefaultAspectElement_GetVTable(void) {
    union U_451b70 u;
    int t;
    struct Rc *a;
    int *a1;
    int v0;
    char *c;
    void **q4c;
    void **q48;
    void **q50;
    igObject_InitHeader((igObject *)u.b);
    q48 = &u.p[2];
    q4c = &u.p[3];
    q50 = &u.p[4];
    u.w[0] = (int)(&g_igDefaultAspectElement_vtable[0]);
    *q48 = 0;
    *q4c = 0;
    *q50 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.w[0] = (int)(&g_igDefaultAspectElement_vtable[0]);
    if (q50 != 0) {
        a = (struct Rc *)*q50;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)a);
            }
        }
    }
    if (q4c != 0) {
        a = (struct Rc *)*q4c;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)a);
            }
        }
    }
    if (q48 != 0) {
        a = (struct Rc *)*q48;
        if (a != 0) {
            a->rc = a->rc - 1;
            if ((a->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)a);
            }
        }
    }
    return t;
}

void igDefaultAspectElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspectElement_Register);
}

static igMetaObjectCallback g_igDefaultAspectElement_callbackList[] = { igGeometryElement_EnsureRegistered, igColorChanger_RunStaticInit, igTransform_EnsureRegistered, 0 };

CallbackArray *igDefaultAspectElement_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDefaultAspectElement_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDefaultAspectElement_GetMetaObject,
        "igDefaultAspectElement",
        0x20, /* instance size */
        igDefaultAspectElement_GetVTable,
        &igDefaultAspectElement_InitFields,
        0, /* extra callback item */
        g_igDefaultAspectElement_callbackList /* callback list */
    );
}

void thunk_igDefaultAspectElement_GetMetaObject(void) {
    igDefaultAspectElement_GetMetaObject();
}

static FieldFactory g_igDefaultAspectElement_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_igDefaultAspectElement_fieldTable[] = {
    "_geometryElement",
    "_colorChanger",
    "_transform",
    "_fitMode",
    "_hMargin",
    "_vMargin",
};
static igMetaField **g_igDefaultAspectElement_fieldHandles[] = {
    &g_igDefaultAspectElement_geometryElementMetaField,
    &g_igDefaultAspectElement_colorChangerMetaField,
    &g_igDefaultAspectElement_transformMetaField,
    &g_igDefaultAspectElement_fitModeMetaField,
    &g_igDefaultAspectElement_hMarginMetaField,
    &g_igDefaultAspectElement_vMarginMetaField,
};
static int g_igDefaultAspectElement_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void igDefaultAspectElement_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDefaultAspectElement_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igDefaultAspectElement_ctorTable, 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_004505b0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_004521d0();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2));
    *(int *)((char *)(temp_s1_3) + 56) = (int)igTransform_GetOrCreateMetaObject();
    *(unsigned char *)((char *)(temp_s1_3) + 52) = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0, 0);
    *(int *)((char *)(temp_v0) + 52) = (int)(FUN_00451ac0);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igDefaultAspectElement_fieldTable, g_igDefaultAspectElement_fieldHandles, g_igDefaultAspectElement_fieldOffsets, temp_s2);
}

