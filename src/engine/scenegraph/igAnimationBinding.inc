int FUN_001a8c30(int arg0) {
    FUN_001a8df0();
    return igMetaObject_CreateInstance(*(int *)0x562338, arg0);
}

igMetaObject *igAnimationBinding_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationBinding_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8df0();
    return g_igAnimationBinding_metaObject[0];
}

int igAnimationBinding_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    S_ref *q2;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00529b70[0];
    q2 = (S_ref *)&u.b[8];
    *(int *)q2 = 0;
    q1 = (S_ref *)&u.b[20];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[24];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00529b70[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q1);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q2);
            }
        }
    }
    return temp_s0;
}

void FUN_001a8df0(void)
{
    igMetaObject_RunStaticInit(igAnimationBinding_Register);
}

void igAnimationBinding_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationBinding_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationBinding_GetMetaObject,
        igAnimationBinding_className,
        0x1C, /* instance size */
        igAnimationBinding_GetVTable,
        &igAnimationBinding_InitFields,
        0, /* extra callback item */
        g_igAnimationBinding_callbackList /* callback list */
    );
}

void thunk_igAnimationBinding_GetMetaObject(void) {
    igAnimationBinding_GetMetaObject();
}

void igAnimationBinding_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationBinding_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d470[0], 5);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a7100();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igMemoryRefMetaField *)temp_s1_2)->_memType = igIntMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1_2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnReset = 1;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s1_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = (int)FUN_001a4d90();
    igMetaObject_NameFields(temp_s0, &DAT_0048d490[0], &DAT_0048d4b0[0], &DAT_0048d4d0[0], temp_s2);
}

