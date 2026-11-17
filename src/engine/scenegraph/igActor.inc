igMetaObject *g_igActor_metaObject;
igMetaField *g_igActor_animationSystemMetaField;
igMetaField *g_igActor_boneMatrixCacheArrayMetaField;
igMetaField *g_igActor_blendMatrixCacheArrayMetaField;
igMetaField *g_igActor_appearanceMetaField;
igMetaField *g_igActor_animationDatabaseMetaField;
igMetaField *g_igActor_modifierListMetaField;
igMetaField *g_igActor_transformMetaField;
igMetaField *g_igActor_forceActorCacheUseMetaField;
igMetaField *g_igActor_actorCacheUsedMetaField;
igMetaField *g_igActor_mvmWhenTraversedMetaField;
igMetaField *g_igActor_inverseViewWhenTraversedMetaField;
igMetaField *g_igActor_updateMetaField;
igMetaField *g_igActor_renderMetaField;

igMetaObject *FUN_001aa730(void) {
    if (g_igActor_metaObject == 0) {
        g_igActor_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igActor_metaObject;
}

igMetaObject *igActor_GetMetaObject(void)
{
    igMetaObject *g = g_igActor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igActor_EnsureRegistered();
    return g_igActor_metaObject;
}

int igActor_GetVTable(void) {
    igActorView actor;
    return *(int *)((char *)&actor + *(int *)((char *)g_objectSystem + 916));
}

void **FUN_001aa8d0(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

void **FUN_001aa950(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if ((short)arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

O *FUN_001aa9d0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

void igActor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igActor_Register);
}

static igMetaObjectCallback g_igActor_callbackList[] = { FUN_001a66a0, igAppearance_EnsureRegistered, igAnimationDatabase_EnsureRegistered, igAnimationModifierList_EnsureRegistered, 0 };

CallbackArray *igActor_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igActor_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igActor_GetMetaObject,
        "igActor",
        0x100, /* instance size */
        igActor_GetVTable,
        &igActor_InitFields,
        0, /* extra callback item */
        g_igActor_callbackList /* callback list */
    );
}

void thunk_igActor_GetMetaObject(void) {
    igActor_GetMetaObject();
}

static FieldFactory g_igActor_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igActor_fieldTable[] = {
    "_animationSystem",
    "_boneMatrixCacheArray",
    "_blendMatrixCacheArray",
    "_appearance",
    "_animationDatabase",
    "_modifierList",
    "_transform",
    "_forceActorCacheUse",
    "_actorCacheUsed",
    "_mvmWhenTraversed",
    "_inverseViewWhenTraversed",
    "_update",
    "_render",
};
static igMetaField **g_igActor_fieldHandles[] = {
    &g_igActor_animationSystemMetaField,
    &g_igActor_boneMatrixCacheArrayMetaField,
    &g_igActor_blendMatrixCacheArrayMetaField,
    &g_igActor_appearanceMetaField,
    &g_igActor_animationDatabaseMetaField,
    &g_igActor_modifierListMetaField,
    &g_igActor_transformMetaField,
    &g_igActor_forceActorCacheUseMetaField,
    &g_igActor_actorCacheUsedMetaField,
    &g_igActor_mvmWhenTraversedMetaField,
    &g_igActor_inverseViewWhenTraversedMetaField,
    &g_igActor_updateMetaField,
    &g_igActor_renderMetaField,
};
static int g_igActor_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    120,
    121,
    124,
    188,
    252,
    253,
};

void igActor_InitFields(void) {
    struct ActorMatrixWords a1;
    struct ActorVectorWords a2, a3, a4, a5;
    struct ActorMatrixWords b1;
    struct ActorVectorWords b2, b3, b4, b5;
    struct ActorMatrixWords c1;
    struct ActorVectorWords c2, c3, c4, c5;
    int temp_s1;
    void *temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_v0;
    void *temp_v0_2;

    temp_s0 = (void *)g_igActor_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igActor_ctorTable, 0xD);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_001a6600();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igMemoryRefMetaField *)temp_s2_2)->_memType = FUN_001888e0();
    ((igRefMetaField *)temp_s2_2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_2)->_releaseOnReset = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igMemoryRefMetaField *)temp_s2_3)->_memType = FUN_001888e0();
    ((igRefMetaField *)temp_s2_3)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_3)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_3)->_releaseOnReset = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_001a6150();
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igAnimationDatabase_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_001a72d0();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    a5.x = 0; a5.y = 0; a5.z = 0; a5.w = 0x3F800000;
    a4.x = 0; a4.y = 0; a4.z = 0x3F800000; a4.w = 0;
    a3.x = 0; a3.y = 0x3F800000; a3.z = 0; a3.w = 0;
    a2.x = 0x3F800000; a2.y = 0; a2.z = 0; a2.w = 0;
    igMatrix44f_FromRows((float *)&a1, (igVec4f *)&a2, (igVec4f *)&a3, (igVec4f *)&a4, (igVec4f *)&a5);
    FUN_0018c640(temp_s2_7, &a1);
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)))->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)))->_persistent = 0;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)));
    b5.x = 0; b5.y = 0; b5.z = 0; b5.w = 0x3F800000;
    b4.x = 0; b4.y = 0; b4.z = 0x3F800000; b4.w = 0;
    b3.x = 0; b3.y = 0x3F800000; b3.z = 0; b3.w = 0;
    b2.x = 0x3F800000; b2.y = 0; b2.z = 0; b2.w = 0;
    igMatrix44f_FromRows((float *)&b1, (igVec4f *)&b2, (igVec4f *)&b3, (igVec4f *)&b4, (igVec4f *)&b5);
    FUN_0018c640(temp_s2_8, &b1);
    ((igMetaField *)temp_s2_8)->_persistent = 0;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)));
    c5.x = 0; c5.y = 0; c5.z = 0; c5.w = 0x3F800000;
    c4.x = 0; c4.y = 0; c4.z = 0x3F800000; c4.w = 0;
    c3.x = 0; c3.y = 0x3F800000; c3.z = 0; c3.w = 0;
    c2.x = 0x3F800000; c2.y = 0; c2.z = 0; c2.w = 0;
    igMatrix44f_FromRows((float *)&c1, (igVec4f *)&c2, (igVec4f *)&c3, (igVec4f *)&c4, (igVec4f *)&c5);
    FUN_0018c640(temp_s2_9, &c1);
    ((igMetaField *)temp_s2_9)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)));
    igBoolMetaField_SetDefaultValue(temp_v0, 1);
    ((igMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)));
    igBoolMetaField_SetDefaultValue(temp_v0_2, 1);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igActor_fieldTable, g_igActor_fieldHandles, g_igActor_fieldOffsets, temp_s1);
}

