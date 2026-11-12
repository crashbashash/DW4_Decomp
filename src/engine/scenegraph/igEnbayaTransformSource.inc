igMetaObject *FUN_001a18b0(void)
{
    igMetaObject *g = ((igMetaObject * *)DAT_00561b48)[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a1990();
    return ((igMetaObject * *)DAT_00561b48)[0];
}

int igEnbayaTransformSource_GetVTable(void) {
    Obj_1a1900 o;
    int **ps;
    int *temp_a0;
    int temp_s0;

    igObject_InitHeader(&o);
    ps = &o.ref;
    o.vt = &DAT_00529080[0];
    *ps = 0;
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00529080[0];
    if (ps != 0) {
        temp_a0 = *ps;
        if (temp_a0 != 0) {
            temp_a0[1] = temp_a0[1] - 1;
            if (((unsigned long long) ((long long) temp_a0[1] << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void FUN_001a1990(void)
{
    igMetaObject_RunStaticInit(igEnbayaTransformSource_Register);
}

void igEnbayaTransformSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEnbayaTransformSource_metaObject),
        igTransformSource_Register,
        igTransformSource_GetPublishedMetaObject,
        thunk_FUN_001a18b0,
        igEnbayaTransformSource_className,
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

void igEnbayaTransformSource_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_00561b48[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048c2d0[0], 2);
    FUN_002ea4b0(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)), -1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a2210();
    igMetaObject_NameFields(temp_s0, &DAT_0048c2d8[0], &DAT_0048c2e0[0], &DAT_0048c2e8[0], temp_s2);
}

