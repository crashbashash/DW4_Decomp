int FUN_00452340(void) {
    if (DAT_0058c610[0] == 0) {
        DAT_0058c610[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c610[0];
}

igMetaObject *igBoxComponent_GetMetaObject(void)
{
    igMetaObject *g = g_igBoxComponent_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igBoxComponent_RunStaticInit();
    return g_igBoxComponent_metaObject[0];
}

int igBoxComponent_GetVTable(void) {
    struct F f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[2] = 0;
    f.w[3] = 0;
    f.w[4] = 0;
    f.w[6] = 0;
    f.vt = &DAT_005417e0[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    f.vt = &DAT_005417e0[0];
    FUN_00450090((O_450090 *)&f, 0);
    return temp_s0;
}

void igBoxComponent_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBoxComponent_Register);
}

void igBoxComponent_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoxComponent_metaObject,
        igGuiComponent_Register,
        igGuiComponent_GetPublishedMetaObject,
        thunk_igBoxComponent_GetMetaObject,
        igBoxComponent_className,
        0x24, /* instance size */
        igBoxComponent_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBoxComponent_GetMetaObject(void) {
    igBoxComponent_GetMetaObject();
}

int FUN_004524e0(void) {
    return DAT_0058c4a8[0];
}

