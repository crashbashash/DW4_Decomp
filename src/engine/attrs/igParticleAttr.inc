igMetaObject *g_igParticleAttr_metaObject;
igMetaField *g_igParticleAttr_bUseCurrentTimeMetaField;
igMetaField *g_igParticleAttr_particleArrayMetaField;
igMetaField *g_igParticleAttr_particleNumMetaField;
igMetaField *g_igParticleAttr_particleOffsetMetaField;
igMetaField *g_igParticleAttr_startTimeMetaField;
igMetaField *g_igParticleAttr_timeMetaField;
igMetaField *g_igParticleAttr_offsetMetaField;

igMetaObject *igParticleAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igParticleAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igParticleAttr_EnsureRegistered();
    return g_igParticleAttr_metaObject;
}

int igParticleAttr_GetVTable(void) {
     Obj_134dc0 o;
     int r;
     Q *q;

     igObject_InitHeader((igObject *)&o);
     o.vt = &g_igParticleAttr_vtable[0];
     o.s = 0;
     r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
     o.vt = &g_igParticleAttr_vtable[0];
     if (&o.s != 0) {
         q = o.s;
         if (q != 0) {
             q->f4 -= 1;
             if ((q->f4 & 0x7fffff) == 0) {
                 igObject_Destroy((igObject *)q);
             }
         }
     }
     return r;
 }

void igParticleAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igParticleAttr_Register);
}

static igMetaObjectCallback g_igParticleAttr_callbackList[] = { FUN_0014cd90, 0 };

CallbackArray *igParticleAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igParticleAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igParticleAttr_GetMetaObjectFunction,
        "igParticleAttr",
        0x30, /* instance size */
        igParticleAttr_GetVTable,
        &igParticleAttr_InitFields,
        0, /* extra callback item */
        g_igParticleAttr_callbackList /* callback list */
    );
}

void igParticleAttr_GetMetaObjectFunction(void) {
    igParticleAttr_GetMetaObject();
}

static FieldFactory g_igParticleAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
};
static const char *g_igParticleAttr_fieldTable[] = {
    "_bUseCurrentTime",
    "_particleArray",
    "_particleNum",
    "_particleOffset",
    "_startTime",
    "_time",
    "_offset",
};
static igMetaField **g_igParticleAttr_fieldHandles[] = {
    &g_igParticleAttr_bUseCurrentTimeMetaField,
    &g_igParticleAttr_particleArrayMetaField,
    &g_igParticleAttr_particleNumMetaField,
    &g_igParticleAttr_particleOffsetMetaField,
    &g_igParticleAttr_startTimeMetaField,
    &g_igParticleAttr_timeMetaField,
    &g_igParticleAttr_offsetMetaField,
};
static int g_igParticleAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    32,
    40,
    44,
};

void igParticleAttr_InitFields(void) {
    int base;
    void *field;
    void *field2;
    igMetaObject *meta;

    meta = g_igParticleAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igParticleAttr_ctorTable, 7);
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field2)->_metaObject = igParticleArray_GetOrCreateMetaObject();
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    igLongMetaField_SetDefault((igMetaField *)field, -1);
    ((igLongMetaField *)field)->_persistent = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, base + 5)) + 38) = 0;
    igMetaObject_NameFields(meta, g_igParticleAttr_fieldTable, g_igParticleAttr_fieldHandles, g_igParticleAttr_fieldOffsets, base);
}

