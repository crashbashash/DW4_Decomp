igMetaObject *g_igVertexBlendMatrixListAttr_metaObject;
igMetaField *g_igVertexBlendMatrixListAttr_matrixListMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_skeletonTransformMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_skeletonInverseTransformMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_matrixCacheMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_isSkeletonTransformIdentityMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_isSkeletonTransformSetMetaField;
igMetaField *g_igVertexBlendMatrixListAttr_currentMatrixCountMetaField;

void FUN_00130930(int arg0) {
    FUN_00130a70();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55EC28, (igMemoryPoolView *)arg0);
}

igMetaObject *igVertexBlendMatrixListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixListAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00130a70();
    return g_igVertexBlendMatrixListAttr_metaObject;
}

int igVertexBlendMatrixListAttr_GetVTable(void) {
    union U_1309c0 u;
    int temp_s0;
    S_ref *q0;
    int pi = (int)u.b;
    igObject_InitHeader((igObject *)pi);
    u.vt = (int)&g_igVertexBlendMatrixListAttr_vtable[0];
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    igMatrix44f_SetIdentity((float *)&u.b[28]);
    igMatrix44f_SetIdentity((float *)(pi + 92));
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&DAT_00522630[4];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    return temp_s0;
}

void FUN_00130a70(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixListAttr_Register);
}

static igMetaObjectCallback g_igVertexBlendMatrixListAttr_callbackList[] = { FUN_001e4bc0, 0 };

CallbackArray *igVertexBlendMatrixListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexBlendMatrixListAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixListAttr_GetMetaObject,
        "igVertexBlendMatrixListAttr",
        0x9C, /* instance size */
        igVertexBlendMatrixListAttr_GetVTable,
        &igVertexBlendMatrixListAttr_InitFields,
        0, /* extra callback item */
        g_igVertexBlendMatrixListAttr_callbackList /* callback list */
    );
}

void thunk_igVertexBlendMatrixListAttr_GetMetaObject(void) {
    igVertexBlendMatrixListAttr_GetMetaObject();
}

static FieldFactory g_igVertexBlendMatrixListAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igVertexBlendMatrixListAttr_fieldTable[] = {
    "_matrixList",
    "_skeletonTransform",
    "_skeletonInverseTransform",
    "_matrixCache",
    "_isSkeletonTransformIdentity",
    "_isSkeletonTransformSet",
    "_currentMatrixCount",
};
static igMetaField **g_igVertexBlendMatrixListAttr_fieldHandles[] = {
    &g_igVertexBlendMatrixListAttr_matrixListMetaField,
    &g_igVertexBlendMatrixListAttr_skeletonTransformMetaField,
    &g_igVertexBlendMatrixListAttr_skeletonInverseTransformMetaField,
    &g_igVertexBlendMatrixListAttr_matrixCacheMetaField,
    &g_igVertexBlendMatrixListAttr_isSkeletonTransformIdentityMetaField,
    &g_igVertexBlendMatrixListAttr_isSkeletonTransformSetMetaField,
    &g_igVertexBlendMatrixListAttr_currentMatrixCountMetaField,
};
static int g_igVertexBlendMatrixListAttr_fieldOffsets[] = {
    24,
    28,
    92,
    16,
    12,
    13,
    20,
};

void igVertexBlendMatrixListAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igVertexBlendMatrixListAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igVertexBlendMatrixListAttr_ctorTable, 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001e4ae0();
    ((igObjectRefMetaField *)temp_s1)->_construct = 1;
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igMetaField *)temp_v0)->_persistent = 0;
    ((igMetaField *)temp_v0)->_isAlikeShallowMethod = 3;
    ((igMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)))->_persistent = 0;
    ((igMetaField *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5)))->_persistent = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    igIntMetaField_SetDefault((igMetaField *)temp_v0_2, -1);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, g_igVertexBlendMatrixListAttr_fieldTable, g_igVertexBlendMatrixListAttr_fieldHandles, g_igVertexBlendMatrixListAttr_fieldOffsets, temp_s2);
}

