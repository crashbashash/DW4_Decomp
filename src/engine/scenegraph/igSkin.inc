igMetaObject *FUN_00197fd0(void) {
    if (g_igSkin_metaObject[0] == 0) {
        g_igSkin_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igSkin_metaObject[0];
}

igMetaObject *igSkin_GetMetaObject(void)
{
    igMetaObject *g = g_igSkin_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00198290();
    return g_igSkin_metaObject[0];
}

int igSkin_GetVTable(void) {
    union U_198070 u;
    int temp_s2;
    S_ref *q3;
    S_ref *q2;
    char *q1;
    int *tv1, *ta1;
    int tc1;
    
    
    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_0052b3b0[0]);
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[16];
    *(int *)q3 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_0052b3b0[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q2);
            }
        }
    }
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader(*ta1, ta1);
            }
        }
    }
    return temp_s2;
}

void **FUN_00198190(void **arg0, short arg1) {
    S_temp_a0_198190 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_198190 *)(*arg0);
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

ObjectRefWord *FUN_00198210(ObjectRefWord *self,int delete_storage) {
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

void FUN_00198290(void)
{
    igMetaObject_RunStaticInit(igSkin_Register);
}

void igSkin_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igSkin_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSkin_GetMetaObject,
        igSkin_className,
        0x14, /* instance size */
        igSkin_GetVTable,
        &igSkin_InitFields,
        0, /* extra callback item */
        g_igSkin_callbackList /* callback list */
    );
}

void thunk_igSkin_GetMetaObject(void) {
    igSkin_GetMetaObject();
}

void igSkin_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSkin_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b560[0], 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0019cd50();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0018a6a0();
    igMetaObject_NameFields(temp_s0, &DAT_0048b568[0], &DAT_0048b570[0], &DAT_0048b578[0], temp_s2);
}

