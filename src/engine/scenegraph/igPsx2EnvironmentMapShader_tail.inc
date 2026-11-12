igMetaObject *igPsx2EnvironmentMapShader_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2EnvironmentMapShader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001ab540();
    return g_igPsx2EnvironmentMapShader_metaObject[0];
}

int igPsx2EnvironmentMapShader_GetVTable(void) {
    union U_1aae40 u;
    int temp_s2;
    char *p0;
    char *p2;
    char *p1;
    FUN_001ab4a0((igEnvironmentMapShader2 *)u.b);
    u.vt = &DAT_00528170[0];
    p0 = &u.b[112];
    FUN_001ab490((int *)p0);
    p1 = &u.b[116];
    FUN_0019ac20((int *)p1);
    p2 = &u.b[120];
    FUN_001ab480((int *)p2);
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = &DAT_00528170[0];
    FUN_001ab400((ObjectRefWord *)p2, -1);
    FUN_0019aa90((void * *)p1, -1);
    FUN_001ab380((void * *)p0, -1);
    FUN_001aaf80((Obj_1aaf80 *)u.b, 0);
    return temp_s2;
}

void **FUN_001aaf00(void **arg0, long long arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

Obj_1aaf80 *FUN_001aaf80(Obj_1aaf80 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = DAT_00528fa0;
        arg0->rel(&arg0->m108);
        arg0->rel(&arg0->m104);
        arg0->rel(&arg0->m100);
        arg0->rel(&arg0->m96);
        arg0->rel(&arg0->m92);
        arg0->rel(&arg0->m88);
        arg0->rel(&arg0->m84);
        arg0->rel(&arg0->m80);
        arg0->rel(&arg0->m76);
        arg0->rel(&arg0->m68);
        arg0->rel(&arg0->m64);
        arg0->rel(&arg0->m52);
        arg0->rel(&arg0->m36);
        arg0->rel(&arg0->m32);
        if (arg0) {
            arg0->vt = DAT_00528dd0;
            FUN_001958f0((void * *)((char *)arg0 + 28), -1);
            FUN_00195970((struct T_195970 *)arg0, 0);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_001ab380(void **arg0, short arg1) {
    S_temp_a0_1ab380 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1ab380 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_001ab400(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

int *FUN_001ab480(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_001ab490(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_001ab4a0(igEnvironmentMapShader2 *arg0) {
    igObject_InitHeader();
    arg0->_vtable = (int)(&DAT_00524950[0]);
    arg0->_name = 0;
    arg0->_vtable = (int)(&DAT_00528a90[0]);
    arg0->_bound = 0;
    arg0->_parentList = 0;
    arg0->_vtable = (int)(&DAT_00528dd0[0]);
    arg0->_childList = 0;
    arg0->_vtable = (int)(&DAT_00528fa0[0]);
    arg0->_envMapTexture = 0;
    arg0->_diffuseTextureBind = 0;
    arg0->_glossMapTexture = 0;
    arg0->_attrPushLists = 0;
    arg0->_attrPopLists = 0;
    arg0->_envMapTextureBind = 0;
    arg0->_envMapCoordSource = 0;
    arg0->_envMapTextureFunc = 0;
    arg0->_diffuseCoordSource = 0;
    arg0->_diffuseTextureFunc = 0;
    arg0->_diffuseBlendState = 0;
    arg0->_glossMapTextureBind = 0;
    arg0->_glossMapCoordSource = 0;
    arg0->_glossMapTextureFunc = 0;
    return arg0;
}

void FUN_001ab540(void)
{
    igMetaObject_RunStaticInit(igPsx2EnvironmentMapShader_Register);
}

void igPsx2EnvironmentMapShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2EnvironmentMapShader_metaObject),
        igEnvironmentMapShader2_Register,
        igEnvironmentMapShader2_GetPublishedMetaObject,
        thunk_igPsx2EnvironmentMapShader_GetMetaObject,
        igPsx2EnvironmentMapShader_className,
        0x7C, /* instance size */
        igPsx2EnvironmentMapShader_GetVTable,
        &igPsx2EnvironmentMapShader_InitFields,
        0, /* extra callback item */
        g_igPsx2EnvironmentMapShader_callbackList /* callback list */
    );
}

igMetaObject *FUN_001ab5d0(void) {
    return g_igEnvironmentMapShader2_metaObject[0];
}

void igPsx2EnvironmentMapShader_InitFields(void) {
    void *temp_s1_2;
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igPsx2EnvironmentMapShader_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048d880[0], 3);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00139f10();
    ((igMetaField *)temp_s1)->_persistent = 0;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, 1 + temp_s2)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_001331a0();
    ((igMetaField *)temp_s1_2)->_persistent = 0;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, 2 + temp_s2)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_001351d0();
    ((igMetaField *)temp_s1_3)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &DAT_0048d890[0], &DAT_0048d8a0[0], &DAT_0048d8b0[0], temp_s2);
    ((igMetaObject *)(g_igPsx2EnvironmentMapShader_metaObject[0]))->_writeProxy = (int)thunk_igEnvironmentMapShader2_GetMetaObject;
}

