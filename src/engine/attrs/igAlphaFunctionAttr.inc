igMetaObject *g_igAlphaFunctionAttr_metaObject;
igMetaField *g_igAlphaFunctionAttr_funcMetaField;
igMetaField *g_igAlphaFunctionAttr_refValueMetaField;

void FUN_0013b490(int arg0) {
    igAlphaFunctionAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x55F490, arg0);
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

    igObject_InitHeader(&o);
    o.vt = &g_igAlphaFunctionAttr_vtable[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igAlphaFunctionAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAlphaFunctionAttr_Register);
}

void igAlphaFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAlphaFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igAlphaFunctionAttr_GetMetaObject,
        "igAlphaFunctionAttr",
        0x14, /* instance size */
        igAlphaFunctionAttr_GetVTable,
        &igAlphaFunctionAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAlphaFunctionAttr_GetMetaObject(void) {
    igAlphaFunctionAttr_GetMetaObject();
}

static FieldFactory g_igAlphaFunctionAttr_ctorTable[] = {
    igEnumMetaField_Create,
    igFloatMetaField_Create,
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
    int temp_s2;
    void *temp_v0;
    igMetaObject *temp_s0;

    temp_s0 = g_igAlphaFunctionAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igAlphaFunctionAttr_ctorTable, 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue(temp_v0, g_igAlphaFunctionAttr_funcDefault);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001496e0);
    igMetaObject_NameFields(temp_s0, g_igAlphaFunctionAttr_fieldTable, g_igAlphaFunctionAttr_fieldHandles, g_igAlphaFunctionAttr_fieldOffsets, temp_s2);
}

void Gap__Attrs__igAlphaFunctionAttr__vfunc_24(S2* p, int q) { Gap__Gfx__igPsx2VisualContext__vfunc_219(q, p->a); Gap__Gfx__igPsx2VisualContext__vfunc_221(q, p->b); }

void Gap__Attrs__igAlphaFunctionAttr__vfunc_26(void **arg0, void **arg1) {
    ((DW4VC_128_1 *)(arg0))->vX((int)(((DW4VC_880_0 *)(arg1))->vX()));
    ((DW4VC_132_1 *)(arg0))->vX((float)(((DW4VC_888_0 *)(arg1))->vX()));
}

/* Setter: stores the alpha-test reference value (`_refValue`, an igFloatMetaField of the reflected
 * igAlphaFunctionAttr). */
void Gap__Attrs__igAlphaFunctionAttr__vfunc_33(igAlphaFunctionAttr *self, float refValue) {
    self->_refValue = refValue;
}

/* Setter for the alpha-test comparison function (`_func`, +12); `_refValue` at +16 is the
 * reference it compares to. */

void Gap__Attrs__igAlphaFunctionAttr__vfunc_32(igAlphaFunctionAttr *self, int func) {
    self->_func = func;
}

