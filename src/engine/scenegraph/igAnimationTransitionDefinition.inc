igMetaObject *g_igAnimationTransitionDefinition_metaObject;
igMetaField *g_igAnimationTransitionDefinition_baseAnimationMetaField;
igMetaField *g_igAnimationTransitionDefinition_transitionPointListMetaField;
igMetaField *g_igAnimationTransitionDefinition_paramsMetaField;

igMetaObject *igAnimationTransitionDefinition_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionDefinition_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationTransitionDefinition_EnsureRegistered();
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

void igAnimationTransitionDefinition_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionDefinition_Register);
}

static igMetaObjectCallback g_igAnimationTransitionDefinition_callbackList[] = { igAnimation_EnsureRegistered, igAnimationTransitionPointList_EnsureRegistered, igAnimationTransitionParams_EnsureRegistered, 0 };

CallbackArray *igAnimationTransitionDefinition_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTransitionDefinition_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igAnimationTransitionDefinition_GetMetaObjectFunction,
        "igAnimationTransitionDefinition",
        0x14, /* instance size */
        igAnimationTransitionDefinition_GetVTable,
        &igAnimationTransitionDefinition_InitFields,
        0, /* extra callback item */
        g_igAnimationTransitionDefinition_callbackList /* callback list */
    );
}

void igAnimationTransitionDefinition_GetMetaObjectFunction(void) {
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
    int base;
    void *paramsField;
    void *transitionPointListField;
    void *baseAnimationField;
    void *meta;

    meta = (void *)g_igAnimationTransitionDefinition_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAnimationTransitionDefinition_ctorTable, 3);
    baseAnimationField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)baseAnimationField)->_metaObject = (int)igAnimation_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)baseAnimationField)->_refCounted = 0;
    transitionPointListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)transitionPointListField)->_metaObject = (int)igAnimationTransitionPointList_GetOrCreateMetaObject();
    ((igRefMetaField *)transitionPointListField)->_construct = 1;
    paramsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)paramsField)->_metaObject = (int)igAnimationTransitionParams_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igAnimationTransitionDefinition_fieldTable, g_igAnimationTransitionDefinition_fieldHandles, g_igAnimationTransitionDefinition_fieldOffsets, base);
}

