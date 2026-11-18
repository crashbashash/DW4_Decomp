igMetaObject *g_igAlphaFunctionAttr_metaObject;
igMetaField *g_igAlphaFunctionAttr_funcMetaField;
igMetaField *g_igAlphaFunctionAttr_refValueMetaField;

igAlphaFunctionAttr *igAlphaFunctionAttr_Create(igMemoryPoolView *pool) {
    igAlphaFunctionAttr_EnsureRegistered();
    return (igAlphaFunctionAttr *)igMetaObject_CreateInstance(g_igAlphaFunctionAttr_metaObject, pool);
}

igMetaObject *igAlphaFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAlphaFunctionAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAlphaFunctionAttr_EnsureRegistered();
    return g_igAlphaFunctionAttr_metaObject;
}

int igAlphaFunctionAttr_GetVTable(void) {
    Obj_13b520 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igAlphaFunctionAttr_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igAlphaFunctionAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAlphaFunctionAttr_Register);
}

CallbackArray *igAlphaFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAlphaFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igAlphaFunctionAttr_GetMetaObjectFunction,
        "igAlphaFunctionAttr",
        0x14, /* instance size */
        igAlphaFunctionAttr_GetVTable,
        &igAlphaFunctionAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAlphaFunctionAttr_GetMetaObjectFunction(void) {
    igAlphaFunctionAttr_GetMetaObject();
}

static FieldFactory g_igAlphaFunctionAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
};
static const char *g_igAlphaFunctionAttr_fieldTable[] = {
    "_func",
    "_refValue",
};
static igMetaField **g_igAlphaFunctionAttr_fieldHandles[] = {
    &g_igAlphaFunctionAttr_funcMetaField,
    &g_igAlphaFunctionAttr_refValueMetaField,
};
static int g_igAlphaFunctionAttr_fieldOffsets[] = {
    12,
    16,
};

int g_igAlphaFunctionAttr_funcDefault = 6;

void igAlphaFunctionAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igAlphaFunctionAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igAlphaFunctionAttr_ctorTable, 2);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, g_igAlphaFunctionAttr_funcDefault);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)(&IG_GFX_ALPHA_FUNCTION_GetMetaEnum);
    igMetaObject_NameFields(meta, g_igAlphaFunctionAttr_fieldTable, g_igAlphaFunctionAttr_fieldHandles, g_igAlphaFunctionAttr_fieldOffsets, base);
}

void igAlphaFunctionAttr_apply(S2* p, igPsx2VisualContext *q) { igPsx2VisualContext_SetAlphaFunc(q, p->a); igPsx2VisualContext_SetAlphaRefValue(q, p->b); }

void igAlphaFunctionAttr_SynchronizeDefault(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_880_0 *)(arg1))->vX()));
    ((DW4VC_132_1 *)(arg0))->vX((float)(((DW4VC_888_0 *)(arg1))->vX()));
}

/* Setter: stores the alpha-test reference value (`_refValue`, an igFloatMetaField of the reflected
 * igAlphaFunctionAttr). */
void igAlphaFunctionAttr_SetRefValue(igAlphaFunctionAttr *self, float refValue) {
    self->_refValue = refValue;
}

/* Setter for the alpha-test comparison function (`_func`, +12); `_refValue` at +16 is the
 * reference it compares to. */

void igAlphaFunctionAttr_SetAlphaFunc(igAlphaFunctionAttr *self, int func) {
    self->_func = func;
}

