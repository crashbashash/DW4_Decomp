igMetaObject *FUN_0019cd50(void) {
    if (g_igNode_metaObject[0] == 0) {
        g_igNode_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igNode_metaObject[0];
}

igMetaObject *igNode_GetMetaObject(void)
{
    igMetaObject *g = g_igNode_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019cf10();
    return g_igNode_metaObject[0];
}

int igNode_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    char *q2;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    q2 = &u.b[8];
    *(int *)q2 = 0;
    u.vt = (int)&DAT_00528a90[0];
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00528a90[0];
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
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q2 != 0) {
        temp_v1 = *(int **)q2;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_0019cf10(void)
{
    igMetaObject_RunStaticInit(igNode_Register);
}

void igNode_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNode_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igNode_GetMetaObject,
        igNode_className,
        0x1C, /* instance size */
        igNode_GetVTable,
        &igNode_InitFields,
        0, /* extra callback item */
        g_igNode_callbackList /* callback list */
    );
}

void thunk_igNode_GetMetaObject(void) {
    igNode_GetMetaObject();
}

void igNode_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;
    void *temp_s1;

    temp_s1 = (void *)g_igNode_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igNode_ctorTable[0], 4);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00186a80();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_0019c8c0();
    ((igObjectRefMetaField *)temp_s2_2)->_resetMethod = 3;
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_2)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_2)->_deepCopyMethod = 4;
    ((igObjectRefMetaField *)temp_s2_2)->_shallowCopyMethod = 4;
    ((igObjectRefMetaField *)temp_s2_2)->_constructCopyMethod = 4;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    igIntMetaField_SetDefault(temp_v0, -1);
    ((igIntMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s1, &g_igNode_fieldTable[0], &DAT_0048bcb0[0], &DAT_0048bcc0[0], temp_s0);
}

void **FUN_0019d0a0(void **arg0, long long arg1) {
    struct Rc *a;
    if (arg0 != 0) {
        a = (struct Rc *)*arg0;
        if (a != 0) { a->rc = a->rc - 1; if ((a->rc & 0x7FFFFF) == 0) { igObject_Destroy((void *)a); } }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void *FUN_0019d120(struct S_19d120 *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_00528e70[0];
        if (&arg0->f28) {
            p = arg0->f28;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_005294b0[0];
            FUN_0013bfe0((char *)arg0 + 0x20, -1);
            FUN_00195a90((struct T_195a90 *)arg0, 0);
        }
        if (arg1 > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

igMetaObject *FUN_0019d1e0(void) {
    return g_igGeometry_metaObject[0];
}

int *FUN_0019d1f0(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void **FUN_0019d200(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

igMetaObject *FUN_0019d280(void) {
    if (g_igModelViewMatrixBoneSelectList_metaObject_00561880[0] == 0) {
        g_igModelViewMatrixBoneSelectList_metaObject_00561880[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igModelViewMatrixBoneSelectList_metaObject_00561880[0];
}

