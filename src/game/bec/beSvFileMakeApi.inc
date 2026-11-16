igMetaObject *g_beSvFileMakeApi_metaObject;
igMetaField *g_beSvFileMakeApi_earlyGamedataMetaField;
igMetaField *g_beSvFileMakeApi_saveWorkMetaField;

void beSvFileMakeApi_Create(int allocator) {
    beSvFileMakeApi_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588280, allocator);
}

void *beSvFileMakeApi_GetMetaObject(void) {
    igMetaObject *g = g_beSvFileMakeApi_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSvFileMakeApi_EnsureRegistered();
    }
    return g_beSvFileMakeApi_metaObject;
}

int beSvFileMakeApi_GetVTable(void) {
    struct Obj_349e00 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[11] = 0;
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.vt = &g_beSvFileMakeApi_vtable[0];
    obj.w[15] = 0;
    obj.w[16] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSvFileMakeApi_vtable[0];
    igSmartPointer_beSaveMemoryObj_Destruct((igSmartPointer<igObject> *)(&obj.w[16]), (short)(-1));
    FUN_00349080((igSmartPointer<igObject> *)(&obj.w[15]), (long long)(-1));
    FUN_00348390((struct S_348390 *)&obj, (short)0);
    return r;
}

void beSvFileMakeApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvFileMakeApi_Register);
}

static igMetaObjectCallback g_beSvFileMakeApi_callbackList[] = { beSvPlatBaseData_EnsureRegistered, beSaveMemoryObj_EnsureRegistered, 0 };

void *beSvFileMakeApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvFileMakeApi_metaObject,
        beSaveApi_Register,
        beSaveApi_GetPublishedMetaObject,
        beSvFileMakeApi_GetMetaObjectFunction,
        "beSvFileMakeApi",
        0x418, /* instance size */
        beSvFileMakeApi_GetVTable,
        beSvFileMakeApi_InitFields,
        0, /* extra callback item */
        g_beSvFileMakeApi_callbackList /* callback list */
    );
}

void beSvFileMakeApi_GetMetaObjectFunction(void)
{
    beSvFileMakeApi_GetMetaObject();
}

static FieldFactory g_beSvFileMakeApi_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSvFileMakeApi_fieldTable[] = {
    "_earlyGamedata",
    "_saveWork",
};
static igMetaField **g_beSvFileMakeApi_fieldHandles[] = {
    &g_beSvFileMakeApi_earlyGamedataMetaField,
    &g_beSvFileMakeApi_saveWorkMetaField,
};
static int g_beSvFileMakeApi_fieldOffsets[] = {
    64,
    68,
};

void beSvFileMakeApi_InitFields(void) {
    int base;
    void *saveWork;
    void *earlyGamedata;
    void *meta;

    meta = (void *)g_beSvFileMakeApi_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvFileMakeApi_ctorTable, 2);
    earlyGamedata = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)earlyGamedata)->_metaObject = (int)beSvPlatBaseData_GetOrCreateMetaObject();
    saveWork = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)saveWork)->_metaObject = (int)beSaveMemoryObj_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSvFileMakeApi_fieldTable, g_beSvFileMakeApi_fieldHandles, g_beSvFileMakeApi_fieldOffsets, base);
}

