igMetaObject *g_igAnimationTransitionParams_metaObject;
igMetaField *g_igAnimationTransitionParams_startRatioMetaField;
igMetaField *g_igAnimationTransitionParams_endRatioMetaField;
igMetaField *g_igAnimationTransitionParams_durationMetaField;
igMetaField *g_igAnimationTransitionParams_targetStartTimeMetaField;

igMetaObject *FUN_001a9bb0(void) {
    if (g_igAnimationTransitionParams_metaObject == 0) {
        g_igAnimationTransitionParams_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationTransitionParams_metaObject;
}

igMetaObject *igAnimationTransitionParams_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionParams_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9c90();
    return g_igAnimationTransitionParams_metaObject;
}

int igAnimationTransitionParams_GetVTable(void) {
    struct Obj_1a9c50 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationTransitionParams_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_001a9c90(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionParams_Register);
}

CallbackArray *igAnimationTransitionParams_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTransitionParams_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionParams_GetMetaObject,
        "igAnimationTransitionParams",
        0x20, /* instance size */
        igAnimationTransitionParams_GetVTable,
        &igAnimationTransitionParams_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAnimationTransitionParams_GetMetaObject(void) {
    igAnimationTransitionParams_GetMetaObject();
}

static FieldFactory g_igAnimationTransitionParams_ctorTable[] = {
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
};
static const char *g_igAnimationTransitionParams_fieldTable[] = {
    "_startRatio",
    "_endRatio",
    "_duration",
    "_targetStartTime",
};
static igMetaField **g_igAnimationTransitionParams_fieldHandles[] = {
    &g_igAnimationTransitionParams_startRatioMetaField,
    &g_igAnimationTransitionParams_endRatioMetaField,
    &g_igAnimationTransitionParams_durationMetaField,
    &g_igAnimationTransitionParams_targetStartTimeMetaField,
};
static int g_igAnimationTransitionParams_fieldOffsets[] = {
    8,
    12,
    16,
    24,
};

void igAnimationTransitionParams_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationTransitionParams_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationTransitionParams_ctorTable, 4);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationTransitionParams_fieldTable, g_igAnimationTransitionParams_fieldHandles, g_igAnimationTransitionParams_fieldOffsets, temp_s1);
}

