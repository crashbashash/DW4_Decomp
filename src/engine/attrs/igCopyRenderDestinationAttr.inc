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

igMetaEnum *FUN_001388f0(void) {
    if (g_igCopyRenderDestinationAttr_copyTypeMetaEnum == 0) {
        g_igCopyRenderDestinationAttr_copyTypeMetaEnum = igMetaEnum_Create("CopyType", g_igCopyRenderDestinationAttr_copyTypeNames, g_igCopyRenderDestinationAttr_copyTypeValues, 5);
    }
    return g_igCopyRenderDestinationAttr_copyTypeMetaEnum;
}

igMetaObject *FUN_00138950(void) {
    if (g_igCopyRenderDestinationAttr_metaObject == 0) {
        g_igCopyRenderDestinationAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igCopyRenderDestinationAttr_vtable[0];
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[20];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igCopyRenderDestinationAttr_vtable[0];
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
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
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

void igCopyRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCopyRenderDestinationAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igCopyRenderDestinationAttr_GetMetaObject,
        "igCopyRenderDestinationAttr",
        0x34, /* instance size */
        igCopyRenderDestinationAttr_GetVTable,
        &igCopyRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igCopyRenderDestinationAttr_callbackList /* callback list */
    );
}

void thunk_igCopyRenderDestinationAttr_GetMetaObject(void) {
    igCopyRenderDestinationAttr_GetMetaObject();
}

static FieldFactory g_igCopyRenderDestinationAttr_ctorTable[] = {
    igEnumMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
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
    int temp_s2;
    void *temp_v0;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igCopyRenderDestinationAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igCopyRenderDestinationAttr_ctorTable, 0xA);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue(temp_v0, 0);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001388f0);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001341f0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igImage_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)igTextureAttr_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_igCopyRenderDestinationAttr_fieldTable, g_igCopyRenderDestinationAttr_fieldHandles, g_igCopyRenderDestinationAttr_fieldOffsets, temp_s2);
}

