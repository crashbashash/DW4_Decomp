igMetaObject *g_beModelCtrlInfoRamData_metaObject;
int g_beModelCtrlInfoRamData_nameStorage;
igMetaField *g_beModelCtrlInfoRamData_nodeMetaField;
igMetaField *g_beModelCtrlInfoRamData_workMetaField;

void *beModelCtrlInfoRamData_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoRamData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoRamData_EnsureRegistered();
    }
    return g_beModelCtrlInfoRamData_metaObject;
}

int beModelCtrlInfoRamData_GetVTable(void) {
    struct Obj_352f30 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &g_beModelCtrlInfoRamData_vtable[0];
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beModelCtrlInfoRamData_vtable[0];
    FUN_00352fc0((igSmartPointer<igObject> *)&obj.w5, -1);
    FUN_0034c1b0((void **)&obj.w4, (short)(-1));
    FUN_00344030((struct W_344030 *)&obj, (short)0);
    return t;
}

igSmartPointer<igObject> *FUN_00352fc0(igSmartPointer<igObject> *self, int delete_storage) {
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

void beModelCtrlInfoRamData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRamData_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoRamData_callbackList[] = { beModelCtrlNode2_EnsureRegistered, beModelCtrlInfoWork_EnsureRegistered, 0 };

void *beModelCtrlInfoRamData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoRamData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoRamData_GetMetaObjectFunction,
        "beModelCtrlInfoRamData",
        0x18, /* instance size */
        beModelCtrlInfoRamData_GetVTable,
        beModelCtrlInfoRamData_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoRamData_callbackList /* callback list */
    );
}

void beModelCtrlInfoRamData_GetMetaObjectFunction(void)
{
    beModelCtrlInfoRamData_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoRamData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoRamData_fieldTable[] = {
    "_node",
    "_work",
};
static igMetaField **g_beModelCtrlInfoRamData_fieldHandles[] = {
    &g_beModelCtrlInfoRamData_nodeMetaField,
    &g_beModelCtrlInfoRamData_workMetaField,
};
static int g_beModelCtrlInfoRamData_fieldOffsets[] = {
    16,
    20,
};

void beModelCtrlInfoRamData_InitFields(void) {
    int base;
    int index;
    void **found;
    void *node;
    void *work;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beModelCtrlInfoRamData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoRamData_ctorTable, 2);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igStringMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igStringMetaField_SetDefaultText(clone, "ONE");
    clone->_externalEnumStorage = (int)(&g_beModelCtrlInfoRamData_nameStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    node = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)node)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    work = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beModelCtrlInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beModelCtrlInfoRamData_fieldTable, g_beModelCtrlInfoRamData_fieldHandles, g_beModelCtrlInfoRamData_fieldOffsets, base);
}

