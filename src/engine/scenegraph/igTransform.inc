void FUN_00196150(int arg0) {
    FUN_001964d0();
    igMetaObject_CreateInstance(*(int *)0x5612B0, arg0);
}

int FUN_00196190(void) {
    if (DAT_005612b0[0] == 0) {
        DAT_005612b0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005612b0[0];
}

igMetaObject *igTransform_GetMetaObject(void)
{
    igMetaObject *g = g_igTransform_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001964d0();
    return g_igTransform_metaObject[0];
}

int igTransform_GetVTable(void) {
    struct W o;
    int r;
    int *pa = (int *)&o;
    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.vt = &DAT_005284f0[0];
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[6] = 0;
    igMatrix44f_SetIdentity((char *)&o + 32);
    pa[25] = 0;
    pa[26] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005284f0[0];
    FUN_00196450((void * *)&o.f[25], -1);
    FUN_001963d0((ObjectRefWord *)&o.f[24], -1);
    FUN_00195a90((struct T_195a90 *)&o, 0);
    return r;
}

void *FUN_001962d0(struct S_1962d0 *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &DAT_005284f0[0];
        if (&arg0->f68) {
            p = (igObject *)arg0->f68;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((void *)p);
                }
            }
        }
        if (&arg0->f64) {
            p = (igObject *)arg0->f64;
            if (p != 0) {
                rc = (int)p->_refCount - 1;
                p->_refCount = rc;
                if (((unsigned long long) ((long long) (int)p->_refCount << 0x29) >> 0x29) == 0) {
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

ObjectRefWord *FUN_001963d0(ObjectRefWord *self,int delete_storage) {
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

void **FUN_00196450(void **arg0, short arg1) {
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
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void FUN_001964d0(void)
{
    igMetaObject_RunStaticInit(igTransform_Register);
}

void igTransform_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTransform_metaObject),
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igTransform_GetMetaObject,
        igTransform_className,
        0x6C, /* instance size */
        igTransform_GetVTable,
        &igTransform_InitFields,
        0, /* extra callback item */
        g_igTransform_callbackList /* callback list */
    );
}

void thunk_igTransform_GetMetaObject(void) {
    igTransform_GetMetaObject();
}

void igTransform_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;
    struct M_196570 o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    temp_s0 = (void *)DAT_005612b0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048b190[0], 4);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    FUN_00130e90(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s1, &o1);
    FUN_002ea4b0(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)), 0);
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_00130310();
    *(char *)((char *)(temp_s1_2) + 38) = 0;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)));
    *(int *)((char *)(temp_s1_3) + 56) = FUN_00194dd0();
    igMetaObject_NameFields(temp_s0, &DAT_0048b1a0[0], &DAT_0048b1b0[0], &DAT_0048b1c0[0], temp_s2);
}

ObjectRefWord *FUN_001966b0(ObjectRefWord *self,int delete_storage) {
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

