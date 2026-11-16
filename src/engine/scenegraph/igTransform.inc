void igTransform_CreateInstance(int arg0) {
    igTransform_EnsureRegistered();
    igMetaObject_CreateInstance((int)g_igTransform_metaObject, arg0);
}

igMetaObject *g_igTransform_metaObject;
igMetaField *g_igTransform_mMetaField;
igMetaField *g_igTransform_targetMetaField;
igMetaField *g_igTransform_mvmMetaField;
igMetaField *g_igTransform_transformInputMetaField;

igMetaObject *igTransform_GetOrCreateMetaObject(void) {
    if (g_igTransform_metaObject == 0) {
        g_igTransform_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTransform_metaObject;
}

igMetaObject *igTransform_GetMetaObject(void)
{
    igMetaObject *g = g_igTransform_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransform_EnsureRegistered();
    return g_igTransform_metaObject;
}

int igTransform_GetVTable(void) {
    struct W o;
    int r;
    int *pa = (int *)&o;
    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.vt = &g_igTransform_vtable[0];
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[6] = 0;
    igMatrix44f_SetIdentity((char *)&o + 32);
    pa[25] = 0;
    pa[26] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_igTransform_vtable[0];
    FUN_00196450((void * *)&o.f[25], -1);
    FUN_001963d0((ObjectRefWord *)&o.f[24], -1);
    igGroup_Destroy((struct T_195a90 *)&o, 0);
    return r;
}

void *FUN_001962d0(struct S_1962d0 *arg0, short arg1) {
    igObject *p;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &g_igTransform_vtable[0];
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
            arg0->f0 = &g_igGroup_vtable[0];
            igSmartPointer_igNodeList_Destruct((void * *)((char *)arg0 + 0x1C), -1);
            igNode_Destroy((struct T_195970 *)arg0, 0);
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
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
        if((short)delete_storage>0) __dl__FPv(self);
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void igTransform_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransform_Register);
}

static igMetaObjectCallback g_igTransform_callbackList[] = { FUN_001303b0, FUN_00194e70, 0 };

void igTransform_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTransform_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igTransform_GetMetaObject,
        "igTransform",
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

static FieldFactory g_igTransform_ctorTable[] = {
    igMatrix44fMetaField_CreateInstance,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igTransform_fieldTable[] = {
    "_m",
    "_target",
    "_mvm",
    "_transformInput",
};
static igMetaField **g_igTransform_fieldHandles[] = {
    &g_igTransform_mMetaField,
    &g_igTransform_targetMetaField,
    &g_igTransform_mvmMetaField,
    &g_igTransform_transformInputMetaField,
};
static int g_igTransform_fieldOffsets[] = {
    32,
    96,
    100,
    104,
};

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

    temp_s0 = (void *)g_igTransform_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igTransform_ctorTable, 4);
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
    igMatrix44f_FromRows(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s1, &o1);
    igIntMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)), 0);
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)));
    *(int *)((char *)(temp_s1_2) + 56) = FUN_00130310();
    *(char *)((char *)(temp_s1_2) + 38) = 0;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)));
    *(int *)((char *)(temp_s1_3) + 56) = (int)FUN_00194dd0();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igTransform_fieldTable, g_igTransform_fieldHandles, g_igTransform_fieldOffsets, temp_s2);
}

ObjectRefWord *FUN_001966b0(ObjectRefWord *self,int delete_storage) {
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

