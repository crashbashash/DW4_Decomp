void FUN_002bc300(int arg0) {
    FUN_002bc5c0();
    igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585AB8), (MemoryPool *)arg0);
}

igMetaObject *igPluginHelper_GetMetaObject(void)
{
    igMetaObject *g = g_igPluginHelper_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bc5c0();
    return g_igPluginHelper_metaObject[0];
}

int igPluginHelper_GetVTable(void) {
    struct Obj_2bc390 obj;
    int t;
    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_0052eee0[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &DAT_0052eee0[0];
    FUN_002bc540((ObjectRefWord *)(&obj.w[4]), -1);
    FUN_002bc4c0((void **)(&obj.w[3]), (short)(-1));
    FUN_002bc440((void **)(&obj.w[2]), (long long)(-1));
    StringRef_Destruct_00130720(&obj.w[1], -1);
    return t;
}

void **FUN_002bc440(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_002bc4c0(void **arg0, short arg1) {
    S_temp_a0_2bc4c0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0_2bc4c0 *)((void *)(*arg0));
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

ObjectRefWord *FUN_002bc540(ObjectRefWord *self,int delete_storage) {
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

void FUN_002bc5c0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPluginHelper_Register);
}

void igPluginHelper_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPluginHelper_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igPluginHelper_GetMetaObject,
        igPluginHelper_className,
        0x18, /* instance size */
        igPluginHelper_GetVTable,
        &igPluginHelper_InitFields,
        0, /* extra callback item */
        g_igPluginHelper_callbackList /* callback list */
    );
}

void thunk_igPluginHelper_GetMetaObject(void) {
    igPluginHelper_GetMetaObject();
}

void igPluginHelper_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igPluginHelper_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004bf9f0[0], 4);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))), (int)&DAT_004f6340[0]);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_002bc760();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_002c2290();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_002c23b0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004bfa00[0], (igMetaField ***)&DAT_004bfa10[0], &DAT_004bfa20[0], temp_s2);
}

