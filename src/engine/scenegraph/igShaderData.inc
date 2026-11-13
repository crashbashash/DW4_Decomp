igMetaObject *igShaderData_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199760();
    return g_igShaderData_metaObject[0];
}

int igShaderData_GetVTable(void) {
    struct Obj_1996b0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00528870[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00528870[0];
    FUN_00194830((struct Ref * *)&obj.w5, -1);
    FUN_001948b0((void * *)&obj.w4, -1);
    FUN_0013a800(&obj.w3, -1);
    FUN_0013a800(&obj.w2, -1);
    return t;
}

void FUN_00199760(void)
{
    igMetaObject_RunStaticInit(igShaderData_Register);
}

void igShaderData_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShaderData_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igShaderData_GetMetaObject,
        igShaderData_className,
        0x18, /* instance size */
        igShaderData_GetVTable,
        &igShaderData_InitFields,
        0, /* extra callback item */
        g_igShaderData_callbackList /* callback list */
    );
}

void thunk_igShaderData_GetMetaObject(void) {
    igShaderData_GetMetaObject();
}

void igShaderData_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igShaderData_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igShaderData_ctorTable[0], 4);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0013abd0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0013abd0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_001e5690();
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_0019ca30();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_igShaderData_fieldTable[0], &DAT_0048b6f0[0], &DAT_0048b700[0], temp_s0);
}

ObjectRefWord *FUN_001998f0(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_00199970(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

