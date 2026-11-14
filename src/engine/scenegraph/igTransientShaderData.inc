igMetaObject *igTransientShaderData_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTransientShaderData_metaObject[0] != 0) {
        ready = (g_igTransientShaderData_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00194a90();
done:
    return g_igTransientShaderData_metaObject[0];
}

int igTransientShaderData_GetVTable(void) {
    struct Obj_194720 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.fC = 0;
    obj.f10 = 0;
    obj.f14 = 0;
    obj.vt = (&DAT_0052b870[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&DAT_0052b870[0]);
    FUN_00194930((Obj_194930 *)&obj, 0);
    return temp_s0;
}

int **FUN_00194790(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_0052b870[0];
        if (arg0 != 0) {
            *arg0 = &DAT_00528870[0];
            FUN_00194830((struct Ref * *)((char *)arg0 + 20), -1);
            FUN_001948b0((void * *)((char *)arg0 + 16), -1);
            FUN_0013a800((char *)arg0 + 12, -1);
            FUN_0013a800((char *)arg0 + 8, -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

void **FUN_00194830(struct Ref **self, short flag) {
    struct Ref *p;
    if (self != 0) {
        p = *self;
        if (p != 0) {
            p->u.w = p->u.w - 1;
            if (p->u.b.cnt == 0) igObject_Destroy(p);
        }
        if (flag > 0) __dl__FPv(self);
    }
    return (void **)self;
}

void **FUN_001948b0(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

Obj_194930 *FUN_00194930(Obj_194930 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00528870[0];
        arg0->rel(&arg0->m20);
        arg0->rel(&arg0->m16);
        arg0->rel(&arg0->m12);
        arg0->rel(&arg0->m8);
        if (arg1 > 0) {
            thunk_Memory_FreeBuffer(arg0);
        }
    }
    return arg0;
}

void FUN_00194a90(void)
{
    igMetaObject_RunStaticInit(igTransientShaderData_Register);
}

void igTransientShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTransientShaderData_metaObject),
        igShaderData_Register,
        igShaderData_GetPublishedMetaObject,
        thunk_igTransientShaderData_GetMetaObject,
        igTransientShaderData_className,
        0x18, /* instance size */
        igTransientShaderData_GetVTable,
        &igTransientShaderData_InitFields,
        0, /* extra callback item */
        g_igTransientShaderData_callbackList /* callback list */
    );
}

void thunk_igTransientShaderData_GetMetaObject(void) {
    igTransientShaderData_GetMetaObject();
}

igMetaObject *FUN_00194b30(void) {
    return g_igShaderData_metaObject[0];
}

void igTransientShaderData_InitFields(void) {
    int temp_s2;
    void **temp_v0;
    T_194b40 *temp_s0;
    M *temp_s1;

    temp_s1 = (M *)(g_igTransientShaderData_metaObject[0]);
    temp_v0 = (void **)(((void * *)igMetaObject_FindFieldByName(temp_s1, &text_attrPushLists[0])));
    temp_s2 = ObjectPointerList_FindIndex(temp_s1->f40, temp_v0);
    temp_s0 = (T_194b40 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    temp_s0->f56 = FUN_0013abd0();
    temp_s0->f52 = 1;
    temp_s0->f38 = 0;
    temp_s0->f28 = (int)(&DAT_005611b0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    temp_s0->references = temp_s0->references - 1;
    if (((unsigned long long)(long long)temp_s0->references & 0x7fffffULL) == 0) {
        igObject_Destroy((void *)temp_s0);
    }
    temp_v0 = (void **)(((void * *)igMetaObject_FindFieldByName(temp_s1, &text_attrPopLists[0])));
    temp_s2 = ObjectPointerList_FindIndex(temp_s1->f40, temp_v0);
    temp_s0 = (T_194b40 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    temp_s0->f56 = FUN_0013abd0();
    temp_s0->f52 = 1;
    temp_s0->f38 = 0;
    temp_s0->f28 = (int)(&DAT_005611b8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    temp_s0->references = temp_s0->references - 1;
    if (((unsigned long long)(long long)temp_s0->references & 0x7fffffULL) == 0) {
        igObject_Destroy((void *)temp_s0);
    }
    temp_v0 = (void **)(((void * *)igMetaObject_FindFieldByName(temp_s1, &text_dataPumps[0])));
    temp_s2 = ObjectPointerList_FindIndex(temp_s1->f40, temp_v0);
    temp_s0 = (T_194b40 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    temp_s0->f56 = FUN_001e5690();
    igObjectRefMetaField_SetDefault(temp_s0, 0);
    temp_s0->f38 = 0;
    temp_s0->f28 = (int)(&DAT_005611c0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    temp_s0->references = temp_s0->references - 1;
    if (((unsigned long long)(long long)temp_s0->references & 0x7fffffULL) == 0) {
        igObject_Destroy((void *)temp_s0);
    }
    temp_v0 = (void **)(((void * *)igMetaObject_FindFieldByName(temp_s1, &text_childLists[0])));
    temp_s2 = ObjectPointerList_FindIndex(temp_s1->f40, temp_v0);
    temp_s0 = (T_194b40 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    temp_s0->f56 = (int)FUN_0019ca30();
    temp_s0->f52 = 1;
    temp_s0->f38 = 0;
    temp_s0->f28 = (int)(&DAT_005611c8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s2, temp_s0);
    temp_s0->references = temp_s0->references - 1;
    if (((unsigned long long)(long long)temp_s0->references & 0x7fffffULL) == 0) {
        igObject_Destroy((void *)temp_s0);
    }
}

