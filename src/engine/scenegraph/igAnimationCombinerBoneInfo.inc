igMetaObject *g_igAnimationCombinerBoneInfo_metaObject;
igMetaField *g_igAnimationCombinerBoneInfo_animationStateMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_transformSourceMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_constantQuaternionMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_constantTranslationMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_priorityMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_useAnimationTranslationMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_lastKeyframeMetaField;
igMetaField *g_igAnimationCombinerBoneInfo_reflectMetaField;

void FUN_001a80b0(int arg0) {
    FUN_001a8220();
    igMetaObject_CreateInstance(g_igAnimationCombinerBoneInfo_metaObject, arg0);
}

igMetaObject *igAnimationCombinerBoneInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8220();
    return g_igAnimationCombinerBoneInfo_metaObject;
}

int igAnimationCombinerBoneInfo_GetVTable(void) {
    struct Obj_1a8140 o;
    int r;
    int *t;
    int *p;
    int c;
    igObject_InitHeader(&o);
    o.vt = &g_igAnimationCombinerBoneInfo_vtable[0];
    o.m12 = 0;
    o.m16 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igAnimationCombinerBoneInfo_vtable[0];
    if (&o.m16 != 0) {
        t = o.m16;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)t);
            }
        }
    }
    if (&o.m12 != 0) {
        t = o.m12;
        if (t != 0) {
            t[1] = t[1] - 1;
            if ((t[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)t);
            }
        }
    }
    return r;
}

void FUN_001a8220(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerBoneInfo_Register);
}

static igMetaObjectCallback g_igAnimationCombinerBoneInfo_callbackList[] = { FUN_001a6dc0, FUN_00194e70, 0 };

void igAnimationCombinerBoneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationCombinerBoneInfo_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationCombinerBoneInfo_GetMetaObject,
        "igAnimationCombinerBoneInfo",
        0x3C, /* instance size */
        igAnimationCombinerBoneInfo_GetVTable,
        &igAnimationCombinerBoneInfo_InitFields,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfo_callbackList /* callback list */
    );
}

void thunk_igAnimationCombinerBoneInfo_GetMetaObject(void) {
    igAnimationCombinerBoneInfo_GetMetaObject();
}

static FieldFactory g_igAnimationCombinerBoneInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    FUN_001872a0,
    FUN_00187890,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
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
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationCombinerBoneInfo_ctorTable, 8);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_001a6bf0();
    *(char *)((char *)(temp_s1) + 36) = 2;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_00194dd0();
    *(char *)((char *)(temp_s1_2) + 36) = 2;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)));
    igIntMetaField_SetDefault(temp_v0, 1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    igIntMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7)), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationCombinerBoneInfo_fieldTable, g_igAnimationCombinerBoneInfo_fieldHandles, g_igAnimationCombinerBoneInfo_fieldOffsets, temp_s2);
}

