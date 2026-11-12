void * FUN_002b8500(int arg0) {
    FUN_002b87c0();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585830), (MemoryPool *)arg0));
}

igMetaObject *igSymbolTable_GetMetaObject(void)
{
    igMetaObject *g = g_igSymbolTable_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002b87c0();
    return g_igSymbolTable_metaObject[0];
}

int igSymbolTable_GetVTable(void) {
    struct Obj_2b8590 obj;

    int temp_s3;

    igObject_InitHeader((ObjectHeader *)&obj);
    obj.vt = (&DAT_0052e730[0]);
    obj.f1C = 0;
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    temp_s3 = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = (&DAT_0052e730[0]);
    FUN_002b8740((ObjectRefWord *)&obj.f28, -1);
    FUN_002b8740((ObjectRefWord *)&obj.f24, -1);
    FUN_002b86c0((void **)&obj.f20, -1);
    FUN_002b8640((ObjectRefWord *)&obj.f1C, -1);
    return temp_s3;
}

ObjectRefWord *FUN_002b8640(ObjectRefWord *self,int delete_storage) {
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

void **FUN_002b86c0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_002b8740(ObjectRefWord *self,int delete_storage) {
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

void FUN_002b87c0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igSymbolTable_Register);
}

void igSymbolTable_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igSymbolTable_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igSymbolTable_GetMetaObject,
        igSymbolTable_className,
        0x2C, /* instance size */
        igSymbolTable_GetVTable,
        &igSymbolTable_InitFields,
        0, /* extra callback item */
        g_igSymbolTable_callbackList /* callback list */
    );
}

void thunk_igSymbolTable_GetMetaObject(void) {
    igSymbolTable_GetMetaObject();
}

void igSymbolTable_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igSymbolTable_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&DAT_004bf520[0], 9);
    FUN_0030e9b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3))), -1);
    FUN_0030e9b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4))), 1);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002ca2a0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002ca8f0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&DAT_004bf550[0], (igMetaField ***)&DAT_004bf580[0], &DAT_004bf5b0[0], temp_s0);
}

