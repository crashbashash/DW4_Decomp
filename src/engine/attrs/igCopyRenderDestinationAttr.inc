igMetaEnum *g_igCopyRenderDestinationAttr_copyTypeMetaEnum;
igMetaObject *g_igCopyRenderDestinationAttr_metaObject;
igMetaField *g_igCopyRenderDestinationAttr_copyTypeMetaField;
igMetaField *g_igCopyRenderDestinationAttr_pRDAttrMetaField;
igMetaField *g_igCopyRenderDestinationAttr_pImageMetaField;
igMetaField *g_igCopyRenderDestinationAttr_pTextureAttrMetaField;
igMetaField *g_igCopyRenderDestinationAttr_sourceXMetaField;
igMetaField *g_igCopyRenderDestinationAttr_sourceYMetaField;
igMetaField *g_igCopyRenderDestinationAttr_destinationXMetaField;
igMetaField *g_igCopyRenderDestinationAttr_destinationYMetaField;
igMetaField *g_igCopyRenderDestinationAttr_sizeWMetaField;
igMetaField *g_igCopyRenderDestinationAttr_sizeHMetaField;

static const char *g_igCopyRenderDestinationAttr_copyTypeNames[] = {
    "NOT_SET",
    "FROM_RENDERDESTINATION_TO_TEXTURE",
    "FROM_RENDERDESTINATION_TO_MEMORY",
    "FROM_RENDERDESTINATION_DEPTH_TO_TEXTURE",
    "FROM_RENDERDESTINATION_DEPTH_TO_MEMORY",
};
static int g_igCopyRenderDestinationAttr_copyTypeValues[] = {
    0,
    1,
    2,
    3,
    4,
};

igMetaEnum *igCopyRenderDestinationAttr_GetCopyTypeMetaEnum(void) {
    if (g_igCopyRenderDestinationAttr_copyTypeMetaEnum == 0) {
        g_igCopyRenderDestinationAttr_copyTypeMetaEnum = igMetaEnum_Create("CopyType", g_igCopyRenderDestinationAttr_copyTypeNames, g_igCopyRenderDestinationAttr_copyTypeValues, 5);
    }
    return g_igCopyRenderDestinationAttr_copyTypeMetaEnum;
}

igMetaObject *igCopyRenderDestinationAttr_GetOrCreateMetaObject(void) {
    if (g_igCopyRenderDestinationAttr_metaObject == 0) {
        g_igCopyRenderDestinationAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCopyRenderDestinationAttr_metaObject;
}

igMetaObject *igCopyRenderDestinationAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igCopyRenderDestinationAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCopyRenderDestinationAttr_EnsureRegistered();
    return g_igCopyRenderDestinationAttr_metaObject;
}

int igCopyRenderDestinationAttr_GetVTable(void) {
    union U_1389f0 u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igCopyRenderDestinationAttr_vtable[0];
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[20];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igCopyRenderDestinationAttr_vtable[0];
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
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q2);
            }
        }
    }
    return temp_s0;
}

void igCopyRenderDestinationAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCopyRenderDestinationAttr_Register);
}

static igMetaObjectCallback g_igCopyRenderDestinationAttr_callbackList[] = { igRenderDestinationAttr_EnsureRegistered, igImage_EnsureRegistered, igTextureAttr_EnsureRegistered, 0 };

CallbackArray *igCopyRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCopyRenderDestinationAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igCopyRenderDestinationAttr_GetMetaObjectFunction,
        "igCopyRenderDestinationAttr",
        0x34, /* instance size */
        igCopyRenderDestinationAttr_GetVTable,
        &igCopyRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igCopyRenderDestinationAttr_callbackList /* callback list */
    );
}

void igCopyRenderDestinationAttr_GetMetaObjectFunction(void) {
    igCopyRenderDestinationAttr_GetMetaObject();
}

static FieldFactory g_igCopyRenderDestinationAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igCopyRenderDestinationAttr_fieldTable[] = {
    "_copyType",
    "_pRDAttr",
    "_pImage",
    "_pTextureAttr",
    "_sourceX",
    "_sourceY",
    "_destinationX",
    "_destinationY",
    "_sizeW",
    "_sizeH",
};
static igMetaField **g_igCopyRenderDestinationAttr_fieldHandles[] = {
    &g_igCopyRenderDestinationAttr_copyTypeMetaField,
    &g_igCopyRenderDestinationAttr_pRDAttrMetaField,
    &g_igCopyRenderDestinationAttr_pImageMetaField,
    &g_igCopyRenderDestinationAttr_pTextureAttrMetaField,
    &g_igCopyRenderDestinationAttr_sourceXMetaField,
    &g_igCopyRenderDestinationAttr_sourceYMetaField,
    &g_igCopyRenderDestinationAttr_destinationXMetaField,
    &g_igCopyRenderDestinationAttr_destinationYMetaField,
    &g_igCopyRenderDestinationAttr_sizeWMetaField,
    &g_igCopyRenderDestinationAttr_sizeHMetaField,
};
static int g_igCopyRenderDestinationAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
};

void igCopyRenderDestinationAttr_InitFields(void) {
    int base;
    void *field;
    void *field2;
    void *field3;
    void *field4;
    igMetaObject *meta;

    meta = g_igCopyRenderDestinationAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igCopyRenderDestinationAttr_ctorTable, 0xA);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, 0);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)(&igCopyRenderDestinationAttr_GetCopyTypeMetaEnum);
    field4 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field4)->_metaObject = (int)igRenderDestinationAttr_GetOrCreateMetaObject();
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field3)->_metaObject = (int)igImage_GetOrCreateMetaObject();
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igTextureAttr_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igCopyRenderDestinationAttr_fieldTable, g_igCopyRenderDestinationAttr_fieldHandles, g_igCopyRenderDestinationAttr_fieldOffsets, base);
}

