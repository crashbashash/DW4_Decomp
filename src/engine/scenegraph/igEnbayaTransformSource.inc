igMetaObject *g_igEnbayaTransformSource_metaObject;
igMetaField *g_igEnbayaTransformSource_trackIdMetaField;
igMetaField *g_igEnbayaTransformSource_enbayaAnimationSourceMetaField;

igMetaObject *FUN_001a18b0(void)
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
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)g_objectSystem + 916));
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
        thunk_FUN_001a18b0,
        "igEnbayaTransformSource",
        sizeof(igEnbayaTransformSource),                   /* Instance size. */
        igEnbayaTransformSource_GetVTable,
        &igEnbayaTransformSource_InitFields,
        0, /* extra callback item */
        g_igEnbayaTransformSource_callbackList /* callback list */
    );
}

void thunk_FUN_001a18b0(void) {
    FUN_001a18b0();
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igEnbayaTransformSource_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igEnbayaTransformSource_ctorTable, 2);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2), -1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a2210();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igEnbayaTransformSource_fieldTable, g_igEnbayaTransformSource_fieldHandles, g_igEnbayaTransformSource_fieldOffsets, temp_s2);
}

