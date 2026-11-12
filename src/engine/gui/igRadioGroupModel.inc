igMetaObject *FUN_0044d170(void) {
    if (g_igRadioGroupModel_metaObject[0] == 0) {
        g_igRadioGroupModel_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igRadioGroupModel_metaObject[0];
}

igMetaObject *igRadioGroupModel_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroupModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroupModel_RunStaticInit();
    return g_igRadioGroupModel_metaObject[0];
}

int igRadioGroupModel_GetVTable(void) {
    union U_44d210 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00540e30[0];
    u.vt = (int)&DAT_00541ca0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00540e30[0];
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

void igRadioGroupModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroupModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igRadioGroupModel_GetMetaObject,
        igRadioGroupModel_className,
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
    return g_igModel_metaObject[0];
}

void igRadioGroupModel_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRadioGroupModel_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0098[0], 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s0, temp_s1), -1);
    igMetaObject_NameFields(temp_s0, &DAT_004d00a0[0], &DAT_004d00a8[0], &DAT_004d00b0[0], temp_s1);
}

