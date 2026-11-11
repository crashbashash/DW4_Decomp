int FUN_0044f790(void) {
    if (DAT_0058c438[0] == 0) {
        DAT_0058c438[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c438[0];
}

igMetaObject *igGuiComponentModel_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentModel_RunStaticInit();
    return g_igGuiComponentModel_metaObject[0];
}

int igGuiComponentModel_GetVTable(void) {
    union U_44f830 u;
    int temp_s0;
    S_ref *q0;

    igObject_InitHeader(u.b);
    q0 = (S_ref *)&u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00540e30[0];
    u.vt = (int)&DAT_00541e30[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
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

void igGuiComponentModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiComponentModel_Register);
}

void igGuiComponentModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igGuiComponentModel_GetMetaObject,
        igGuiComponentModel_className,
        0x24, /* instance size */
        igGuiComponentModel_GetVTable,
        &igGuiComponentModel_InitFields,
        0, /* extra callback item */
        g_igGuiComponentModel_callbackList /* callback list */
    );
}

void thunk_igGuiComponentModel_GetMetaObject(void) {
    igGuiComponentModel_GetMetaObject();
}

void igGuiComponentModel_InitFields(void) {
    int temp_s2;
    void *temp_a0;
    void *temp_s1;
    struct { int a; int b; int c; } z;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c438[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d04b0[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = FUN_0044ff40();
    *(char *)(60 + (char *)(temp_s1)) = 0;
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1), 1);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    z.a = 0;
    z.b = 0;
    z.c = 0;
    FUN_0018e470(temp_a0, &z);
    igMetaObject_NameFields(temp_s0, &DAT_004d04d0[0], &DAT_004d04f0[0], &DAT_004d0510[0], temp_s2);
}

