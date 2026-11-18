igMetaObject *g_igEnbayaTransformSource_metaObject;
igMetaField *g_igEnbayaTransformSource_trackIdMetaField;
igMetaField *g_igEnbayaTransformSource_enbayaAnimationSourceMetaField;

igMetaObject *igEnbayaTransformSource_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaTransformSource_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnbayaTransformSource_EnsureRegistered();
    return g_igEnbayaTransformSource_metaObject;
}

int igEnbayaTransformSource_GetVTable(void) {
    Obj_1a1900 o;
    int **ps;
    int *temp_a0;
    int temp_s0;

    igObject_InitHeader((igObject *)&o);
    ps = &o.ref;
    o.vt = &g_igEnbayaTransformSource_vtable[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igEnbayaTransformSource_vtable[0];
    if (ps != 0) {
        temp_a0 = *ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igEnbayaTransformSource_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEnbayaTransformSource_Register);
}

static igMetaObjectCallback g_igEnbayaTransformSource_callbackList[] = { igEnbayaAnimationSource_EnsureRegistered, 0 };

CallbackArray *igEnbayaTransformSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEnbayaTransformSource_metaObject,
        igTransformSource_Register,
        igTransformSource_GetPublishedMetaObject,
        igEnbayaTransformSource_GetMetaObjectFunction,
        "igEnbayaTransformSource",
        sizeof(igEnbayaTransformSource),                   /* Instance size. */
        igEnbayaTransformSource_GetVTable,
        &igEnbayaTransformSource_InitFields,
        0, /* extra callback item */
        g_igEnbayaTransformSource_callbackList /* callback list */
    );
}

void igEnbayaTransformSource_GetMetaObjectFunction(void) {
    igEnbayaTransformSource_GetMetaObject();
}

static FieldFactory g_igEnbayaTransformSource_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igEnbayaTransformSource_fieldTable[] = {
    "_trackId",
    "_enbayaAnimationSource",
};
static igMetaField **g_igEnbayaTransformSource_fieldHandles[] = {
    &g_igEnbayaTransformSource_trackIdMetaField,
    &g_igEnbayaTransformSource_enbayaAnimationSourceMetaField,
};
static int g_igEnbayaTransformSource_fieldOffsets[] = {
    8,
    12,
};

void igEnbayaTransformSource_InitFields(void) {
    int base;
    void *enbayaAnimationSourceField;
    void *meta;

    meta = (void *)g_igEnbayaTransformSource_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igEnbayaTransformSource_ctorTable, 2);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), -1);
    enbayaAnimationSourceField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)enbayaAnimationSourceField)->_metaObject = (int)igEnbayaAnimationSource_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igEnbayaTransformSource_fieldTable, g_igEnbayaTransformSource_fieldHandles, g_igEnbayaTransformSource_fieldOffsets, base);
}

