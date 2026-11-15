igMetaObject *g_igListenerInterface_metaObject;
igMetaField *g_igListenerInterface_instancesMetaField;
igMetaField *g_igListenerInterface_instancesListenerMetaField;
igMetaField *g_igListenerInterface_typesMetaField;
igMetaField *g_igListenerInterface_typesListenerMetaField;

igMetaObject *FUN_00226c60(void) {
    if (g_igListenerInterface_metaObject == 0) {
        g_igListenerInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igListenerInterface_metaObject;
}

igMetaObject *igListenerInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226e30();
    return g_igListenerInterface_metaObject;
}

int igListenerInterface_GetVTable(void) {
    struct Obj_5 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c080[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052c080[0];
    FUN_00226db0((T_2 **)&obj.w11, -1);
    igSmartPointer_igMetaObjectList_Destruct(&obj.w10, -1);
    FUN_00226db0((T_2 **)&obj.w9, -1);
    igSmartPointer_igObjectList_Destruct(&obj.w8, -1);
    return t;
}

struct T_2 **FUN_00226db0(struct T_2 **arg0, short arg1) {
    struct T_2 *o;
    if (arg0 != 0) {
        o = *arg0;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_00226e30(void)
{
    igMetaObject_RunStaticInit(igListenerInterface_Register);
}

static igMetaObjectCallback g_igListenerInterface_callbackList[] = { igObjectList_EnsureRegistered, FUN_002270b0, igMetaObjectList_EnsureRegistered, 0 };

void igListenerInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igListenerInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igListenerInterface_GetMetaObject,
        "igListenerInterface",
        0x30, /* instance size */
        igListenerInterface_GetVTable,
        &igListenerInterface_InitFields,
        0, /* extra callback item */
        g_igListenerInterface_callbackList /* callback list */
    );
}

void thunk_igListenerInterface_GetMetaObject(void) {
    igListenerInterface_GetMetaObject();
}

static FieldFactory g_igListenerInterface_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igListenerInterface_fieldTable[] = {
    "_instances",
    "_instancesListener",
    "_types",
    "_typesListener",
};
static igMetaField **g_igListenerInterface_fieldHandles[] = {
    &g_igListenerInterface_instancesMetaField,
    &g_igListenerInterface_instancesListenerMetaField,
    &g_igListenerInterface_typesMetaField,
    &g_igListenerInterface_typesListenerMetaField,
};
static int g_igListenerInterface_fieldOffsets[] = {
    32,
    36,
    40,
    44,
};

void igListenerInterface_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    igMetaObject *temp_s1;

    temp_s1 = g_igListenerInterface_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igListenerInterface_ctorTable, 4);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_00226fd0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igMetaObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_00226fd0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_igListenerInterface_fieldTable, g_igListenerInterface_fieldHandles, g_igListenerInterface_fieldOffsets, temp_s0);
}

