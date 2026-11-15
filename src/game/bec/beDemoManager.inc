igMetaObject *g_beDemoManager_metaObject;
igMetaField *g_beDemoManager_messengerMetaField;
igMetaField *g_beDemoManager_luaMetaField;
igMetaField *g_beDemoManager_buildDataMetaField;
igMetaField *g_beDemoManager_activeDataListMetaField;
igMetaField *g_beDemoManager_turningOKMetaField;
igMetaField *g_beDemoManager_disableRemoveAllMetaField;
igMetaField *g_beDemoManager_calledRemoveAllMetaField;

void beDemoManager_CreateInstance(int arg0) {
    FUN_00363480();
    igMetaObject_CreateInstance(*(int *)0x589790, arg0);
}

igMetaObject *FUN_00363250(void) {
    if (g_beDemoManager_metaObject == 0) {
        g_beDemoManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beDemoManager_metaObject;
}

void *FUN_003632a0(void) {
    igMetaObject *g = g_beDemoManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00363480();
    }
    return g_beDemoManager_metaObject;
}

int beDemoManager_GetVTable(void) {
    struct Obj_3632f0 o;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_0053a460[0];
    o.f8 = 0;
    o.f24 = 0;
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_0053a460[0];
    FUN_00363400((struct R **)&o.f28, (short)(-1));
    FUN_00363380((ObjectRefWord *)&o.f24, -1);
    FUN_00231030(&o, 0);
    return r;
}

ObjectRefWord *FUN_00363380(ObjectRefWord *self,int delete_storage) {
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

struct R **FUN_00363400(struct R **arg0, short arg1) {
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

void FUN_00363480(void)
{
    igMetaObject_RunStaticInit(beDemoManager_Register);
}

static igMetaObjectCallback g_beDemoManager_callbackList[] = { FUN_00357d10, FUN_0035b9c0, FUN_00363930, FUN_00363710, 0 };

void *beDemoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDemoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beDemoManager_GetMetaObject,
        "beDemoManager",
        0x24, /* instance size */
        beDemoManager_GetVTable,
        beDemoManager_InitFields,
        0, /* extra callback item */
        g_beDemoManager_callbackList /* callback list */
    );
}

void beDemoManager_GetMetaObject(void)
{
    FUN_003632a0();
}

static FieldFactory g_beDemoManager_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beDemoManager_fieldTable[] = {
    "_messenger",
    "_lua",
    "_buildData",
    "_activeDataList",
    "_turningOK",
    "_disableRemoveAll",
    "_calledRemoveAll",
};
static igMetaField **g_beDemoManager_fieldHandles[] = {
    &g_beDemoManager_messengerMetaField,
    &g_beDemoManager_luaMetaField,
    &g_beDemoManager_buildDataMetaField,
    &g_beDemoManager_activeDataListMetaField,
    &g_beDemoManager_turningOKMetaField,
    &g_beDemoManager_disableRemoveAllMetaField,
    &g_beDemoManager_calledRemoveAllMetaField,
};
static int g_beDemoManager_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    33,
    34,
};

void beDemoManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s0;

    temp_s0 = (void *)g_beDemoManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beDemoManager_ctorTable, 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00357910();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0035b770();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_00363800();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = (int)FUN_00363630();
    ((igRefMetaField *)temp_s1_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beDemoManager_fieldTable, g_beDemoManager_fieldHandles, g_beDemoManager_fieldOffsets, temp_s2);
}

