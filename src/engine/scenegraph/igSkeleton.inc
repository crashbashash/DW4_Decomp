igMetaObject *g_igSkeleton_metaObject;
igMetaField *g_igSkeleton_boneInfoListMetaField;
igMetaField *g_igSkeleton_invJointArrayMetaField;
igMetaField *g_igSkeleton_jointCountMetaField;

igMetaObject *FUN_00198550(void)
{
    igMetaObject *g = g_igSkeleton_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSkeleton_EnsureRegistered();
    return g_igSkeleton_metaObject;
}

int igSkeleton_GetVTable(void) {
    union U u;
    int temp_s1;
    int *ps;
    int *pr;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = (int *)&u.b[8];
    *ps = 0;
    u.vt = (int)&g_igSkeleton_vtable[0];
    pr = (int *)&u.b[16];
    *pr = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igSkeleton_vtable[0];
    if (pr != 0) {
        o = (char *)*pr;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = (int *)*ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void igSkeleton_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSkeleton_Register);
}

static igMetaObjectCallback g_igSkeleton_callbackList[] = { igSkeletonBoneInfoList_EnsureRegistered, 0 };

void igSkeleton_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSkeleton_metaObject,
        igAnimationHierarchy_Register,
        igAnimationHierarchy_GetPublishedMetaObject,
        thunk_FUN_00198550,
        "igSkeleton",
        sizeof(igSkeleton),                                   /* Instance size. */
        igSkeleton_GetVTable,
        &igSkeleton_InitFields,
        0, /* extra callback item */
        g_igSkeleton_callbackList /* callback list */
    );
}

void thunk_FUN_00198550(void) {
    FUN_00198550();
}

igMetaObject *g_igAnimationHierarchy_metaObject;
igMetaField *g_igAnimationHierarchy_boneTranslationArrayMetaField;

igMetaObject *FUN_00198720(void) {
    return g_igAnimationHierarchy_metaObject;
}

static FieldFactory g_igSkeleton_ctorTable[] = {
    igObjectRefMetaField_Create,
    igMemoryRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igSkeleton_fieldTable[] = {
    "_boneInfoList",
    "_invJointArray",
    "_jointCount",
};
static igMetaField **g_igSkeleton_fieldHandles[] = {
    &g_igSkeleton_boneInfoListMetaField,
    &g_igSkeleton_invJointArrayMetaField,
    &g_igSkeleton_jointCountMetaField,
};
static int g_igSkeleton_fieldOffsets[] = {
    16,
    20,
    24,
};

void igSkeleton_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSkeleton_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igSkeleton_ctorTable, 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001987f0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igMemoryRefMetaField *)temp_s1_2)->_memType = FUN_001888e0();
    ((igRefMetaField *)temp_s1_2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igSkeleton_fieldTable, g_igSkeleton_fieldHandles, g_igSkeleton_fieldOffsets, temp_s2);
}

