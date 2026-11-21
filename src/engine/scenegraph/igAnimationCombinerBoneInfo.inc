igMetaObject *g_igAnimationCombinerBoneInfo_metaObject;
igMetaField *g_igAnimationCombinerBoneInfo_animationStateMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_transformSourceMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_constantQuaternionMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_constantTranslationMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_priorityMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_useAnimationTranslationMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_lastKeyframeMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_reflectMetaField;

void igAnimationCombinerBoneInfo_Create(int arg0) {
    igAnimationCombinerBoneInfo_EnsureRegistered();
    igMetaObject_CreateInstance(g_igAnimationCombinerBoneInfo_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igAnimationCombinerBoneInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationCombinerBoneInfo_EnsureRegistered();
    return g_igAnimationCombinerBoneInfo_metaObject;
}

int igAnimationCombinerBoneInfo_GetVTable(void) {
    struct Obj_1a8140 o;
    int r;
    int *t;
    int *p;
    int c;
    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igAnimationCombinerBoneInfo_vtable[0];
    o.m12 = 0;
    o.m16 = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igAnimationCombinerBoneInfo_vtable[0];
    if (&o.m16 != 0) {
        t = o.m16;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
    }
    if (&o.m12 != 0) {
        t = o.m12;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
    }
    return r;
}

void igAnimationCombinerBoneInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerBoneInfo_Register);
}

static igMetaObjectCallback g_igAnimationCombinerBoneInfo_callbackList[] = { igAnimationState_EnsureRegistered, igTransformSource_EnsureRegistered, 0 };

CallbackArray *igAnimationCombinerBoneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationCombinerBoneInfo_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igAnimationCombinerBoneInfo_GetMetaObjectFunction,
        "igAnimationCombinerBoneInfo",
        0x3C, /* instance size */
        igAnimationCombinerBoneInfo_GetVTable,
        &igAnimationCombinerBoneInfo_InitFields,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfo_callbackList /* callback list */
    );
}

void igAnimationCombinerBoneInfo_GetMetaObjectFunction(void) {
    igAnimationCombinerBoneInfo_GetMetaObject();
}

static FieldFactory g_igAnimationCombinerBoneInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igAnimationCombinerBoneInfo_fieldTable[] = {
    "_animationState",
    "_transformSource",
    "_constantQuaternion",
    "_constantTranslation",
    "_priority",
    "_useAnimationTranslation",
    "_lastKeyframe",
    "_reflect",
};
static igMetaField **g_igAnimationCombinerBoneInfo_fieldHandles[] = {
    &g_igAnimationCombinerBoneInfo_animationStateMetaField,
    &g_igAnimationCombinerBoneInfo_transformSourceMetaField,
    &g_igAnimationCombinerBoneInfo_constantQuaternionMetaField,
    &g_igAnimationCombinerBoneInfo_constantTranslationMetaField,
    &g_igAnimationCombinerBoneInfo_priorityMetaField,
    &g_igAnimationCombinerBoneInfo_useAnimationTranslationMetaField,
    &g_igAnimationCombinerBoneInfo_lastKeyframeMetaField,
    &g_igAnimationCombinerBoneInfo_reflectMetaField,
};
static int g_igAnimationCombinerBoneInfo_fieldOffsets[] = {
    12,
    16,
    20,
    36,
    48,
    52,
    8,
    56,
};

void igAnimationCombinerBoneInfo_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationCombinerBoneInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationCombinerBoneInfo_ctorTable, 8);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)igAnimationState_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s1) + 36) = 2;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    *(int *)((char *)(temp_s1_2) + 56) = (int)igTransformSource_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s1_2) + 36) = 2;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 6)));
    ((Gap::Core::igIntMetaField *)temp_v0)->setDefault(1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 7)))->setDefault(-1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationCombinerBoneInfo_fieldTable, g_igAnimationCombinerBoneInfo_fieldHandles, g_igAnimationCombinerBoneInfo_fieldOffsets, temp_s2);
}

