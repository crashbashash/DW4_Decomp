static const char *g_igShaderFactory_fileCachingModeNames[] = {
    "NO_CACHING", "NON_PERSISTENT_CACHE", "PERSISTENT_CACHE", "GLOBAL_CACHE",
};
static int g_igShaderFactory_fileCachingModeValues[] = {
    0, 1, 2, 3,
};
igMetaEnum *g_igShaderFactory_fileCachingModeMetaEnum;

igMetaEnum *FUN_00199110(void) {
    if (g_igShaderFactory_fileCachingModeMetaEnum == 0) {
        g_igShaderFactory_fileCachingModeMetaEnum = igMetaEnum_Create("FILE_CACHING_MODE", g_igShaderFactory_fileCachingModeNames, g_igShaderFactory_fileCachingModeValues, 4);
    }
    return g_igShaderFactory_fileCachingModeMetaEnum;
}

igMetaObject *g_igShaderFactory_metaObject;
igMetaField *g_igShaderFactory_attrNamesMetaField;
igMetaField *g_igShaderFactory_attrTypesMetaField;
igMetaField *g_igShaderFactory_fileCachingModeMetaField;

igMetaObject *FUN_00199170(void) {
    if (g_igShaderFactory_metaObject == 0) {
        g_igShaderFactory_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igShaderFactory_metaObject;
}

igMetaObject *igShaderFactory_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderFactory_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001994d0();
    return g_igShaderFactory_metaObject;
}

int igShaderFactory_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;
    char *q2;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader((igObject *)u.b);
    q2 = &u.b[8];
    *(int *)q2 = 0;
    u.vt = (int)&g_igShaderFactory_vtable[0];
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    q0 = (S_ref *)&u.b[16];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.vt = (int)&g_igShaderFactory_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q1);
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
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void *FUN_00199330(struct T_199330 *arg0, long long arg1) {
    struct Rc *o;
    int *a1;
    int v0;
    if (arg0 != 0) {
        arg0->vt = &g_igShaderFactory_vtable[0];
        if (&arg0->f16 != 0) {
            o = arg0->f16;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)o);
                }
            }
        }
        if (&arg0->f12 != 0) {
            o = arg0->f12;
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)o);
                }
            }
        }
        if (arg0 != 0) {
            arg0->vt = &g_igNamedObject_vtable[0];
            if (&arg0->f8 != 0) {
                char *p = arg0->f8;
                if (p != 0) {
                    a1 = (int *)(p - 8);
                    v0 = *(int *)(p - 4) - 1;
                    *(int *)(p - 4) = v0;
                    if (v0 == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
                    }
                }
            }
        }
        if ((short)arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void **igSmartPointer_igNamedObjectList_Destruct(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void FUN_001994d0(void)
{
    igMetaObject_RunStaticInit(igShaderFactory_Register);
}

static igMetaObjectCallback g_igShaderFactory_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

CallbackArray *igShaderFactory_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igShaderFactory_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igShaderFactory_GetMetaObject,
        "igShaderFactory",
        0x18, /* instance size */
        igShaderFactory_GetVTable,
        &igShaderFactory_InitFields,
        0, /* extra callback item */
        g_igShaderFactory_callbackList /* callback list */
    );
}

void thunk_igShaderFactory_GetMetaObject(void) {
    igShaderFactory_GetMetaObject();
}

static FieldFactory g_igShaderFactory_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igShaderFactory_fieldTable[] = {
    "_attrNames",
    "_attrTypes",
    "_fileCachingMode",
};
static igMetaField **g_igShaderFactory_fieldHandles[] = {
    &g_igShaderFactory_attrNamesMetaField,
    &g_igShaderFactory_attrTypesMetaField,
    &g_igShaderFactory_fileCachingModeMetaField,
};
static int g_igShaderFactory_fieldOffsets[] = {
    12,
    16,
    20,
};

void igShaderFactory_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igShaderFactory_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igShaderFactory_ctorTable, 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    *(int *)((char *)(temp_s1) + 56) = (int)igNamedObjectList_GetOrCreateMetaObject();
    *(unsigned char *)((char *)(temp_s1) + 52) = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    *(int *)((char *)(temp_s1_2) + 56) = (int)igNamedObjectList_GetOrCreateMetaObject();
    *(unsigned char *)((char *)(temp_s1_2) + 52) = 1;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    igEnumMetaField_SetDefaultValue((igMetaField *)temp_v0, 3);
    *(int *)((char *)(temp_v0) + 52) = (int)(FUN_00199110);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igShaderFactory_fieldTable, g_igShaderFactory_fieldHandles, g_igShaderFactory_fieldOffsets, temp_s2);
}

