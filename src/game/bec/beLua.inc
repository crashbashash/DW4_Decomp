igMetaObject *g_beLua_metaObject;
igMetaField *g_beLua_systemMetaField;
igMetaField *g_beLua_infoListMetaField;
igMetaField *g_beLua_luaStateMetaField;
igMetaField *g_beLua_luaGlueMetaField;

void beLua_CreateInstance(int arg0) {
    FUN_0035b9c0();
    igMetaObject_CreateInstance(*(int *)0x589208, arg0);
}

igMetaObject *FUN_0035b770(void) {
    if (g_beLua_metaObject == 0) {
        g_beLua_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLua_metaObject;
}

void *FUN_0035b7c0(void) {
    igMetaObject *g = g_beLua_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035b9c0();
    }
    return g_beLua_metaObject;
}

int beLua_GetVTable(void) {
    struct Obj_35b810 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &DAT_0053a9e0[0];
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[6] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053a9e0[0];
    FUN_0035b940((ObjectRefWord *)(&obj.w[6]), -1);
    FUN_0035b8c0((void **)(&obj.w[5]), (short)(-1));
    FUN_0033f560((void **)(&obj.w[4]), -1);
    FUN_00231030(&obj, 0);
    return r;
}

void **FUN_0035b8c0(void **arg0, short arg1) {
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

ObjectRefWord *FUN_0035b940(ObjectRefWord *self,int delete_storage) {
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

void FUN_0035b9c0(void)
{
    igMetaObject_RunStaticInit(beLua_Register);
}

static igMetaObjectCallback g_beLua_callbackList[] = { FUN_00342f30, FUN_0036abd0, FUN_0035abe0, igLuaGlue_EnsureRegistered, 0 };

void *beLua_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLua_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beLua_GetMetaObject,
        "beLua",
        0x20, /* instance size */
        beLua_GetVTable,
        beLua_InitFields,
        0, /* extra callback item */
        g_beLua_callbackList /* callback list */
    );
}

void beLua_GetMetaObject(void)
{
    FUN_0035b7c0();
}

static FieldFactory g_beLua_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beLua_fieldTable[] = {
    "_system",
    "_infoList",
    "_luaState",
    "_luaGlue",
};
static igMetaField **g_beLua_fieldHandles[] = {
    &g_beLua_systemMetaField,
    &g_beLua_infoListMetaField,
    &g_beLua_luaStateMetaField,
    &g_beLua_luaGlueMetaField,
};
static int g_beLua_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beLua_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s0;

    temp_s0 = (void *)g_beLua_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beLua_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0036aaf0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0035aa60();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = igLuaGlue_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_4)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beLua_fieldTable, g_beLua_fieldHandles, g_beLua_fieldOffsets, temp_s2);
}

