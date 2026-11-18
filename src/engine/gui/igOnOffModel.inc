igMetaObject *g_igOnOffModel_metaObject;
igMetaField *g_igOnOffModel_valueMetaField;

igMetaObject *igOnOffModel_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffModel_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffModel_RunStaticInit();
    return g_igOnOffModel_metaObject;
}

int igOnOffModel_GetVTable(void) {
    union U_44d430 u;
    int temp_s0;
    char *q1;
    void *temp_a0;

    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igModel_vtable[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&g_igOnOffModel_vtable[0];
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igModel_vtable[0];
    if (q1 != 0) {
        temp_a0 = *(void **)q1;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
    }
    return temp_s0;
}

void igOnOffModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igOnOffModel_Register);
}

CallbackArray *igOnOffModel_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOnOffModel_metaObject,
        igGuiComponentModel_Register,
        igGuiComponentModel_GetPublishedMetaObject,
        thunk_igOnOffModel_GetMetaObject,
        "igOnOffModel",
        0x28, /* instance size */
        igOnOffModel_GetVTable,
        &igOnOffModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igOnOffModel_GetMetaObject(void) {
    igOnOffModel_GetMetaObject();
}

static FieldFactory g_igOnOffModel_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_igOnOffModel_fieldTable[] = {
    "_value",
};
static igMetaField **g_igOnOffModel_fieldHandles[] = {
    &g_igOnOffModel_valueMetaField,
};
static int g_igOnOffModel_fieldOffsets[] = {
    36,
};

void igOnOffModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igOnOffModel_metaObject;
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igOnOffModel_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igOnOffModel_fieldTable, g_igOnOffModel_fieldHandles, g_igOnOffModel_fieldOffsets, temp_s1);
}

