igMetaObject *g_beMeterCtrlOneData_metaObject;
igMetaField *g_beMeterCtrlOneData_nodeMetaField;
igMetaField *g_beMeterCtrlOneData_maxValueFMetaField;
igMetaField *g_beMeterCtrlOneData_ratioTimeValueFMetaField;
igMetaField *g_beMeterCtrlOneData_addMaxValueFMetaField;
igMetaField *g_beMeterCtrlOneData_nowValueFMetaField;
igMetaField *g_beMeterCtrlOneData_dspValueFMetaField;
igMetaField *g_beMeterCtrlOneData_nonZeroTimeLMetaField;
igMetaField *g_beMeterCtrlOneData_nonMaxTimeLMetaField;
igMetaField *g_beMeterCtrlOneData_ketaKazuMetaField;
igMetaField *g_beMeterCtrlOneData_isChangeMetaField;
igMetaField *g_beMeterCtrlOneData_isZeroSuppMetaField;
igMetaField *g_beMeterCtrlOneData_isNotchModeMetaField;
igMetaField *g_beMeterCtrlOneData_hpMetaField;
igMetaField *g_beMeterCtrlOneData_mHpMetaField;

void *beMeterCtrlOneData_GetMetaObject(void) {
    igMetaObject *g = g_beMeterCtrlOneData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMeterCtrlOneData_EnsureRegistered();
    }
    return g_beMeterCtrlOneData_metaObject;
}

int beMeterCtrlOneData_GetVTable(void) {
    beMeterCtrlOneData obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&g_beMeterCtrlOneData_vtable[0];
    obj._node = 0;
    obj._hp = 0;
    obj._mHp = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beMeterCtrlOneData_vtable[0];
    igSmartPointer_beDataObjInt_Destruct((igSmartPointer<igObject> *)&obj._mHp, (short)(-1));
    igSmartPointer_beDataObjInt_Destruct((igSmartPointer<igObject> *)&obj._hp, (short)(-1));
    igSmartPointer_beMeterCtrlNode_Destruct((igSmartPointer<igObject> *)&obj._node, (long long)(-1));
    igNamedObject_Destroy(&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beMeterCtrlNode_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beMeterCtrlOneData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlOneData_Register);
}

static igMetaObjectCallback g_beMeterCtrlOneData_callbackList[] = { beMeterCtrlNode_EnsureRegistered, beDataObjInt_EnsureRegistered, 0 };

void *beMeterCtrlOneData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrlOneData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beMeterCtrlOneData_GetMetaObjectFunction,
        "beMeterCtrlOneData",
        0x48, /* instance size */
        beMeterCtrlOneData_GetVTable,
        beMeterCtrlOneData_InitFields,
        0, /* extra callback item */
        g_beMeterCtrlOneData_callbackList /* callback list */
    );
}

void beMeterCtrlOneData_GetMetaObjectFunction(void)
{
    beMeterCtrlOneData_GetMetaObject();
}

static FieldFactory g_beMeterCtrlOneData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMeterCtrlOneData_fieldTable[] = {
    "_node",
    "_maxValueF",
    "_ratioTimeValueF",
    "_addMaxValueF",
    "_nowValueF",
    "_dspValueF",
    "_nonZeroTimeL",
    "_nonMaxTimeL",
    "_ketaKazu",
    "_isChange",
    "_isZeroSupp",
    "_isNotchMode",
    "_hp",
    "_mHp",
};
static igMetaField **g_beMeterCtrlOneData_fieldHandles[] = {
    &g_beMeterCtrlOneData_nodeMetaField,
    &g_beMeterCtrlOneData_maxValueFMetaField,
    &g_beMeterCtrlOneData_ratioTimeValueFMetaField,
    &g_beMeterCtrlOneData_addMaxValueFMetaField,
    &g_beMeterCtrlOneData_nowValueFMetaField,
    &g_beMeterCtrlOneData_dspValueFMetaField,
    &g_beMeterCtrlOneData_nonZeroTimeLMetaField,
    &g_beMeterCtrlOneData_nonMaxTimeLMetaField,
    &g_beMeterCtrlOneData_ketaKazuMetaField,
    &g_beMeterCtrlOneData_isChangeMetaField,
    &g_beMeterCtrlOneData_isZeroSuppMetaField,
    &g_beMeterCtrlOneData_isNotchModeMetaField,
    &g_beMeterCtrlOneData_hpMetaField,
    &g_beMeterCtrlOneData_mHpMetaField,
};
static int g_beMeterCtrlOneData_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    40,
    48,
    56,
    60,
    61,
    62,
    64,
    68,
};

void beMeterCtrlOneData_InitFields(void) {
    int base;
    void *node;
    void *hp;
    void *mHp;
    void *meta;

    meta = (void *)g_beMeterCtrlOneData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMeterCtrlOneData_ctorTable, 0xE);
    node = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)node)->_metaObject = (int)beMeterCtrlNode_GetOrCreateMetaObject();
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 4), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 5), 0.0f);
    hp = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)hp)->_metaObject = (int)beDataObjInt_GetOrCreateMetaObject();
    mHp = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)mHp)->_metaObject = (int)beDataObjInt_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beMeterCtrlOneData_fieldTable, g_beMeterCtrlOneData_fieldHandles, g_beMeterCtrlOneData_fieldOffsets, base);
}

igMetaEnum *g_beMeterCtrlOneData_msgActionMetaEnum;
static const char *g_beMeterCtrlOneData_msgActionNames[] = {
    "GETVALUE", "SETVALUE", "ADDVALUE", "GETPERCENT",
    "SETPERCENT", "ADDPERCENT", "SETMAXVALUE", "SETMODELHP",
};
static int g_beMeterCtrlOneData_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

igMetaEnum *beMeterCtrl_GetMsgActionEnum(void) {
    if (g_beMeterCtrlOneData_msgActionMetaEnum == 0) {
        g_beMeterCtrlOneData_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beMeterCtrlOneData_msgActionNames, g_beMeterCtrlOneData_msgActionValues, 8);
    }
    return g_beMeterCtrlOneData_msgActionMetaEnum;
}

