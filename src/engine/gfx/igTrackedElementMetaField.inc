igMetaObject *igTrackedElementMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igTrackedElementMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014e4a0();
    return g_igTrackedElementMetaField_metaObject[0];
}

int igTrackedElementMetaField_GetVTable(void) {
    union U_14e350 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init(u.b);
    u.vt = (int)&DAT_00531740[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00526ec0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00531740[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    q1 = &u.b[12];
    u.vt = (int)&DAT_0052f230[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
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

ObjectRefWord *FUN_0014e420(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void FUN_0014e4a0(void)
{
    igMetaObject_RunStaticInit(igTrackedElementMetaField_Register);
}

void igTrackedElementMetaField_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTrackedElementMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igTrackedElementMetaField_GetMetaObject,
        igTrackedElementMetaField_className,
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
    return DAT_00586918[0];
}

void FUN_0014e540(void) {
    Q *temp_s0;
    Q *p;

    if (DAT_0055fe40[0] == 0) {
        DAT_0055fe40[0] = (Q *)igMetaObject_CreateInstance(DAT_0055fe38[0], Memory_GetAllocatorBySelector(DAT_00587040[0]));
        temp_s0 = DAT_0055fe40[0];
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            p = DAT_0055fe40[0];
            p->f4 -= 1;
            if ((p->f4 & 0x7fffff) == 0) {
                igObject_Destroy(p);
            }
            DAT_0055fe40[0]->f18 = FUN_002fc250()->f12 - 1;
            igMetaField_FinalizeDescriptor(DAT_0055fe40[0]);
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

    temp_s0 = (void *)(FUN_002c5fb0(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_004dcc30[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004dcc30[0]));
    }
    sp3C = (void *)(var_v0);
    igMetaField_SetFieldName(temp_s0, &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *(int *)((char *)(temp_s0) + 8) = 0;
    *(int *)((char *)(temp_s0) + 52) = (int)(&FUN_0014e2a0);
    igMetaField_FinalizeDescriptor(temp_s0);
    ObjectList_AppendRetained(arg0, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
    temp_s0_2 = (void *)(igIntMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_004dcc38[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_4 = FUN_002eb010(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = StringPool_Construct(var_v0_4);
            }
            DAT_00586f20[0] = var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004dcc38[0]));
    }
    sp38 = (void *)(var_v0_3);
    igMetaField_SetFieldName(temp_s0_2, &sp38);
    if (sp38 != 0) {
        temp_a1_2 = (int *)((char *)sp38 - 8);
        temp_v0_2 = *(int *)((char *)(sp38) - 4) - 1;
        *(int *)((char *)(sp38) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s0_2) + 8) = 4;
    igMetaField_FinalizeDescriptor(temp_s0_2);
    ObjectList_AppendRetained(arg0, temp_s0_2);
    *(int *)((char *)(temp_s0_2) + 4) = (int)((int) (*(int *)((char *)(temp_s0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0_2);
    }
    temp_s0_3 = (void *)(igIntMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0])));
    if (&DAT_004dcc40[0] == 0) {
        var_v0_5 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_6 = FUN_002eb010(0x10);
            if (var_v0_6 != 0) {
                var_v0_6 = StringPool_Construct(var_v0_6);
            }
            DAT_00586f20[0] = var_v0_6;
        }
        var_v0_5 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004dcc40[0]));
    }
    sp34 = (void *)(var_v0_5);
    igMetaField_SetFieldName(temp_s0_3, &sp34);
    if (sp34 != 0) {
        temp_a1_3 = (int *)((char *)sp34 - 8);
        temp_v0_3 = *(int *)((char *)(sp34) - 4) - 1;
        *(int *)((char *)(sp34) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    *(int *)((char *)(temp_s0_3) + 8) = 8;
    igMetaField_FinalizeDescriptor(temp_s0_3);
    ObjectList_AppendRetained(arg0, temp_s0_3);
    *(int *)((char *)(temp_s0_3) + 4) = (int)((int) (*(int *)((char *)(temp_s0_3) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_3) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0_3);
    }
}

