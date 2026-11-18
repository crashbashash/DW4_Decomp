igMetaObject *g_igAnimationTransitionDefinition_metaObject;
igMetaField *g_igAnimationTransitionDefinition_baseAnimationMetaField;
igMetaField *g_igAnimationTransitionDefinition_transitionPointListMetaField;
igMetaField *g_igAnimationTransitionDefinition_paramsMetaField;

igMetaObject *igAnimationTransitionDefinition_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionDefinition_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a96c0();
    return g_igAnimationTransitionDefinition_metaObject;
}

int igAnimationTransitionDefinition_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p1;
    S_ref *p2;
    S_ref *t1;
    S_ref *t2;

    igObject_InitHeader((igObject *)u.b);
    p1 = (S_ref *)&u.b[16];
    p2 = (S_ref *)&u.b[12];
    u.vt = (int)&g_igAnimationTransitionDefinition_vtable[0];
    *(int *)p2 = 0;
    *(int *)p1 = 0;
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igAnimationTransitionDefinition_vtable[0];
    if (p1 != 0) {
        t1 = *(S_ref **)p1;
        if (t1 != 0) {
            t1->f4 = (int)((int) (t1->f4 - 1));
            if (((unsigned long long) ((long long) t1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t1);
            }
        }
    }
    if (p2 != 0) {
        t2 = *(S_ref **)p2;
        if (t2 != 0) {
            t2->f4 = (int)((int) (t2->f4 - 1));
            if (((unsigned long long) ((long long) t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)t2);
            }
        }
    }
    return temp_s0;
}

void FUN_001a96c0(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionDefinition_Register);
}

static igMetaObjectCallback g_igAnimationTransitionDefinition_callbackList[] = { igAnimation_EnsureRegistered, FUN_001a9910, FUN_001a9c90, 0 };

CallbackArray *igAnimationTransitionDefinition_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTransitionDefinition_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionDefinition_GetMetaObject,
        "igAnimationTransitionDefinition",
        0x14, /* instance size */
        igAnimationTransitionDefinition_GetVTable,
        &igAnimationTransitionDefinition_InitFields,
        0, /* extra callback item */
        g_igAnimationTransitionDefinition_callbackList /* callback list */
    );
}

void thunk_igAnimationTransitionDefinition_GetMetaObject(void) {
    igAnimationTransitionDefinition_GetMetaObject();
}

static FieldFactory g_igAnimationTransitionDefinition_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAnimationTransitionDefinition_fieldTable[] = {
    "_baseAnimation",
    "_transitionPointList",
    "_params",
};
static igMetaField **g_igAnimationTransitionDefinition_fieldHandles[] = {
    &g_igAnimationTransitionDefinition_baseAnimationMetaField,
    &g_igAnimationTransitionDefinition_transitionPointListMetaField,
    &g_igAnimationTransitionDefinition_paramsMetaField,
};
static int g_igAnimationTransitionDefinition_fieldOffsets[] = {
    8,
    12,
    16,
};

void igAnimationTransitionDefinition_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationTransitionDefinition_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationTransitionDefinition_ctorTable, 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a9130();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_001a9830();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_001a9bb0();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationTransitionDefinition_fieldTable, g_igAnimationTransitionDefinition_fieldHandles, g_igAnimationTransitionDefinition_fieldOffsets, temp_s2);
}

