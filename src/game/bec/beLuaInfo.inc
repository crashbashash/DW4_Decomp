igMetaObject *g_beLuaInfo_metaObject;
igMetaField *g_beLuaInfo_dataListMetaField;

igMetaObject *beLuaInfo_GetMetaObject(void)
{
    igMetaObject *g = g_beLuaInfo_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beLuaInfo_EnsureRegistered();
    return g_beLuaInfo_metaObject;
}

int beLuaInfo_GetVTable(void) {
    struct Obj_35ad60 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &g_beLuaInfo_vtable[0];
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beLuaInfo_vtable[0];
    FUN_0035ade0((ObjectRefWord *)&obj.w7, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return t;
}

ObjectRefWord *FUN_0035ade0(ObjectRefWord *self,int delete_storage) {
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

void beLuaInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLuaInfo_Register);
}

static igMetaObjectCallback g_beLuaInfo_callbackList[] = { beLuaDataList_EnsureRegistered, 0 };

void *beLuaInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLuaInfo_GetMetaObjectFunction,
        "beLuaInfo",
        0x20, /* instance size */
        beLuaInfo_GetVTable,
        beLuaInfo_InitFields,
        0, /* extra callback item */
        g_beLuaInfo_callbackList /* callback list */
    );
}

void beLuaInfo_GetMetaObjectFunction(void)
{
    beLuaInfo_GetMetaObject();
}

static FieldFactory g_beLuaInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beLuaInfo_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beLuaInfo_fieldHandles[] = {
    &g_beLuaInfo_dataListMetaField,
};
static int g_beLuaInfo_fieldOffsets[] = {
    28,
};

void beLuaInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLuaInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beLuaInfo_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)beLuaDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beLuaInfo_fieldTable, g_beLuaInfo_fieldHandles, g_beLuaInfo_fieldOffsets, temp_s2);
}

