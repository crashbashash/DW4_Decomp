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

igMetaObject *igActor_GetOrCreateMetaObject(void) {
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
    return *(int *)((char *)&actor + g_objectSystem->vtableProbeOffset);
}

void **igSmartPointer_igAnimationSystem_Destruct(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy((igObject *)p);
        }
        if (flag > 0) operator delete(self);
    }
    return (void **)self;
}

void **igSmartPointer_igAppearance_Destruct(void **arg0, long long arg1) {
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

O *igSmartPointer_igAnimationModifierList_Destruct(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy((igObject *)t); }
        if (arg1 > 0) operator delete(arg0);
    }
    return arg0;
}

void igActor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igActor_Register);
}

static igMetaObjectCallback g_igActor_callbackList[] = { igAnimationSystem_EnsureRegistered, igAppearance_EnsureRegistered, igAnimationDatabase_EnsureRegistered, Gap::Sg::igAnimationModifierList::arkRegister, 0 };

CallbackArray *igActor_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igActor_metaObject,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        igActor_GetMetaObjectFunction,
        "igActor",
        0x100, /* instance size */
        igActor_GetVTable,
        &igActor_InitFields,
        0, /* extra callback item */
        g_igActor_callbackList /* callback list */
    );
}

void igActor_GetMetaObjectFunction(void) {
    igActor_GetMetaObject();
}

static FieldFactory g_igActor_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool,
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
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igAnimationSystem_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igMemoryRefMetaField *)temp_s2_2)->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
    ((igRefMetaField *)temp_s2_2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_2)->_releaseOnReset = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igMemoryRefMetaField *)temp_s2_3)->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
    ((igRefMetaField *)temp_s2_3)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s2_3)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s2_3)->_releaseOnReset = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igAppearance_GetOrCreateMetaObject();
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igAnimationDatabase_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)Gap::Sg::igAnimationModifierList::getClassTypeLazy();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_7)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                       igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)))->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)))->_persistent = 0;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_8)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                       igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    ((igMetaField *)temp_s2_8)->_persistent = 0;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)));
    ((Gap::Math::igMatrix44fMetaField *)temp_s2_9)->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                       igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    ((igMetaField *)temp_s2_9)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)));
    ((Gap::Core::igBoolMetaField *)temp_v0)->setDefault(1);
    ((igMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC)));
    ((Gap::Core::igBoolMetaField *)temp_v0_2)->setDefault(1);
    ((igMetaField *)temp_v0_2)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igActor_fieldTable, g_igActor_fieldHandles, g_igActor_fieldOffsets, temp_s1);
}

