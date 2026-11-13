void FUN_0019aea0(int arg0) {
    FUN_0019b270();
    igMetaObject_CreateInstance(*(int *)0x5615E0, arg0);
}

igMetaObject *FUN_0019aee0(void) {
    if (g_igSceneInfo_metaObject[0] == 0) {
        g_igSceneInfo_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igSceneInfo_metaObject[0];
}

igMetaObject *igSceneInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igSceneInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019b270();
    return g_igSceneInfo_metaObject[0];
}

int igSceneInfo_GetVTable(void) {
    struct Obj_19af80 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_005288e0[0];
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w15 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_005288e0[0];
    FUN_001958f0((void * *)&obj.w15, -1);
    FUN_0019b1f0((void * *)&obj.w7, -1);
    FUN_00131aa0(&obj.w6, -1);
    FUN_00198210((ObjectRefWord *)&obj.w5, -1);
    FUN_00131b20(&obj, 0);
    return t;
}

void *FUN_0019b040(igSceneInfo *arg0, short arg1) {
    igObject *p;
    int rc;
    int *hd;

    if (arg0 != 0) {
        arg0->_vtable = (int)  &DAT_005288e0[0];
        if (&arg0->_sceneGraphList) {
            p = (igObject *)arg0->_sceneGraphList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (&arg0->_cameras) {
            p = (igObject *)arg0->_cameras;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (&arg0->_textures) {
            p = (igObject *)arg0->_textures;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (&arg0->_sceneGraph) {
            p = (igObject *)arg0->_sceneGraph;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->_vtable = (int)  &DAT_0052fde0[0];
            if (arg0 != 0) {
                arg0->_vtable = (int)  &g_igNamedObject_vtable[0];
                if (&arg0->_name) {
                    p = (igObject *)arg0->_name;
                    if (p != 0) {
                        hd = (int *)((char *)p - 8);
                        rc = *(int *)((char *)p - 4) - 1;
                        *(int *)((char *)p - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*hd, hd);
                        }
                    }
                }
            }
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_0019b1f0(void **arg0, short arg1) {
    S_temp_a0_19b1f0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_19b1f0 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_0019b270(void)
{
    igMetaObject_RunStaticInit(igSceneInfo_Register);
}

void igSceneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igSceneInfo_metaObject),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igSceneInfo_GetMetaObject,
        igSceneInfo_className,
        0x40, /* instance size */
        igSceneInfo_GetVTable,
        &igSceneInfo_InitFields,
        0, /* extra callback item */
        g_igSceneInfo_callbackList /* callback list */
    );
}

void thunk_igSceneInfo_GetMetaObject(void) {
    igSceneInfo_GetMetaObject();
}

void igSceneInfo_InitFields(void) {
    struct V3 v;
    int temp_s1;
    void *temp_a0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s0;

    temp_s0 = (void *)g_igSceneInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igSceneInfo_ctorTable[0], 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0019cd50();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0013a360();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    ((igMetaField *)temp_s2_2)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s2_2)->_shallowCopyMethod = 2;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0019f4c0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    ((igMetaField *)temp_s2_3)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s2_3)->_shallowCopyMethod = 2;
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)));
    v.x = 0;
    v.y = 0x3F800000;
    v.z = 0;
    FUN_0018e470(temp_a0, &v);
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_0019cbe0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_igSceneInfo_fieldTable[0], &DAT_0048b7c0[0], &DAT_0048b7e0[0], temp_s1);
}

