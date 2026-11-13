void FUN_001a80b0(int arg0) {
    FUN_001a8220();
    igMetaObject_CreateInstance(g_igAnimationCombinerBoneInfo_metaObject[0], arg0);
}

igMetaObject *igAnimationCombinerBoneInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8220();
    return g_igAnimationCombinerBoneInfo_metaObject[0];
}

int igAnimationCombinerBoneInfo_GetVTable(void) {
    struct Obj_1a8140 o;
    int r;
    int *t;
    int *p;
    int c;
    igObject_InitHeader(&o);
    o.vt = &DAT_00529d30[0];
    o.m12 = 0;
    o.m16 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00529d30[0];
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

void igAnimationCombinerBoneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationCombinerBoneInfo_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationCombinerBoneInfo_GetMetaObject,
        igAnimationCombinerBoneInfo_className,
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

void igAnimationCombinerBoneInfo_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationCombinerBoneInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAnimationCombinerBoneInfo_ctorTable[0], 8);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_001a6bf0();
    *(char *)((char *)(temp_s1) + 36) = 2;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_00194dd0();
    *(char *)((char *)(temp_s1_2) + 36) = 2;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)));
    FUN_002ea4b0(temp_v0, 1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    FUN_002ea4b0(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7)), -1);
    igMetaObject_NameFields(temp_s0, &g_igAnimationCombinerBoneInfo_fieldTable[0], &DAT_0048d300[0], &DAT_0048d320[0], temp_s2);
}

