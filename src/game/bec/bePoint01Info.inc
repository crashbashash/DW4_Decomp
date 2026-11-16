igMetaObject *g_bePoint01Info_metaObject;
igMetaField *g_bePoint01Info_switchMetaField;
igMetaField *g_bePoint01Info_dataListMetaField;

void *bePoint01Info_GetMetaObject(void) {
    igMetaObject *g = g_bePoint01Info_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePoint01Info_EnsureRegistered();
    }
    return g_bePoint01Info_metaObject;
}

int bePoint01Info_GetVTable(void) {
    struct Obj obj;
    int temp_s1;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f14 = 0;
    obj.f18 = 0;
    obj.vt = (&g_bePoint01Info_vtable[0]);
    obj.f1C = 0;
    obj.f20 = 0;
    temp_s1 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_bePoint01Info_vtable[0]);
    FUN_0034b790((ObjectRefWord *)&obj.f20, -1);
    FUN_00343260((ObjectRefWord *)&obj.f1C, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return temp_s1;
}

ObjectRefWord *FUN_0034b790(ObjectRefWord *self,int delete_storage) {
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

void bePoint01Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePoint01Info_Register);
}

static igMetaObjectCallback g_bePoint01Info_callbackList[] = { igSwitch_EnsureRegistered, beGroupKeepList_EnsureRegistered, 0 };

void *bePoint01Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePoint01Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        bePoint01Info_GetMetaObjectFunction,
        "bePoint01Info",
        0x24, /* instance size */
        bePoint01Info_GetVTable,
        bePoint01Info_InitFields,
        0, /* extra callback item */
        g_bePoint01Info_callbackList /* callback list */
    );
}

void bePoint01Info_GetMetaObjectFunction(void)
{
    bePoint01Info_GetMetaObject();
}

static FieldFactory g_bePoint01Info_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_bePoint01Info_fieldTable[] = {
    "_switch",
    "_dataList",
};
static igMetaField **g_bePoint01Info_fieldHandles[] = {
    &g_bePoint01Info_switchMetaField,
    &g_bePoint01Info_dataListMetaField,
};
static int g_bePoint01Info_fieldOffsets[] = {
    28,
    32,
};

void bePoint01Info_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)g_bePoint01Info_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_bePoint01Info_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igSwitch_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beGroupKeepList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_bePoint01Info_fieldTable, g_bePoint01Info_fieldHandles, g_bePoint01Info_fieldOffsets, temp_s2);
}

igMetaEnum *g_bePoint01Info_msgActionMetaEnum;
static const char *g_bePoint01Info_msgActionNames[] = {
    "SHOWPOLYGON", "HIDEPOLYGON", "GETMATRIX", "GETMATRIXDIRECT",
    "GETPOINTNAME", "SETGENERATEPOS", "GETGENERATEPOS",
};
static int g_bePoint01Info_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6,
};

igMetaEnum *FUN_0034b980(void) {
    if (g_bePoint01Info_msgActionMetaEnum == 0) {
        g_bePoint01Info_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_bePoint01Info_msgActionNames, g_bePoint01Info_msgActionValues, 7);
    }
    return g_bePoint01Info_msgActionMetaEnum;
}

