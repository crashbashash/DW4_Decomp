igMetaObject *igOnOffModel_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffModel_RunStaticInit();
    return g_igOnOffModel_metaObject[0];
}

int igOnOffModel_GetVTable(void) {
    union U_44d430 u;
    int temp_s0;
    char *q1;
    void *temp_a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00540e30[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00541c40[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (q1 != 0) {
        temp_a0 = *(void **)q1;
        if (temp_a0 != 0) {
            *(int *)((char *)(temp_a0) + 4) = (int)((int) (*(int *)((char *)(temp_a0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_a0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    return temp_s0;
}

void igOnOffModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igOnOffModel_Register);
}

void igOnOffModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffModel_metaObject,
        igGuiComponentModel_Register,
        igGuiComponentModel_GetPublishedMetaObject,
        thunk_igOnOffModel_GetMetaObject,
        igOnOffModel_className,
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

void igOnOffModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igOnOffModel_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d00b8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004d00c0[0], &DAT_004d00c8[0], &DAT_004d00d0[0], temp_s1);
}

