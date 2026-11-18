igMetaObject *g_igListenerInterface_metaObject;
igMetaField *g_igListenerInterface_instancesMetaField;
igMetaField *g_igListenerInterface_instancesListenerMetaField;
igMetaField *g_igListenerInterface_typesMetaField;
igMetaField *g_igListenerInterface_typesListenerMetaField;

igMetaObject *igListenerInterface_GetOrCreateMetaObject(void) {
    if (g_igListenerInterface_metaObject == 0) {
        g_igListenerInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igListenerInterface_vtable[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igListenerInterface_vtable[0];
    FUN_00226db0((T_2 **)&obj.w11, -1);
    igSmartPointer_igMetaObjectList_Destruct((igSmartPointer<igObject> *)&obj.w10, -1);
    FUN_00226db0((T_2 **)&obj.w9, -1);
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&obj.w8, -1);
    return t;
}

struct T_2 **FUN_00226db0(struct T_2 **arg0, short arg1) {
    struct T_2 *o;
    if (arg0 != 0) {
        o = *arg0;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

void FUN_00226e30(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igListenerInterface_Register);
}

static igMetaObjectCallback g_igListenerInterface_callbackList[] = { igObjectList_EnsureRegistered, FUN_002270b0, igMetaObjectList_EnsureRegistered, 0 };

CallbackArray *igListenerInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igListenerInterface_metaObject,
        (igMetaObjectRegisterFunction)igInterface_Register,
        (igMetaObjectGetFunction)igInterface_GetPublishedMetaObject,
        igListenerInterface_GetMetaObjectFunction,
        "igListenerInterface",
        0x30, /* instance size */
        igListenerInterface_GetVTable,
        &igListenerInterface_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igListenerInterface_callbackList /* callback list */
    );
}

void igListenerInterface_GetMetaObjectFunction(void) {
    igListenerInterface_GetMetaObject();
}

static FieldFactory g_igListenerInterface_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
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
    int base;
    void *field;
    void *field2;
    void *field3;
    void *field4;
    igMetaObject *meta;

    meta = g_igListenerInterface_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igListenerInterface_ctorTable, 4);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igListenerListList_GetOrCreateMetaObject();
    ((igRefMetaField *)field2)->_construct = 1;
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field3)->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)field3)->_construct = 1;
    field4 = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)field4)->_metaObject = (int)igListenerListList_GetOrCreateMetaObject();
    ((igRefMetaField *)field4)->_construct = 1;
    igMetaObject_NameFields(meta, g_igListenerInterface_fieldTable, g_igListenerInterface_fieldHandles, g_igListenerInterface_fieldOffsets, base);
}

