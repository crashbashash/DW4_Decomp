igMetaObject *g_igSkin_metaObject;
igMetaField *g_igSkin_skinnedGraphMetaField;
igMetaField *g_igSkin_boundMetaField;

igMetaObject *FUN_00197fd0(void) {
    if (g_igSkin_metaObject == 0) {
        g_igSkin_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSkin_metaObject;
}

igMetaObject *igSkin_GetMetaObject(void)
{
    igMetaObject *g = g_igSkin_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSkin_EnsureRegistered();
    return g_igSkin_metaObject;
}

int igSkin_GetVTable(void) {
    union U_198070 u;
    int temp_s2;
    S_ref *q3;
    S_ref *q2;
    char *q1;
    int *tv1, *ta1;
    int tc1;
    
    
    igObject_InitHeader((igObject *)u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&g_igSkin_vtable[0]);
    q2 = (S_ref *)&u.b[12];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[16];
    *(int *)q3 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
    u.w[0] = (int)(&g_igSkin_vtable[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q2);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*ta1, (StringTokenHeader *)ta1);
            }
        }
    }
    return temp_s2;
}

void **igSmartPointer_igAABox_Destruct(void **arg0, short arg1) {
    S_temp_a0_198190 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_198190 *)(*arg0);
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *igSmartPointer_igNode_Destruct(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy((igObject *)object);
        }
        if((short)delete_storage>0) operator delete(self);
    }
    return self;
}

void igSkin_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSkin_Register);
}

static igMetaObjectCallback g_igSkin_callbackList[] = { igNode_EnsureRegistered, igAABox_EnsureRegistered, 0 };

CallbackArray *igSkin_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSkin_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSkin_GetMetaObject,
        "igSkin",
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

static FieldFactory g_igSkin_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igSkin_fieldTable[] = {
    "_skinnedGraph",
    "_bound",
};
static igMetaField **g_igSkin_fieldHandles[] = {
    &g_igSkin_skinnedGraphMetaField,
    &g_igSkin_boundMetaField,
};
static int g_igSkin_fieldOffsets[] = {
    12,
    16,
};

void igSkin_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igSkin_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igSkin_ctorTable, 2);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igNode_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igAABox_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igSkin_fieldTable, g_igSkin_fieldHandles, g_igSkin_fieldOffsets, temp_s2);
}

