igMetaObject *FUN_0044f210(void) {
    if (g_igGuiSystemModel_metaObject[0] == 0) {
        g_igGuiSystemModel_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGuiSystemModel_metaObject[0];
}

igMetaObject *igGuiSystemModel_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiSystemModel_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiSystemModel_RunStaticInit();
    return g_igGuiSystemModel_metaObject[0];
}

int igGuiSystemModel_GetVTable(void) {
    struct igGuiSystemModel s;
    char *p;
    int r;
    p = (char *)&s;
    igObject_InitHeader(p);
    s._views = 0;
    *(int **)&s._vtable = &DAT_00541170[0];
    igMatrix44f_SetIdentity(s._viewMatrix);
    igMatrix44f_SetIdentity(((struct igGuiSystemModel *)p)->_projectionMatrix);
    ((struct igGuiSystemModel *)p)->_rootComponent = 0;
    ((struct igGuiSystemModel *)p)->_focusedComponent = 0;
    ((struct igGuiSystemModel *)p)->_componentUnderMouse = 0;
    ((struct igGuiSystemModel *)p)->_pushedComponent = 0;
    r = *(int *)((char *)&s + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&s._vtable = &DAT_00541170[0];
    FUN_003cafa0(&s._pushedComponent, -1);
    FUN_003cafa0(&s._componentUnderMouse, -1);
    FUN_003cafa0(&s._focusedComponent, -1);
    FUN_003cafa0(&s._rootComponent, -1);
    FUN_0044c110((S *)&s, 0);
    return r;
}

void igGuiSystemModel_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igGuiSystemModel_Register);
}

void igGuiSystemModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiSystemModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igGuiSystemModel_GetMetaObject,
        igGuiSystemModel_className,
        0xB8, /* instance size */
        igGuiSystemModel_GetVTable,
        &igGuiSystemModel_InitFields,
        0, /* extra callback item */
        g_igGuiSystemModel_callbackList /* callback list */
    );
}

void thunk_igGuiSystemModel_GetMetaObject(void) {
    igGuiSystemModel_GetMetaObject();
}

void igGuiSystemModel_InitFields(void) {
    int temp_s2;
    int sp48[2];
    int sp40[2];
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s0;

    temp_s0 = (void *)g_igGuiSystemModel_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igGuiSystemModel_ctorTable[0], 0xB);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    sp48[0] = 0;
    sp48[1] = 0;
    FUN_0018e2f0(temp_a0, sp48);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    sp40[0] = 0;
    sp40[1] = 0;
    FUN_0018e2f0(temp_a0_2, sp40);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_0044ff40();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    *(int *)((char *)(temp_s1_2) + 56) = (int)FUN_0044ff40();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    *(int *)((char *)(temp_s1_3) + 56) = (int)FUN_0044ff40();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9));
    *(int *)((char *)(temp_s1_4) + 56) = (int)FUN_0044ff40();
    igMetaObject_NameFields(temp_s0, &g_igGuiSystemModel_fieldTable[0], &DAT_004d0420[0], &DAT_004d0450[0], temp_s2);
}

