igMetaObject *g_beSwitchCtrlInfo_metaObject;
igMetaField *g_beSwitchCtrlInfo_switchNodeMetaField;

void *beSwitchCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beSwitchCtrlInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSwitchCtrlInfo_EnsureRegistered();
    }
    return g_beSwitchCtrlInfo_metaObject;
}

int beSwitchCtrlInfo_GetVTable(void) {
    struct Obj_3431e0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &g_beSwitchCtrlInfo_vtable[0];
    obj.w[6] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSwitchCtrlInfo_vtable[0];
    FUN_00343260((ObjectRefWord *)(&obj.w[6]), -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return r;
}

ObjectRefWord *FUN_00343260(ObjectRefWord *self,int delete_storage) {
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

void beSwitchCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSwitchCtrlInfo_Register);
}

static igMetaObjectCallback g_beSwitchCtrlInfo_callbackList[] = { igSwitch_EnsureRegistered, 0 };

void *beSwitchCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSwitchCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beSwitchCtrlInfo_GetMetaObjectFunction,
        "beSwitchCtrlInfo",
        0x20, /* instance size */
        beSwitchCtrlInfo_GetVTable,
        beSwitchCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beSwitchCtrlInfo_callbackList /* callback list */
    );
}

void beSwitchCtrlInfo_GetMetaObjectFunction(void)
{
    beSwitchCtrlInfo_GetMetaObject();
}

static FieldFactory g_beSwitchCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beSwitchCtrlInfo_fieldTable[] = {
    "_switchNode",
};
static igMetaField **g_beSwitchCtrlInfo_fieldHandles[] = {
    &g_beSwitchCtrlInfo_switchNodeMetaField,
};
static int g_beSwitchCtrlInfo_fieldOffsets[] = {
    28,
};

void beSwitchCtrlInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSwitchCtrlInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSwitchCtrlInfo_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igSwitch_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beSwitchCtrlInfo_fieldTable, g_beSwitchCtrlInfo_fieldHandles, g_beSwitchCtrlInfo_fieldOffsets, temp_s2);
}

igMetaEnum *g_beSwitchCtrlInfo_msgActionMetaEnum;
static const char *g_beSwitchCtrlInfo_msgActionNames[] = {
    "ALLON", "ALLOF",
};
static int g_beSwitchCtrlInfo_msgActionValues[] = {
    0, 1,
};

igMetaEnum *beSwitchCtrl_GetMessageEnum(void) {
    if (g_beSwitchCtrlInfo_msgActionMetaEnum == 0) {
        g_beSwitchCtrlInfo_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beSwitchCtrlInfo_msgActionNames, g_beSwitchCtrlInfo_msgActionValues, 2);
    }
    return g_beSwitchCtrlInfo_msgActionMetaEnum;
}

