igMetaObject *g_beLuaState_metaObject;
igMetaField *g_beLuaState_lpMetaField;

void beLuaState_Create(int arg0) {
    beLuaState_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5891B0, arg0);
}

igMetaObject *beLuaState_GetOrCreateMetaObject(void) {
    if (g_beLuaState_metaObject == 0) {
        g_beLuaState_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLuaState_metaObject;
}

void *beLuaState_GetMetaObject(void) {
    igMetaObject *g = g_beLuaState_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLuaState_EnsureRegistered();
    }
    return g_beLuaState_metaObject;
}

int beLuaState_GetVTable(void) {
    Obj_35ab00 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_igLuaState_vtable[0];
    obj.r1 = 0;
    obj.r2 = 0;
    obj.vt = &g_beLuaState_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_igLuaState_vtable[0];
    obj.rel2();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

void beLuaState_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLuaState_Register);
}

void *beLuaState_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaState_metaObject,
        igLuaState_Register,
        igLuaState_GetPublishedMetaObject,
        beLuaState_GetMetaObjectFunction,
        "beLuaState",
        0x18, /* instance size */
        beLuaState_GetVTable,
        beLuaState_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLuaState_GetMetaObjectFunction(void)
{
    beLuaState_GetMetaObject();
}

int igLuaState_GetPublishedMetaObject(void) {
    return g_igLuaState_metaObject[0];
}

static FieldFactory g_beLuaState_ctorTable[] = {
    igRawRefMetaField_Create,
};
static const char *g_beLuaState_fieldTable[] = {
    "_lp",
};
static igMetaField **g_beLuaState_fieldHandles[] = {
    &g_beLuaState_lpMetaField,
};
static int g_beLuaState_fieldOffsets[] = {
    20,
};

void beLuaState_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLuaState_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beLuaState_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beLuaState_fieldTable, g_beLuaState_fieldHandles, g_beLuaState_fieldOffsets, temp_s1);
}

