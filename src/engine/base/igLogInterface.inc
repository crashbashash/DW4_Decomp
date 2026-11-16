igMetaObject *g_igLogInterface_metaObject;
igMetaField *g_igLogInterface_verboseMetaField;

igMetaObject *FUN_002265e0(void) {
    if (g_igLogInterface_metaObject == 0) {
        g_igLogInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLogInterface_metaObject;
}

igMetaObject *igLogInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igLogInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002266c0();
    return g_igLogInterface_metaObject;
}

int igLogInterface_GetVTable(void) {
    union U_2 u;

    igObject_InitHeader((igObject *)u.b);
    u.w[0] = (int)(&g_igLogInterface_vtable[0]);
    return *(int *)&u.b[*(int *)((char *)g_objectSystem + 916)];
}

void FUN_002266c0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igLogInterface_Register);
}

CallbackArray *igLogInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLogInterface_metaObject,
        (igMetaObjectRegisterFunction)igInterface_Register,
        (igMetaObjectGetFunction)igInterface_GetPublishedMetaObject,
        thunk_igLogInterface_GetMetaObject,
        "igLogInterface",
        0x24, /* instance size */
        igLogInterface_GetVTable,
        &igLogInterface_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLogInterface_GetMetaObject(void) {
    igLogInterface_GetMetaObject();
}

static FieldFactory g_igLogInterface_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igLogInterface_fieldTable[] = {
    "_verbose",
};
static igMetaField **g_igLogInterface_fieldHandles[] = {
    &g_igLogInterface_verboseMetaField,
};
static int g_igLogInterface_fieldOffsets[] = {
    32,
};

void igLogInterface_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igLogInterface_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igLogInterface_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_igLogInterface_fieldTable, g_igLogInterface_fieldHandles, g_igLogInterface_fieldOffsets, temp_s1);
}

