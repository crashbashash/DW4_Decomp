igMetaObject *igPlanarShadowShader_GetMetaObject(void)
{
    igMetaObject *g = g_igPlanarShadowShader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019c3f0();
    return g_igPlanarShadowShader_metaObject[0];
}

int igPlanarShadowShader_GetVTable(void) {
    union U_19bf50 u;


    int temp_s5;

    FUN_0019c380((void *)u.b);
    u.vt = (int)&DAT_005289f0[0];
    FUN_0019c370((int *)&u.b[40]);
    FUN_0019c360((int *)&u.b[44]);
    FUN_00151090(&u.b[48]);
    FUN_00151090(&u.b[64]);
    FUN_0019c360((int *)&u.b[80]);
    FUN_0019c350((int *)&u.b[84]);
    FUN_0019c340((int *)&u.b[88]);
    FUN_0019c330((int *)&u.b[92]);
    FUN_0019c330((int *)&u.b[96]);
    FUN_0019ac10((int *)&u.b[100]);
    FUN_0019c320((int *)&u.b[104]);
    temp_s5 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&D_005289f0[0];
    FUN_0019c2a0((ObjectRefWord *)&u.b[104], -1);
    FUN_0019ab10((O *)&u.b[100], -1);
    FUN_0018f980(&u.b[96], -1);
    FUN_0018f980(&u.b[92], -1);
    FUN_0013bfe0(&u.b[88], -1);
    FUN_0019c220((void * *)&u.b[84], -1);
    FUN_00199970((struct R * *)&u.b[80], -1);
    FUN_00199970((struct R * *)&u.b[44], -1);
    FUN_0019c1a0((ObjectRefWord *)&u.b[40], -1);
    FUN_0019c0e0((struct S_19c0e0 *)u.b, 0);
    return temp_s5;
}

void *FUN_0019c0e0(struct S_19c0e0 *arg0, short arg1) {
    void *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_005294b0[0];
        if (&arg0->f20) {
            p = arg0->f20;
            if (p != 0) {
                rc = *(int *)((char *)(p) + 4) - 1;
                *(int *)((char *)(p) + 4) = rc;
                if (((unsigned long long) ((long long) *(int *)((char *)(p) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &DAT_00528dd0[0];
            FUN_001958f0((void * *)((char *)arg0 + 0x1C), -1);
            FUN_00195970((struct T_195970 *)arg0, 0);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0019c1a0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void **FUN_0019c220(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((void *)r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0019c2a0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((void *)object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

int *FUN_0019c320(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019c330(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019c340(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019c350(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019c360(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *FUN_0019c370(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void *FUN_0019c380(void *arg0) {
    igAttrSet *self = (igAttrSet *)arg0;
    igObject_InitHeader();
    self->_vtable = (int)(&g_igNamedObject_vtable[0]);
    self->_name = 0;
    self->_vtable = (int)(&DAT_00528a90[0]);
    self->_bound = 0;
    self->_parentList = 0;
    self->_vtable = (int)(&DAT_00528dd0[0]);
    self->_childList = 0;
    self->_vtable = (int)(&DAT_005294b0[0]);
    self->_attributes = 0;
    return arg0;
}

void FUN_0019c3f0(void)
{
    igMetaObject_RunStaticInit(igPlanarShadowShader_Register);
}

void igPlanarShadowShader_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPlanarShadowShader_metaObject),
        igAttrSet_Register,
        igAttrSet_GetPublishedMetaObject,
        thunk_igPlanarShadowShader_GetMetaObject,
        igPlanarShadowShader_className,
        0x70, /* instance size */
        igPlanarShadowShader_GetVTable,
        &igPlanarShadowShader_InitFields,
        0, /* extra callback item */
        g_igPlanarShadowShader_callbackList /* callback list */
    );
}

void thunk_igPlanarShadowShader_GetMetaObject(void) {
    igPlanarShadowShader_GetMetaObject();
}

igMetaObject *FUN_0019c490(void) {
    return g_igAttrSet_metaObject[0];
}

void igPlanarShadowShader_InitFields(void) {
    void *temp_s2_9;
    void *temp_s2_8;
    void *temp_s2_7;
    void *temp_s2_6;
    void *temp_s2_5;
    void *temp_s2_4;
    void *temp_s2_3;
    void *temp_s2_2;
    void *temp_s2;
    void *temp_a0_2;
    void *temp_a0;
    int temp_s1;
    void *temp_s0;
    V4 spA;
    V4 spB;

    temp_s0 = (void *)g_igPlanarShadowShader_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igPlanarShadowShader_ctorTable[0], 0xD);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_001365e0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00135540();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)));
    spA.x = 0; spA.y = 1.0f; spA.z = 0; spA.w = 0;
    FUN_0018e670(temp_a0, &spA);
    temp_a0_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)));
    spB.x = 0; spB.w = 1.0f; spB.y = 0; spB.z = 0;
    FUN_0018e670(temp_a0_2, &spB);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_00135540();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    ((igMetaField *)temp_s2_3)->_persistent = 0;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_0019f930();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    ((igMetaField *)temp_s2_4)->_persistent = 0;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    ((igMetaField *)temp_s2_5)->_persistent = 0;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00186a80();
    ((igMetaField *)temp_s2_6)->_persistent = 0;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00186a80();
    ((igMetaField *)temp_s2_7)->_persistent = 0;
    temp_s2_8 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xB)));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_00138f20();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    ((igMetaField *)temp_s2_8)->_persistent = 0;
    temp_s2_9 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xC)));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_00133430();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    ((igMetaField *)temp_s2_9)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igPlanarShadowShader_fieldTable[0], &DAT_0048bbf0[0], &DAT_0048bc30[0], temp_s1);
}