int FUN_001ab6c0(S_1ab6c0 *arg0, int arg1) {
    int i;
    int n;
    int *s;

    n = arg0->f20->count;
    for (i = 0; i < n; i++) {
        s = arg0->f20->data[i]->f8;
        s = s != 0 ? s : &emptyString[0];
        if (strcmp(s, arg1) == 0) {
            return i;
        }
    }
    return -1;
}

int FUN_001ab770(void *arg0, void **arg1, void **arg2) {
    int temp_v0_2;
    int temp_a0;
    void *temp_v0;
    int var_s2;
    int temp_s1;
    int var_s0;
    temp_v0 = (void *)(((void *)FUN_001a8c30(igObject_GetAllocator())));
    FUN_001abb50((S_1abb50 *)temp_v0, (A *)arg1);
    temp_s1 = ((DW4VC_96_0 *)(arg1))->vX();
    var_s0 = 0;
    for (var_s2 = 0; var_s2 < temp_s1; var_s2++) {
        temp_v0_2 = FUN_001ab6c0((S_1ab6c0 *)arg0, ((DW4VC_104_1 *)(arg1))->vX((int)(var_s2)));
        if (temp_v0_2 != -1) {
            var_s0 += 1;
        }
        *(int *)(*(int *)((char *)(temp_v0) + 12) + var_s2 * 4) = temp_v0_2;
    }
    if (var_s0 != 0) {
        *(int *)((char *)(temp_v0) + 16) = var_s0;
        ObjectList_AppendRetained(*(int *)((char *)(arg0) + 16), temp_v0);
        *arg2 = temp_v0;
    } else {
        *arg2 = 0;
    }
    ((S1_1ab770 *)temp_v0)->f4 = (int)((int) (((S1_1ab770 *)temp_v0)->f4 - 1));
    if (((unsigned long long) ((long long) ((S1_1ab770 *)temp_v0)->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy((void *)temp_v0);
    }
    return var_s0;
}

int FUN_001ab8b0(int arg0, int arg1, void **arg2) {
    void *sp4C;

    sp4C = 0;
    FUN_001ab920((const H *)arg0, arg1, (T_1ab920 * *)&sp4C);
    if (sp4C != 0) {
        *arg2 = sp4C;
        return *(int *)((char *)sp4C + 16);
    }
    return FUN_001ab770((void *)arg0, (void * *)arg1, (void * *)arg2);
}

int FUN_001ab920(const H *a, int id, T_1ab920 **out) {
    int i;
    int n = a->list->cnt;
    for (i = 0; i < n; i++) {
        T_1ab920 *t = (T_1ab920 *)a->list->arr[i];
        unsigned b = t->busy != 0u;
        if (!b && t->id == id) { *out = t; return i; }
    }
    *out = 0;
    return -1;
}

