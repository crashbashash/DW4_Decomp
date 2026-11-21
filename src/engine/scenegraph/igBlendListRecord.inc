int FUN_001a2c70(int arg0) {
    igBlendListRecord_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igBlendListRecord_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igBlendListRecord_metaObject;
igMetaField *g_igBlendListRecord_attrMetaField;
igMetaField *g_igBlendListRecord_fwdPtrMetaField;

igMetaObject *igBlendListRecord_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendListRecord_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendListRecord_EnsureRegistered();
    return g_igBlendListRecord_metaObject;
}

int igBlendListRecord_GetVTable(void) {
    union U_1a2d00 u;
    void **q2;
    int temp_s0;
    void *temp_a0;

    igObject_InitHeader((igObject *)u.b);
    q2 = &u.p[2];
    u.w[0] = (int)(&g_igBlendListRecord_vtable[0]);
    *q2 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.w[0] = (int)(&g_igBlendListRecord_vtable[0]);
    if (q2 != 0) {
        temp_a0 = *q2;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igBlendListRecord_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendListRecord_Register);
}

static igMetaObjectCallback g_igBlendListRecord_callbackList[] = { Gap::Attrs::igBlendMatrixPaletteAttr::arkRegister, Gap::Attrs::igAttr::arkRegister, 0 };

CallbackArray *igBlendListRecord_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendListRecord_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igBlendListRecord_GetMetaObjectFunction,
        "igBlendListRecord",
        0x10, /* instance size */
        igBlendListRecord_GetVTable,
        &igBlendListRecord_InitFields,
        0, /* extra callback item */
        g_igBlendListRecord_callbackList /* callback list */
    );
}

void igBlendListRecord_GetMetaObjectFunction(void) {
    igBlendListRecord_GetMetaObject();
}

static FieldFactory g_igBlendListRecord_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igBlendListRecord_fieldTable[] = {
    "_attr",
    "_fwdPtr",
};
static igMetaField **g_igBlendListRecord_fieldHandles[] = {
    &g_igBlendListRecord_attrMetaField,
    &g_igBlendListRecord_fwdPtrMetaField,
};
static int g_igBlendListRecord_fieldOffsets[] = {
    8,
    12,
};

void igBlendListRecord_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBlendListRecord_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igBlendListRecord_ctorTable, 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)Gap::Attrs::igBlendMatrixPaletteAttr::getClassTypeLazy();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)Gap::Attrs::igAttr::getClassTypeLazy();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igBlendListRecord_fieldTable, g_igBlendListRecord_fieldHandles, g_igBlendListRecord_fieldOffsets, temp_s2);
}

