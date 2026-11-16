igMetaObject *g_igRadioGroupModel_metaObject;
igMetaField *g_igRadioGroupModel_selectedMetaField;

igMetaObject *FUN_0044d170(void) {
    if (g_igRadioGroupModel_metaObject == 0) {
        g_igRadioGroupModel_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRadioGroupModel_metaObject;
}

igMetaObject *igRadioGroupModel_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroupModel_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroupModel_RunStaticInit();
    return g_igRadioGroupModel_metaObject;
}

int igRadioGroupModel_GetVTable(void) {
    union U_44d210 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader((igObject *)u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&g_igModel_vtable[0];
    u.vt = (int)&g_igRadioGroupModel_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem) + 916)];
    u.vt = (int)&g_igModel_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void igRadioGroupModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igRadioGroupModel_Register);
}

CallbackArray *igRadioGroupModel_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRadioGroupModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igRadioGroupModel_GetMetaObject,
        "igRadioGroupModel",
        0x10, /* instance size */
        igRadioGroupModel_GetVTable,
        &igRadioGroupModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRadioGroupModel_GetMetaObject(void) {
    igRadioGroupModel_GetMetaObject();
}

igMetaObject *FUN_0044d340(void) {
    return g_igModel_metaObject;
}

static FieldFactory g_igRadioGroupModel_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_igRadioGroupModel_fieldTable[] = {
    "_selected",
};
static igMetaField **g_igRadioGroupModel_fieldHandles[] = {
    &g_igRadioGroupModel_selectedMetaField,
};
static int g_igRadioGroupModel_fieldOffsets[] = {
    12,
};

void igRadioGroupModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRadioGroupModel_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igRadioGroupModel_ctorTable, 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igRadioGroupModel_fieldTable, g_igRadioGroupModel_fieldHandles, g_igRadioGroupModel_fieldOffsets, temp_s1);
}

