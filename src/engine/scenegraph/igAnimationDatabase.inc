igMetaObject *FUN_001a7780(void) {
    if (g_igAnimationDatabase_metaObject[0] == 0) {
        g_igAnimationDatabase_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAnimationDatabase_metaObject[0];
}

igMetaObject *igAnimationDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationDatabase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7b00();
    return g_igAnimationDatabase_metaObject[0];
}

int igAnimationDatabase_GetVTable(void) {
    struct W_1a7820 o;
    int *p19;
    int *p18;
    int *p17;
    int *p16;
    int r;
    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.vt = &DAT_005295c0[0];
    p16 = &o.f[4];
    *p16 = 0;
    p17 = &o.f[5];
    *p17 = 0;
    p18 = &o.f[6];
    *p18 = 0;
    p19 = &o.f[7];
    *p19 = 0;
    o.f[8] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_005295c0[0];
    FUN_001a7a80((void * *)&o.f[8], -1);
    FUN_001a7a00((ObjectRefWord *)p19, -1);
    FUN_001a6350((struct Ref * *)p18, -1);
    FUN_001a7980((void * *)p17, -1);
    FUN_001a7900((ObjectRefWord *)p16, -1);
    FUN_00131b20(&o, 0);
    return r;
}

ObjectRefWord *FUN_001a7900(ObjectRefWord *self,int delete_storage) {
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

void **FUN_001a7980(void **arg0, short arg1) {
    S_temp_a0_1a7980 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_1a7980 *)(*arg0);
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

ObjectRefWord *FUN_001a7a00(ObjectRefWord *self,int delete_storage) {
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

void **FUN_001a7a80(void **arg0, short arg1) {
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

void FUN_001a7b00(void)
{
    igMetaObject_RunStaticInit(igAnimationDatabase_Register);
}

void igAnimationDatabase_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationDatabase_metaObject),
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igAnimationDatabase_GetMetaObject,
        igAnimationDatabase_className,
        0x28, /* instance size */
        igAnimationDatabase_GetVTable,
        &igAnimationDatabase_InitFields,
        0, /* extra callback item */
        g_igAnimationDatabase_callbackList /* callback list */
    );
}

void thunk_igAnimationDatabase_GetMetaObject(void) {
    igAnimationDatabase_GetMetaObject();
}

void igAnimationDatabase_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s1;

    temp_s1 = (void *)g_igAnimationDatabase_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igAnimationDatabase_ctorTable[0], 5);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_001983e0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_001a8f80();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_00197e60();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_001a5fe0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_001a83b0();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_igAnimationDatabase_fieldTable[0], &DAT_0048d260[0], &DAT_0048d280[0], temp_s0);
}

