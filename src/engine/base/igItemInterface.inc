igMetaObject *FUN_00227c20(void) {
    if (g_igItemInterface_metaObject[0] == 0) {
        g_igItemInterface_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igItemInterface_metaObject[0];
}

igMetaObject *igItemInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igItemInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00227ef0();
    return g_igItemInterface_metaObject[0];
}

int igItemInterface_GetVTable(void) {
    struct Obj_7 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c0f0[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052c0f0[0];
    FUN_00227e70((void **)&obj.w11, -1);
    FUN_00227df0((ObjectRefWord *)&obj.w10, -1);
    FUN_0013a880(&obj.w9, -1);
    FUN_00227d70((void **)&obj.w8, -1);
    return t;
}

void **FUN_00227d70(void **arg0, short arg1) {
    S_temp_a0 *temp_a0;

    if (arg0 != 0) {
        temp_a0 = (S_temp_a0 *)(*arg0);
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

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_00227df0(ObjectRefWord *self,int delete_storage) {
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

void **FUN_00227e70(void **arg0, short arg1) {
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
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00227ef0(void)
{
    igMetaObject_RunStaticInit(igItemInterface_Register);
}

void igItemInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igItemInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igItemInterface_GetMetaObject,
        igItemInterface_className,
        0x34, /* instance size */
        igItemInterface_GetVTable,
        &igItemInterface_InitFields,
        0, /* extra callback item */
        g_igItemInterface_callbackList /* callback list */
    );
}

void thunk_igItemInterface_GetMetaObject(void) {
    igItemInterface_GetMetaObject();
}

void igItemInterface_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igItemInterface_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igItemInterface_ctorTable[0], 5);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002280b0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igMetaObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igMetaObjectListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igStringRefListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, &g_igItemInterface_fieldTable[0], &DAT_00497e30[0], &DAT_00497e50[0], temp_s0);
    igMetaObject_AddExitCallback(FUN_002280a0);
}

void FUN_002280a0(void) {
    FUN_00229980();
}

