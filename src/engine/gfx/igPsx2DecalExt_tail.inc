igMetaObject *igPsx2DecalExt_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2DecalExt_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001542b0();
    return g_igPsx2DecalExt_metaObject;
}

int igPsx2DecalExt_GetVTable(void) {
    union U_1541d0 u;
    int temp_s1;
    S_ref *q1;
    S_ref *q2;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00530a10[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[16];
    *(int *)q2 = 0;
    u.w[0] = (int)(&g_igPsx2DecalExt_vtable[0]);
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00530a10[0]);
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s1;
}

void FUN_001542b0(void)
{
    igMetaObject_RunStaticInit(igPsx2DecalExt_Register);
}

static igMetaObjectCallback g_igPsx2DecalExt_callbackList[] = { FUN_001511a0, 0 };

void igPsx2DecalExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2DecalExt_metaObject,
        igDecalExt_Register,
        igDecalExt_GetPublishedMetaObject,
        thunk_igPsx2DecalExt_GetMetaObject,
        "igPsx2DecalExt",
        0x20, /* instance size */
        igPsx2DecalExt_GetVTable,
        &igPsx2DecalExt_InitFields,
        0, /* extra callback item */
        g_igPsx2DecalExt_callbackList /* callback list */
    );
}

int FUN_00154340(void) {
    return (int)g_igDecalExt_metaObject;
}

static FieldFactory g_igPsx2DecalExt_ctorTable[] = {
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
};
static const char *g_igPsx2DecalExt_fieldTable[] = {
    "_context",
    "_offsetUnits",
};
static igMetaField **g_igPsx2DecalExt_fieldHandles[] = {
    &g_igPsx2DecalExt_contextMetaField,
    &g_igPsx2DecalExt_offsetUnitsMetaField,
};
static int g_igPsx2DecalExt_fieldOffsets[] = {
    24,
    28,
};

void igPsx2DecalExt_InitFields(void) {
    int fieldStart;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igPsx2DecalExt_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2DecalExt_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00150770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 1), 1);
    igMetaObject_NameFields(meta, g_igPsx2DecalExt_fieldTable, g_igPsx2DecalExt_fieldHandles, g_igPsx2DecalExt_fieldOffsets, fieldStart);
}

