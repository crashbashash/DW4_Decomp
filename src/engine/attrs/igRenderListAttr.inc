igMetaObject *g_igRenderListAttr_metaObject;
igMetaField *g_igRenderListAttr_handleMetaField;
igMetaField *g_igRenderListAttr_vcMetaField;

igMetaObject *igRenderListAttr_GetOrCreateMetaObject(void) {
    if (g_igRenderListAttr_metaObject == 0) {
        g_igRenderListAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRenderListAttr_metaObject;
}

igMetaObject *igRenderListAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderListAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderListAttr_EnsureRegistered();
    return g_igRenderListAttr_metaObject;
}

int igRenderListAttr_GetVTable(void) {
    union U_133ef0 u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader((igObject *)u.b);
    p = (S_ref *)&u.b[16];
    u.vt = (int)&g_igRenderListAttr_vtable[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igRenderListAttr_vtable[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    return temp_s0;
}

void igRenderListAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderListAttr_Register);
}

static igMetaObjectCallback g_igRenderListAttr_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

CallbackArray *igRenderListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRenderListAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igRenderListAttr_GetMetaObjectFunction,
        "igRenderListAttr",
        0x14, /* instance size */
        igRenderListAttr_GetVTable,
        &igRenderListAttr_InitFields,
        0, /* extra callback item */
        g_igRenderListAttr_callbackList /* callback list */
    );
}

void igRenderListAttr_GetMetaObjectFunction(void) {
    igRenderListAttr_GetMetaObject();
}

static FieldFactory g_igRenderListAttr_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igRenderListAttr_fieldTable[] = {
    "_handle",
    "_vc",
};
static igMetaField **g_igRenderListAttr_fieldHandles[] = {
    &g_igRenderListAttr_handleMetaField,
    &g_igRenderListAttr_vcMetaField,
};
static int g_igRenderListAttr_fieldOffsets[] = {
    12,
    16,
};

void igRenderListAttr_InitFields(void) {
    int base;
    struct F_134020 *field;
    struct F_134020 *field2;
    igMetaObject *meta;

    meta = g_igRenderListAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igRenderListAttr_ctorTable, 2);
    field = (struct F_134020 *)(igMetaObject_GetFieldAt(meta, base));
    igIntMetaField_SetDefault((igMetaField *)field, -1);
    field->b38 = 0;
    field2 = (struct F_134020 *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    field2->b38 = 0;
    field2->b40 = 1;
    field2->b39 = 1;
    field2->b44 = 3;
    igMetaObject_NameFields(meta, g_igRenderListAttr_fieldTable, g_igRenderListAttr_fieldHandles, g_igRenderListAttr_fieldOffsets, base);
}

