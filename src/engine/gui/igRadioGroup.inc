igMetaObject *FUN_0044cdf0(void) {
    if (g_igRadioGroup_metaObject[0] == 0) {
        g_igRadioGroup_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igRadioGroup_metaObject[0];
}

igMetaObject *igRadioGroup_GetMetaObject(void)
{
    igMetaObject *g = g_igRadioGroup_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRadioGroup_EnsureRegistered();
    return g_igRadioGroup_metaObject[0];
}

int igRadioGroup_GetVTable(void) {
    union U_44ce90 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00540dd0[0];
    p48 = &u.b[8];
    *(int *)p48 = 0;
    p4C = &u.b[12];
    *(int *)p4C = 0;
    p50 = &u.b[16];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00540dd0[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return r;
}

void igRadioGroup_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRadioGroup_Register);
}

void igRadioGroup_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroup_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRadioGroup_GetMetaObject,
        igRadioGroup_className,
        0x20, /* instance size */
        igRadioGroup_GetVTable,
        &igRadioGroup_InitFields,
        0, /* extra callback item */
        g_igRadioGroup_callbackList /* callback list */
    );
}

void thunk_igRadioGroup_GetMetaObject(void) {
    igRadioGroup_GetMetaObject();
}

void igRadioGroup_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s1;

    temp_s1 = (void *)g_igRadioGroup_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igRadioGroup_ctorTable[0], 6);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0044d170();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_0044cbd0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_0044c880();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), -1);
    igMetaObject_NameFields(temp_s1, &g_igRadioGroup_fieldTable[0], &DAT_004d0060[0], &DAT_004d0080[0], temp_s0);
}

