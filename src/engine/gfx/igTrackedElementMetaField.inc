igMetaObject *g_igTrackedElementMetaField_metaObject;

igMetaObject *igTrackedElementMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igTrackedElementMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTrackedElementMetaField_EnsureRegistered();
    return g_igTrackedElementMetaField_metaObject;
}

int igTrackedElementMetaField_GetVTable(void) {
    union U_14e350 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)u.b);
    u.vt = (int)&g_igCompoundMetaField_vtable[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&g_igTrackedElementMetaField_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.vt = (int)&g_igCompoundMetaField_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
            }
        }
    }
    q1 = &u.b[12];
    u.vt = (int)&g_igMetaField_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
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

igSmartPointer<igObject> *igSmartPointer_igMetaFieldList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void igTrackedElementMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTrackedElementMetaField_Register);
}

static igMetaObjectCallback g_igTrackedElementMetaField_callbackList[] = { FUN_0014e540, 0 };

CallbackArray *igTrackedElementMetaField_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTrackedElementMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igTrackedElementMetaField_GetMetaObject,
        "igTrackedElementMetaField",
        0x38, /* instance size */
        igTrackedElementMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igTrackedElementMetaField_callbackList /* callback list */
    );
}

void thunk_igTrackedElementMetaField_GetMetaObject(void) {
    igTrackedElementMetaField_GetMetaObject();
}

int FUN_0014e530(void) {
    return g_igCompoundMetaField_metaObject[0];
}

Q * g_igTrackedElementMetaField_instance;

void FUN_0014e540(void) {
    Q *temp_s0;
    Q *p;

    if (g_igTrackedElementMetaField_instance == 0) {
        g_igTrackedElementMetaField_instance = (Q *)igMetaObject_CreateInstance(g_igTrackedElementMetaField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
        temp_s0 = g_igTrackedElementMetaField_instance;
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), temp_s0);
            p = g_igTrackedElementMetaField_instance;
            p->f4 -= 1;
            if ((p->f4 & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)p);
            }
            g_igTrackedElementMetaField_instance->f18 = ((R_14e540 *)igMetaField_GetMetaFieldList())->f12 - 1;
            igMetaField_FinalizeDescriptor((igMetaField *)g_igTrackedElementMetaField_instance);
        }
    }
}

int Gap__Gfx__igTrackedElementMetaField__vfunc_25(void) {
    return 0xC;
}

void Gap__Gfx__igTrackedElementMetaField__vfunc_11(void *arg0) {
    FUN_0014e630(*(int *)((char *)arg0 + 52));
}

void FUN_0014e630(int arg0) {
    void *sp3C;
    void *sp38;
    void *sp34;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int var_v0_2;
    int var_v0_4;
    int var_v0_6;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *var_v0;
    void *var_v0_3;
    void *var_v0_5;

    temp_s0 = (void *)(igEnumMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("which" == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_2 = (int)StringPool_Allocate(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = (int)StringPool_Construct((StringPool *)var_v0_2);
            }
            g_stringPool = (StringPool *)var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(g_stringPool, "which"));
    }
    sp3C = (void *)(var_v0);
    igMetaField_SetFieldName((igMetaField *)temp_s0, &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
        }
    }
    *(int *)((char *)(temp_s0) + 8) = 0;
    *(int *)((char *)(temp_s0) + 52) = (int)(&FUN_0014e2a0);
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
    temp_s0_2 = (void *)(igIntMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("place" == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_4 = (int)StringPool_Allocate(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = (int)StringPool_Construct((StringPool *)var_v0_4);
            }
            g_stringPool = (StringPool *)var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(g_stringPool, "place"));
    }
    sp38 = (void *)(var_v0_3);
    igMetaField_SetFieldName((igMetaField *)temp_s0_2, &sp38);
    if (sp38 != 0) {
        temp_a1_2 = (int *)((char *)sp38 - 8);
        temp_v0_2 = *(int *)((char *)(sp38) - 4) - 1;
        *(int *)((char *)(sp38) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*temp_a1_2, (StringTokenHeader *)temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s0_2) + 8) = 4;
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0_2);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0_2);
    *(int *)((char *)(temp_s0_2) + 4) = (int)((int) (*(int *)((char *)(temp_s0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0_2);
    }
    temp_s0_3 = (void *)(igIntMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("arg0" == 0) {
        var_v0_5 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_6 = (int)StringPool_Allocate(0x10);
            if (var_v0_6 != 0) {
                var_v0_6 = (int)StringPool_Construct((StringPool *)var_v0_6);
            }
            g_stringPool = (StringPool *)var_v0_6;
        }
        var_v0_5 = (void *)(StringPool_Intern(g_stringPool, "arg0"));
    }
    sp34 = (void *)(var_v0_5);
    igMetaField_SetFieldName((igMetaField *)temp_s0_3, &sp34);
    if (sp34 != 0) {
        temp_a1_3 = (int *)((char *)sp34 - 8);
        temp_v0_3 = *(int *)((char *)(sp34) - 4) - 1;
        *(int *)((char *)(sp34) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*temp_a1_3, (StringTokenHeader *)temp_a1_3);
        }
    }
    *(int *)((char *)(temp_s0_3) + 8) = 8;
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0_3);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0_3);
    *(int *)((char *)(temp_s0_3) + 4) = (int)((int) (*(int *)((char *)(temp_s0_3) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_3) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0_3);
    }
}

