void FUN_0013b490(int arg0) {
    FUN_0013b560();
    igMetaObject_CreateInstance(*(int *)0x55F490, arg0);
}

igMetaObject *igAlphaFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAlphaFunctionAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013b560();
    return g_igAlphaFunctionAttr_metaObject[0];
}

int igAlphaFunctionAttr_GetVTable(void) {
    Obj_13b520 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00524390[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0013b560(void)
{
    igMetaObject_RunStaticInit(igAlphaFunctionAttr_Register);
}

void igAlphaFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAlphaFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igAlphaFunctionAttr_GetMetaObject,
        igAlphaFunctionAttr_className,
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

void igAlphaFunctionAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f490[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486c90[0], 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    FUN_002dc7a0(temp_v0, &DAT_00486cb0[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001496e0);
    igMetaObject_NameFields(temp_s0, &DAT_00486c98[0], &DAT_00486ca0[0], &DAT_00486ca8[0], temp_s2);
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

