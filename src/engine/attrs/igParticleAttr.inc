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

     igObject_InitHeader(&o);
     o.vt = &g_igParticleAttr_vtable[0];
     o.s = 0;
     r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
     o.vt = &g_igParticleAttr_vtable[0];
     if (&o.s != 0) {
         q = o.s;
         if (q != 0) {
             q->f4 -= 1;
             if ((q->f4 & 0x7fffff) == 0) {
                 igObject_Destroy(q);
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

void igParticleAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igParticleAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igParticleAttr_GetMetaObject,
        "igParticleAttr",
        0x30, /* instance size */
        igParticleAttr_GetVTable,
        &igParticleAttr_InitFields,
        0, /* extra callback item */
        g_igParticleAttr_callbackList /* callback list */
    );
}

void thunk_igParticleAttr_GetMetaObject(void) {
    igParticleAttr_GetMetaObject();
}

static FieldFactory g_igParticleAttr_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igUnsignedIntMetaField_Create,
    igLongMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
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
    int temp_s2;
    void *temp_v0;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igParticleAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igParticleAttr_ctorTable, 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0014c980();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    igLongMetaField_SetDefault(temp_v0, -1);
    ((igLongMetaField *)temp_v0)->_persistent = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5)) + 38) = 0;
    igMetaObject_NameFields(temp_s0, g_igParticleAttr_fieldTable, g_igParticleAttr_fieldHandles, g_igParticleAttr_fieldOffsets, temp_s2);
}

