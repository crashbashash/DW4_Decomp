igMetaObject *igPsx2BlendEquationExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2BlendEquationExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2BlendEquationExt_EnsureRegistered();
    return g_igPsx2BlendEquationExt_metaObject;
}

int igPsx2BlendEquationExt_GetVTable(void) {
    union U_154630 u;
    int temp_s1;
    S_ref *q1;
    S_ref *q2;
    
    
    igObject_InitHeader((igObject *)u.b);
    u.w[0] = (int)(&DAT_00530a10[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    u.w[0] = (int)(&g_igPsx2BlendEquationExt_vtable[0]);
    temp_s1 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&DAT_00530a10[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q2);
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
    return temp_s1;
}

void igPsx2BlendEquationExt_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2BlendEquationExt_Register);
}

static igMetaObjectCallback g_igPsx2BlendEquationExt_callbackList[] = { igPsx2VisualContext_EnsureRegistered, 0 };

CallbackArray *igPsx2BlendEquationExt_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2BlendEquationExt_metaObject,
        igBlendEquationExt_Register,
        igBlendEquationExt_GetPublishedMetaObject,
        igPsx2BlendEquationExt_GetMetaObjectFunction,
        "igPsx2BlendEquationExt",
        0x30, /* instance size */
        igPsx2BlendEquationExt_GetVTable,
        &igPsx2BlendEquationExt_InitFields,
        0, /* extra callback item */
        g_igPsx2BlendEquationExt_callbackList /* callback list */
    );
}

igMetaObject *igBlendEquationExt_GetPublishedMetaObject(void) {
    return g_igBlendEquationExt_metaObject;
}

static FieldFactory g_igPsx2BlendEquationExt_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igCharMetaField_Create,
};
static const char *g_igPsx2BlendEquationExt_fieldTable[] = {
    "_context",
    "_blendA",
    "_blendB",
    "_blendC",
    "_blendD",
    "_blendConstant",
};
static igMetaField **g_igPsx2BlendEquationExt_fieldHandles[] = {
    &g_igPsx2BlendEquationExt_contextMetaField,
    &g_igPsx2BlendEquationExt_blendAMetaField,
    &g_igPsx2BlendEquationExt_blendBMetaField,
    &g_igPsx2BlendEquationExt_blendCMetaField,
    &g_igPsx2BlendEquationExt_blendDMetaField,
    &g_igPsx2BlendEquationExt_blendConstantMetaField,
};
static int g_igPsx2BlendEquationExt_fieldOffsets[] = {
    24,
    28,
    32,
    36,
    40,
    44,
};

void igPsx2BlendEquationExt_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igPsx2BlendEquationExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2BlendEquationExt_ctorTable, 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igPsx2VisualContext_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    ((Gap::Core::igCharMetaField *)(igMetaObject_GetFieldAt(meta, fieldStart + 5)))->setDefault(-0x80);
    igMetaObject_NameFields(meta, g_igPsx2BlendEquationExt_fieldTable, g_igPsx2BlendEquationExt_fieldHandles, g_igPsx2BlendEquationExt_fieldOffsets, fieldStart);
}

