int FUN_0014a780(int arg0) {
    FUN_0014ab70();
    return igMetaObject_CreateInstance(*(int *)0x55F9E0, arg0);
}

igMetaObject *FUN_0014a7c0(void) {
    if (g_igVertexArray2_metaObject[0] == 0) {
        g_igVertexArray2_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igVertexArray2_metaObject[0];
}

igMetaObject *igVertexArray2_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexArray2_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ab70();
    return g_igVertexArray2_metaObject[0];
}

int igVertexArray2_GetVTable(void) {
    struct Obj_14a860 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &DAT_00526410[0];
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00526410[0];
    FUN_0014aaf0((ObjectRefWord *)&obj.w[4], -1);
    FUN_0014aa70((void **)&obj.w[3], -1);
    ObjectRef_Destruct_001363f0(&obj.w[2], -1);
    FUN_00131bc0(&obj, 0);
    return r;
}

Obj_14a910 *FUN_0014a910(Obj_14a910 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = &DAT_00526410[0];
        arg0->rel(&arg0->m20);
        arg0->rel(&arg0->m16);
        arg0->rel(&arg0->m12);
        if (arg0) {
            arg0->vt = &g_igNamedObject_vtable[0];
            arg0->relS(&arg0->m8);
        }
        if (arg1 > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void **FUN_0014aa70(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)((void *)(*arg0));
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if ((temp_a0->f4 & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_0014aaf0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_0014ab70(void)
{
    igMetaObject_RunStaticInit(igVertexArray2_Register);
}

void igVertexArray2_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexArray2_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igVertexArray2_GetMetaObject,
        igVertexArray2_className,
        0x18, /* instance size */
        igVertexArray2_GetVTable,
        &igVertexArray2_InitFields,
        0, /* extra callback item */
        g_igVertexArray2_callbackList /* callback list */
    );
}

void thunk_igVertexArray2_GetMetaObject(void) {
    igVertexArray2_GetMetaObject();
}

void igVertexArray2_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igVertexArray2_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igVertexArray2_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0014ae00();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_v0)->_metaObject = (int)((int) g_igObject_metaObject[0]);
    ((igMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igVertexArray2_fieldTable[0], &DAT_00488540[0], &DAT_00488550[0], temp_s2);
    *(int *)((char *)(g_igVertexArray2_metaObject[0]) + 60) = (int)(thunk_FUN_00152200);
}

void thunk_FUN_00152200(void) {
    FUN_00152200();
}

