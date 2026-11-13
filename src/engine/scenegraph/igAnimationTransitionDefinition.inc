igMetaObject *igAnimationTransitionDefinition_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionDefinition_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a96c0();
    return g_igAnimationTransitionDefinition_metaObject[0];
}

int igAnimationTransitionDefinition_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *p1;
    S_ref *p2;
    S_ref *t1;
    S_ref *t2;

    igObject_InitHeader(u.b);
    p1 = (S_ref *)&u.b[16];
    p2 = (S_ref *)&u.b[12];
    u.vt = (int)&DAT_00529a30[0];
    *(int *)p2 = 0;
    *(int *)p1 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00529a30[0];
    if (p1 != 0) {
        t1 = *(S_ref **)p1;
        if (t1 != 0) {
            t1->f4 = (int)((int) (t1->f4 - 1));
            if (((unsigned long long) ((long long) t1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)t1);
            }
        }
    }
    if (p2 != 0) {
        t2 = *(S_ref **)p2;
        if (t2 != 0) {
            t2->f4 = (int)((int) (t2->f4 - 1));
            if (((unsigned long long) ((long long) t2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)t2);
            }
        }
    }
    return temp_s0;
}

void FUN_001a96c0(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionDefinition_Register);
}

void igAnimationTransitionDefinition_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationTransitionDefinition_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionDefinition_GetMetaObject,
        igAnimationTransitionDefinition_className,
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

void igAnimationTransitionDefinition_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationTransitionDefinition_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAnimationTransitionDefinition_ctorTable[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a9130();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_001a9830();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_001a9bb0();
    igMetaObject_NameFields(temp_s0, &g_igAnimationTransitionDefinition_fieldTable[0], &DAT_0048d5d0[0], &DAT_0048d5e0[0], temp_s2);
}

