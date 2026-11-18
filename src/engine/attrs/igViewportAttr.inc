igMetaObject *g_igViewportAttr_metaObject;
igMetaField *g_igViewportAttr_xMetaField;
igMetaField *g_igViewportAttr_yMetaField;
igMetaField *g_igViewportAttr_wMetaField;
igMetaField *g_igViewportAttr_hMetaField;
igMetaField *g_igViewportAttr_scissorExtMetaField;
igMetaField *g_igViewportAttr_nearZMetaField;
igMetaField *g_igViewportAttr_farZMetaField;

igMetaObject *igViewportAttr_GetOrCreateMetaObject(void) {
    if (g_igViewportAttr_metaObject == 0) {
        g_igViewportAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewportAttr_metaObject;
}

igMetaObject *igViewportAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igViewportAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igViewportAttr_EnsureRegistered();
    return g_igViewportAttr_metaObject;
}

int igViewportAttr_GetVTable(void) {
    union U_1304e0 u;
    int temp_s0;
    char *ps;
    int *temp_a0;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igViewportAttr_vtable[0];
    ps = &u.b[28];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igViewportAttr_vtable[0];
    if (ps != 0) {
        temp_a0 = *(int **)ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igViewportAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewportAttr_Register);
}

static igMetaObjectCallback g_igViewportAttr_callbackList[] = { igScissorExt_EnsureRegistered, 0 };

CallbackArray *igViewportAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igViewportAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igViewportAttr_GetMetaObjectFunction,
        "igViewportAttr",
        0x28, /* instance size */
        igViewportAttr_GetVTable,
        &igViewportAttr_InitFields,
        0, /* extra callback item */
        g_igViewportAttr_callbackList /* callback list */
    );
}

void igViewportAttr_GetMetaObjectFunction(void) {
    igViewportAttr_GetMetaObject();
}

igMetaObject *igVisualAttribute_GetPublishedMetaObject(void) {
    return g_igVisualAttribute_metaObject;
}

static FieldFactory g_igViewportAttr_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
};
static const char *g_igViewportAttr_fieldTable[] = {
    "_x",
    "_y",
    "_w",
    "_h",
    "_scissorExt",
    "_nearZ",
    "_farZ",
};
static igMetaField **g_igViewportAttr_fieldHandles[] = {
    &g_igViewportAttr_xMetaField,
    &g_igViewportAttr_yMetaField,
    &g_igViewportAttr_wMetaField,
    &g_igViewportAttr_hMetaField,
    &g_igViewportAttr_scissorExtMetaField,
    &g_igViewportAttr_nearZMetaField,
    &g_igViewportAttr_farZMetaField,
};
static int g_igViewportAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

void igViewportAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igViewportAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igViewportAttr_ctorTable, 7);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 2), 0x27F);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 3), 0x1BF);
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igScissorExt_GetOrCreateMetaObject();
    ((igMetaField *)field)->_persistent = 0;
    ((igMetaField *)field)->_deepCopyMethod = 1;
    ((igMetaField *)field)->_shallowCopyMethod = 1;
    ((igMetaField *)field)->_isAlikeShallowMethod = 3;
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 6), 1.0f);
    igMetaObject_NameFields(meta, g_igViewportAttr_fieldTable, g_igViewportAttr_fieldHandles, g_igViewportAttr_fieldOffsets, base);
}

igStringRef *igStringRef_Destruct(igStringRef *self, short deleteFlag) {
    if (self) {
        char *value = self->p;
        if (value) {
            StringTokenHeader *header = (StringTokenHeader *)value - 1;
            if (--header->refCount == 0) StringChunk_ReleaseHeader((StringChunk *)header->owner, header);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

