igMetaObject *g_beMessengerDelay_metaObject;
igMetaField *g_beMessengerDelay_isUseMetaField;
igMetaField *g_beMessengerDelay_sendTimeMetaField;
igMetaField *g_beMessengerDelay_groupNameMetaField;
igMetaField *g_beMessengerDelay_infoNameMetaField;
igMetaField *g_beMessengerDelay_ramNoMetaField;
igMetaField *g_beMessengerDelay_messageMetaField;
igMetaField *g_beMessengerDelay_argDataMetaField;

void *beMessengerDelay_Create(void *allocator){beMessengerDelay_EnsureRegistered();return ((void *)igMetaObject_CreateInstance((void *)g_beMessengerDelay_metaObject,allocator));}

igMetaObject *beMessengerDelay_GetMetaObject(void) {
    igMetaObject *g = g_beMessengerDelay_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beMessengerDelay_EnsureRegistered();
    return g_beMessengerDelay_metaObject;
}

int beMessengerDelay_GetVTable(void) {
    union U_3589e0 u;
    int temp_s3;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_beMessengerDelay_vtable[0]);
    u.w[6] = 0;
    u.w[7] = 0;
    u.w[9] = 0;
    u.w[10] = 0;
    temp_s3 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beMessengerDelay_vtable[0]);
    FUN_00357a90((igSmartPointer<igObject> *)&u.w[10], -1);
    igStringRef_Destruct(&u.w[9], -1);
    igStringRef_Destruct(&u.w[7], -1);
    igStringRef_Destruct(&u.w[6], -1);
    return temp_s3;
}

void beMessengerDelay_EnsureRegistered(){igMetaObject_RunStaticInit(beMessengerDelay_Register);}

static igMetaObjectCallback g_beMessengerDelay_callbackList[] = { beMessengerArgData_EnsureRegistered, 0 };

void *beMessengerDelay_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerDelay_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMessengerDelay_GetMetaObjectFunction,
        "beMessengerDelay",
        0x30, /* instance size */
        beMessengerDelay_GetVTable,
        beMessengerDelay_InitFields,
        0, /* extra callback item */
        g_beMessengerDelay_callbackList /* callback list */
    );
}

void beMessengerDelay_GetMetaObjectFunction(void)
{
    beMessengerDelay_GetMetaObject();
}

static FieldFactory g_beMessengerDelay_ctorTable[] = {
    igBoolMetaField_Create,
    igLongMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMessengerDelay_fieldTable[] = {
    "_isUse",
    "_sendTime",
    "_groupName",
    "_infoName",
    "_ramNo",
    "_message",
    "_argData",
};
static igMetaField **g_beMessengerDelay_fieldHandles[] = {
    &g_beMessengerDelay_isUseMetaField,
    &g_beMessengerDelay_sendTimeMetaField,
    &g_beMessengerDelay_groupNameMetaField,
    &g_beMessengerDelay_infoNameMetaField,
    &g_beMessengerDelay_ramNoMetaField,
    &g_beMessengerDelay_messageMetaField,
    &g_beMessengerDelay_argDataMetaField,
};
static int g_beMessengerDelay_fieldOffsets[] = {
    8,
    16,
    24,
    28,
    32,
    36,
    40,
};

void beMessengerDelay_InitFields(void) {
    int base;
    void *argData;
    void *meta;

    meta = (void *)g_beMessengerDelay_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMessengerDelay_ctorTable, 7);
    argData = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)argData)->_metaObject = (int)beMessengerArgData_GetOrCreateMetaObject();
    ((igRefMetaField *)argData)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMessengerDelay_fieldTable, g_beMessengerDelay_fieldHandles, g_beMessengerDelay_fieldOffsets, base);
}

