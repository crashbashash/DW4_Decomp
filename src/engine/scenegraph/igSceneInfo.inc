igSceneInfo *igSceneInfo_CreateInstance(int allocator) {
    igSceneInfo_EnsureRegistered();
    return (igSceneInfo *)igMetaObject_CreateInstance((igMetaObject *)g_igSceneInfo_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *g_igSceneInfo_metaObject;
igMetaField *g_igSceneInfo_sceneGraphMetaField;
igMetaField *g_igSceneInfo_texturesMetaField;
igMetaField *g_igSceneInfo_camerasMetaField;
igMetaField *g_igSceneInfo_animationBeginMetaField;
igMetaField *g_igSceneInfo_animationEndMetaField;
igMetaField *g_igSceneInfo_upVectorMetaField;
igMetaField *g_igSceneInfo_sceneGraphListMetaField;

igMetaObject *igSceneInfo_GetOrCreateMetaObject(void) {
    if (g_igSceneInfo_metaObject == 0) {
        g_igSceneInfo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSceneInfo_metaObject;
}

igMetaObject *igSceneInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igSceneInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSceneInfo_EnsureRegistered();
    return g_igSceneInfo_metaObject;
}

int igSceneInfo_GetVTable(void) {
    struct Obj_19af80 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.vt = &g_igSceneInfo_vtable[0];
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w15 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj.vt = &g_igSceneInfo_vtable[0];
    igSmartPointer_igNodeList_Destruct((igSmartPointer<igObject> *)&obj.w15, -1);
    FUN_0019b1f0((void * *)&obj.w7, -1);
    igSmartPointer_igTextureList_Destruct((igSmartPointer<igObject> *)&obj.w6, -1);
    igSmartPointer_igNode_Destruct((igSmartPointer<igObject> *)&obj.w5, -1);
    igInfo_Destroy((igInfo *)&obj, 0);
    return t;
}

void *igSceneInfo_Destroy(igSceneInfo *arg0, short arg1) {
    igObject *p;
    int rc;
    int *hd;

    if (arg0 != 0) {
        arg0->_vtable = (int)  &g_igSceneInfo_vtable[0];
        if (&arg0->_sceneGraphList) {
            p = (igObject *)arg0->_sceneGraphList;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (&arg0->_cameras) {
            p = (igObject *)arg0->_cameras;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (&arg0->_textures) {
            p = (igObject *)arg0->_textures;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (&arg0->_sceneGraph) {
            p = (igObject *)arg0->_sceneGraph;
            if (p != 0) {
                rc = p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int) p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->_vtable = (int)  &g_igInfo_vtable[0];
            if (arg0 != 0) {
                arg0->_vtable = (int)  &g_igNamedObject_vtable[0];
                if (&arg0->_name) {
                    p = (igObject *)arg0->_name;
                    if (p != 0) {
                        hd = (int *)((char *)p - 8);
                        rc = *(int *)((char *)p - 4) - 1;
                        *(int *)((char *)p - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                        }
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
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
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void igSceneInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((CallbackArray * (*)())igSceneInfo_Register);
}

static igMetaObjectCallback g_igSceneInfo_callbackList[] = { igNode_EnsureRegistered, igTextureList_EnsureRegistered, igGraphPathList_EnsureRegistered, igNodeList_EnsureRegistered, 0 };

CallbackArray *igSceneInfo_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSceneInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igSceneInfo_GetMetaObject,
        "igSceneInfo",
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

static FieldFactory g_igSceneInfo_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igSceneInfo_fieldTable[] = {
    "_sceneGraph",
    "_textures",
    "_cameras",
    "_animationBegin",
    "_animationEnd",
    "_upVector",
    "_sceneGraphList",
};
static igMetaField **g_igSceneInfo_fieldHandles[] = {
    &g_igSceneInfo_sceneGraphMetaField,
    &g_igSceneInfo_texturesMetaField,
    &g_igSceneInfo_camerasMetaField,
    &g_igSceneInfo_animationBeginMetaField,
    &g_igSceneInfo_animationEndMetaField,
    &g_igSceneInfo_upVectorMetaField,
    &g_igSceneInfo_sceneGraphListMetaField,
};
static int g_igSceneInfo_fieldOffsets[] = {
    20,
    24,
    28,
    32,
    40,
    48,
    60,
};

void igSceneInfo_InitFields(void) {
    struct V3 v;
    int temp_s1;
    void *temp_a0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s0;

    temp_s0 = (void *)g_igSceneInfo_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igSceneInfo_ctorTable, 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igNode_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igTextureList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    ((igMetaField *)temp_s2_2)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s2_2)->_shallowCopyMethod = 2;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0019f4c0();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    ((igMetaField *)temp_s2_3)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s2_3)->_shallowCopyMethod = 2;
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    v.x = 0;
    v.y = 0x3F800000;
    v.z = 0;
    igVec3fMetaField_SetDefault((igMetaField *)temp_a0, (const float *)&v);
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igNodeList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igSceneInfo_fieldTable, g_igSceneInfo_fieldHandles, g_igSceneInfo_fieldOffsets, temp_s1);
}

