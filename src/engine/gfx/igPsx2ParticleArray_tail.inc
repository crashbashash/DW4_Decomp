igMetaObject *igPsx2ParticleArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ParticleArray_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153460();
    return g_igPsx2ParticleArray_metaObject;
}

int igPsx2ParticleArray_GetVTable(void) {
    union U_1533f0 u;
    int t;
    igObject_InitHeader((igObject *)u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[40] = 0;
    *(int *)&u.b[44] = 0;
    *(int *)&u.b[48] = 0;
    *(int *)&u.b[68] = 0;
    u.vt = (int)&g_igPsx2ParticleArray_vtable[0];
    t = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igPsx2ParticleArray_vtable[0];
    igParticleArray_Destroy((igParticleArray *)u.b, 0);
    return t;
}

void FUN_00153460(void)
{
    igMetaObject_RunStaticInit(igPsx2ParticleArray_Register);
}

CallbackArray *igPsx2ParticleArray_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPsx2ParticleArray_metaObject,
        igParticleArray_Register,
        igParticleArray_GetPublishedMetaObject,
        thunk_igPsx2ParticleArray_GetMetaObject,
        "igPsx2ParticleArray",
        0x78, /* instance size */
        igPsx2ParticleArray_GetVTable,
        &igPsx2ParticleArray_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_001534e0(void) {
    return g_igParticleArray_metaObject;
}

static FieldFactory g_igPsx2ParticleArray_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
};
static const char *g_igPsx2ParticleArray_fieldTable[] = {
    "_hardwareSupport",
    "_currentEditIndex",
    "_ps2ParticleFormat",
    "_bSynchronize",
    "_lSequence",
};
static igMetaField **g_igPsx2ParticleArray_fieldHandles[] = {
    &g_igPsx2ParticleArray_hardwareSupportMetaField,
    &g_igPsx2ParticleArray_currentEditIndexMetaField,
    &g_igPsx2ParticleArray_ps2ParticleFormatMetaField,
    &g_igPsx2ParticleArray_bSynchronizeMetaField,
    &g_igPsx2ParticleArray_lSequenceMetaField,
};
static int g_igPsx2ParticleArray_fieldOffsets[] = {
    92,
    96,
    100,
    104,
    112,
};

void igPsx2ParticleArray_InitFields(void) {
    int fieldStart;
    igMetaObject *meta;

    meta = g_igPsx2ParticleArray_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPsx2ParticleArray_ctorTable, 5);
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart)) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 1)) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 2)) + 38) = 0;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, fieldStart + 3), 1);
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 4)) + 38) = 0;
    igMetaObject_NameFields(meta, g_igPsx2ParticleArray_fieldTable, g_igPsx2ParticleArray_fieldHandles, g_igPsx2ParticleArray_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igPsx2ParticleArray_metaObject) + 64) = (int)(&thunk_igParticleArray_GetMetaObject);
}

