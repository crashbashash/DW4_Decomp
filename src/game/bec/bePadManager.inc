igMetaObject *g_bePadManager_metaObject;
igMetaField *g_bePadManager_systemMetaField;
igMetaField *g_bePadManager_padListMetaField;
igMetaField *g_bePadManager_kbReceiverMetaField;
igMetaField *g_bePadManager_is1pAllDeviceMetaField;
igMetaField *g_bePadManager_isPadDisableMetaField;

void bePadManager_CreateInstance(int arg0) {
    bePadManager_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588518, arg0);
}

igMetaObject *bePadManager_GetOrCreateMetaObject(void) {
    if (g_bePadManager_metaObject == 0) {
        g_bePadManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_bePadManager_metaObject;
}

void *bePadManager_GetMetaObject(void) {
    igMetaObject *g = g_bePadManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePadManager_EnsureRegistered();
    }
    return g_bePadManager_metaObject;
}

int bePadManager_GetVTable(void) {
    struct Obj_34c980 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &g_bePadManager_vtable[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_bePadManager_vtable[0];
    FUN_0034cab0((struct R **)&obj.w6, (short)(-1));
    FUN_0034ca30((ObjectRefWord *)&obj.w5, -1);
    FUN_0033dc20((void **)&obj.w4, (short)(-1));
    FUN_00231030(&obj, 0);
    return t;
}

ObjectRefWord *FUN_0034ca30(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_0034cab0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void bePadManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePadManager_Register);
}

static igMetaObjectCallback g_bePadManager_callbackList[] = { beSystem_EnsureRegistered, bePadDataList_EnsureRegistered, beKeyboardReceiver_EnsureRegistered, 0 };

void *bePadManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePadManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        bePadManager_GetMetaObjectFunction,
        "bePadManager",
        0x20, /* instance size */
        bePadManager_GetVTable,
        bePadManager_InitFields,
        0, /* extra callback item */
        g_bePadManager_callbackList /* callback list */
    );
}

void bePadManager_GetMetaObjectFunction(void)
{
    bePadManager_GetMetaObject();
}

static FieldFactory g_bePadManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_bePadManager_fieldTable[] = {
    "_system",
    "_padList",
    "_kbReceiver",
    "_is1pAllDevice",
    "_isPadDisable",
};
static igMetaField **g_bePadManager_fieldHandles[] = {
    &g_bePadManager_systemMetaField,
    &g_bePadManager_padListMetaField,
    &g_bePadManager_kbReceiverMetaField,
    &g_bePadManager_is1pAllDeviceMetaField,
    &g_bePadManager_isPadDisableMetaField,
};
static int g_bePadManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    29,
};

void bePadManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s0;

    temp_s0 = (void *)g_bePadManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_bePadManager_ctorTable, 5);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)bePadDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beKeyboardReceiver_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_bePadManager_fieldTable, g_bePadManager_fieldHandles, g_bePadManager_fieldOffsets, temp_s2);
}

